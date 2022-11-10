#include "uart.h"

/* Activer l'horloge du PORTB */
static void clock_enable_PB(){
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
}

/* Activer l'horloge du port série USART1
   Spécifier que l'horloge sur laquelle se base l'USART1 pour timer chaque bit est PCLK */
static void clock_enable_USART(){
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->CCIPR &= ~RCC_CCIPR_USART1SEL;
}

/* configurez ces broches en mode Alternate Function
   ST-LINK-UART1_TX -> PB6, ST-LINK-UART1_RX -> PB7 */
static void alternateFunctionMode(){
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE6_0) | GPIO_MODER_MODE6_1;
    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL6_Msk) | GPIO_AFRL_AFSEL6_0 | GPIO_AFRL_AFSEL6_1 | GPIO_AFRL_AFSEL6_2; // PB6 USART1_TX
    
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE7_0) | GPIO_MODER_MODE7_1;
    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL7_Msk) | GPIO_AFRL_AFSEL7_0 | GPIO_AFRL_AFSEL7_1 | GPIO_AFRL_AFSEL7_2; // PB7 USART1_RX
}

/* Faire un reset du port série par précaution */
static void resetSerialPort(){
    RCC->APB2RSTR |=  RCC_APB2RSTR_USART1RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;
}

/* Configurer la vitesse du port série à 115200 bauds */
static void setBaudRate(int baudrate){
    USART1->BRR = SYSCLK/baudrate;    
}

// Configurer l'oversampling à 16
static void oversampling16(){
    USART1->CR1 &= ~USART_CR1_OVER8;   
}

/* mettre le port série en mode 8N1 */
static void mode8N1(){
    USART1->CR1 &= ~(USART_CR1_M1_Msk | USART_CR1_M0_Msk) ; // M[1:0] = 00, 8 bits de données, page 1377
    USART1->CR1 &= ~(USART_CR1_PCE); // pas de parité, page 1378 
    USART1->CR2 &= ~(USART_CR2_STOP_Msk); // 1 bit de stop, page 1381
}

/* Activer l'USART1, le transmetteur et le récepteur */
static void enableUSART1TxRx(){
    USART1->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE; 
}

static void enableINT(){
    USART1->CR1 |= USART_CR1_RXNEIE; // RXNE Interrupt Enable 
    NVIC_EnableIRQ(37);
}

void uart_init(int baudrate){ 
    clock_enable_PB();
    clock_enable_USART();
    alternateFunctionMode();
    resetSerialPort();
    setBaudRate(baudrate);
    oversampling16();
    mode8N1();
    enableUSART1TxRx(); 
    enableINT();
}

/* qui attend que l'USART1 soit prêt à transmettre quelque chose, puis lui demande de l'envoyer */
void uart_putchar(uint8_t c){
    uint8_t wait_tx = 0;

    do{
        wait_tx = !(USART1->ISR & USART_ISR_TXE);
    }
    while(wait_tx);

    USART1->TDR = c;
}

/* qui attend que l'UART ait reçu un caractère puis le retourne */
uint8_t uart_getchar(){
    uint8_t wait_rx = 0;

    do{
        if(USART1->ISR & USART_ISR_ORE)
            uart_puts("Erreur d'overrun");
        else if(USART1->ISR & USART_ISR_FE)
            uart_puts("Erreur de framing");
        else{
            wait_rx = !(USART1->ISR & USART_ISR_RXNE);
            continue;
        }
        while(1); // En réception, si vous avez une erreur de framing ou d'overrun, déclenchez une boucle sans fin.
    }
    while(wait_rx);

    return USART1->RDR;
}

/* qui fait la même chose que puts sous Linux */
void uart_puts(const char *s){
    while(*s)
        uart_putchar(*s++);

    uart_putchar('\r'); //debut de la ligne
    uart_putchar('\n'); //nouvelle ligne
}

/* qui fait la même chose que fgets sous Linux */
void uart_gets(char *s, size_t size){
    for (size_t i = 0; i < size; i++){
        s[i] = uart_getchar();

        if(s[i] == '\n'){
            s[i+1] = '\0';
            break;
        }
    }    
}

/* pour vérifier le uart_getchar */
void uart_echo(){
    while(1)
        uart_putchar(uart_getchar());
}

/* fonction pour votre carte qui reçoit des octets sur le port série et en calcule la somme sur 32 bits */
uint32_t sum = 0;
void checksum(){
    while(1)
        sum += uart_getchar();
}

extern volatile uint8_t frames[192];

/* Écrivez la tâche de réception du port série (handler d'IRQ) qui traitera les octets reçus. */
void USART1_IRQHandler(void){
    /* 
        Faites en sorte que si votre UART reçoit une erreur de transmission (FE ou OR), 
        alors la trame courante est ignorée et qu'on se remette en attente de la prochaine trame. 
    */
    static uint8_t erreur = 0;

    if(erreur) return;

    if (USART1->ISR & USART_ISR_ORE || USART1->ISR & USART_ISR_FE){ // Erreur d'overrun || Erreur de framing
        USART1->RQR |= USART_RQR_RXFRQ_Msk; // The RXNE flag can also be cleared by writing 1 to the RXFRQ in the USART_RQR register
        USART1->ICR |= USART_ICR_FECF_Msk;  // The FE bit is reset by writing 1 to the FECF in the USART_ICR register.
        USART1->ICR |= USART_ICR_ORECF_Msk; // The ORE bit is reset by setting the ORECF bit in the ICR register.
        erreur = 1;
        return;
    }
    
    static uint8_t pos;
    uint8_t c = uart_getchar();

    if(c == 0xFF || pos >= 192){
        pos = 0;
        erreur = 0;
        return;
    }

    frames[pos++] = c;
}
