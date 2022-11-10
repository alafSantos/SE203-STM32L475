#include "matrix.h"

/*
    DRIVER     PROCESSEUR
    SB	       PC5
    LAT	       PC4
    RST	       PC3
    SCK	       PB1
    SDA	       PA4
    C0	       PB2
    C1	       PA15
    C2	       PA2
    C3	       PA7
    C4	       PA6
    C5	       PA5
    C6	       PB0
    C7	       PA3
*/

/* Contrôle des broches */
#define SB(value)   (GPIOC->BSRR = value ? GPIO_BSRR_BS5_Msk : GPIO_BSRR_BR5_Msk)
#define LAT(value)  (GPIOC->BSRR = value ? GPIO_BSRR_BS4_Msk : GPIO_BSRR_BR4_Msk)
#define RST(value)  (GPIOC->BSRR = value ? GPIO_BSRR_BS3_Msk : GPIO_BSRR_BR3_Msk)
#define SCK(value)  (GPIOB->BSRR = value ? GPIO_BSRR_BS1_Msk : GPIO_BSRR_BR1_Msk)
#define SDA(value)  (GPIOA->BSRR = value ? GPIO_BSRR_BS4_Msk : GPIO_BSRR_BR4_Msk)
#define ROW0(value) (GPIOB->BSRR = value ? GPIO_BSRR_BS2_Msk : GPIO_BSRR_BR2_Msk)
#define ROW1(value) (GPIOA->BSRR = value ? GPIO_BSRR_BS15_Msk : GPIO_BSRR_BR15_Msk)
#define ROW2(value) (GPIOA->BSRR = value ? GPIO_BSRR_BS2_Msk : GPIO_BSRR_BR2_Msk)
#define ROW3(value) (GPIOA->BSRR = value ? GPIO_BSRR_BS7_Msk : GPIO_BSRR_BR7_Msk)
#define ROW4(value) (GPIOA->BSRR = value ? GPIO_BSRR_BS6_Msk : GPIO_BSRR_BR6_Msk)
#define ROW5(value) (GPIOA->BSRR = value ? GPIO_BSRR_BS5_Msk : GPIO_BSRR_BR5_Msk)
#define ROW6(value) (GPIOB->BSRR = value ? GPIO_BSRR_BS0_Msk : GPIO_BSRR_BR0_Msk)
#define ROW7(value) (GPIOA->BSRR = value ? GPIO_BSRR_BS3_Msk : GPIO_BSRR_BR3_Msk)

enum {
    LOW,
    HIGH
};

static void delay(uint32_t n){
  for(uint32_t i = 0; i < n; i++)
    asm volatile("nop");
}

/* Génération de pulse */
void pulse_SCK(){
    SCK(LOW);
    SCK(HIGH);
    SCK(LOW);
}

void pulse_LAT(){
    LAT(HIGH);
    LAT(LOW);
    LAT(HIGH);
}


/* Contrôle des lignes */
void deactivate_rows(){
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
}

void activate_row(int row){
    switch (row)
    {
        case 0:
            ROW0(HIGH);
            break;

        case 1:
            ROW1(HIGH);
            break;  
        
        case 2:
            ROW2(HIGH);
            break;

        case 3:
            ROW3(HIGH);
            break;

        case 4:
            ROW4(HIGH);
            break;

        case 5:
            ROW5(HIGH);
            break;

        case 6:
            ROW6(HIGH);
            break;

        case 7:
            ROW7(HIGH);
            break;

        default:
            deactivate_rows();
            break;
    }
}

/* Contrôle du DM163 */
void send_byte(uint8_t val, int bank) {
    /* 
        le premier, appelé BANK0 qui stocke 6 bits par LED. Il contient donc 24*6 = 144 bits.
        le deuxième, appelé BANK1 qui stocke 8 bits par LED. Il contient donc 24*8 = 192 bits.
    */
    SB(bank);
    uint8_t counter = 5;
    if(bank)
        counter = 7;
    do{
        SDA((1<<counter) & val);
        pulse_SCK();
    }while(counter--);
}

void mat_set_row(int row, const rgb_color *val){
    uint8_t i = 7;
    do
    {
        send_byte(val[i].b, 1);
        send_byte(val[i].g, 1);
        send_byte(val[i].r, 1);
    } while (i--);
    deactivate_rows();
    delay(1000);
    pulse_LAT();
    activate_row(row);
}

/* Initialisation du BANK0 */
void init_bank0(){
    for (uint8_t i = 0; i<24; i++) // 24 broches
        send_byte(0xFF, 0);
    pulse_LAT();
}

/* met en marche les horloges des ports A, B et C */
static void clock_enable(){
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN;
}

/* configure toutes les broches reliées au driver en mode GPIO Output avec la vitesse maximale (très haute vitesse) */
static void pinMode(){
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE5_Msk) | GPIO_MODER_MODE5_0;   // 01: General purpose output mode
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE4_Msk) | GPIO_MODER_MODE4_0;   // 01: General purpose output mode
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE3_Msk) | GPIO_MODER_MODE3_0;   // 01: General purpose output mode
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE1_Msk) | GPIO_MODER_MODE1_0;   // 01: General purpose output mode
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE4_Msk) | GPIO_MODER_MODE4_0;   // 01: General purpose output mode
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE2_Msk) | GPIO_MODER_MODE2_0;   // 01: General purpose output mode
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE15_Msk) | GPIO_MODER_MODE15_0; // 01: General purpose output mode
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE2_Msk) | GPIO_MODER_MODE2_0;   // 01: General purpose output mode
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE7_Msk) | GPIO_MODER_MODE7_0;   // 01: General purpose output mode
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE6_Msk) | GPIO_MODER_MODE6_0;   // 01: General purpose output mode
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE5_Msk) | GPIO_MODER_MODE5_0;   // 01: General purpose output mode
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE0_Msk) | GPIO_MODER_MODE0_0;   // 01: General purpose output mode
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE3_Msk) | GPIO_MODER_MODE3_0;   // 01: General purpose output mode

    GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_Msk; // 11: Very high speed
    GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED4_Msk; // 11: Very high speed
    GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_Msk; // 11: Very high speed
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED1_Msk; // 11: Very high speed
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED4_Msk; // 11: Very high speed
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED2_Msk; // 11: Very high speed
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED15_Msk;// 11: Very high speed
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED2_Msk; // 11: Very high speed
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED7_Msk; // 11: Very high speed
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED6_Msk; // 11: Very high speed
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_Msk; // 11: Very high speed
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED0_Msk; // 11: Very high speed
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_Msk; // 11: Very high speed
}

/* positionne ces sorties à une valeur initiale acceptable */
static void output_init(){
    RST(LOW); // RST : 0 (reset le DM163)
    LAT(HIGH); // LAT : 1
    SB(HIGH); // SB : 1
    SCK(LOW); // SCK : 0
    SDA(LOW); // SDA : 0
    ROW0(LOW); // C0 : 0
    ROW1(LOW); // C1 : 0
    ROW2(LOW); // C2 : 0
    ROW3(LOW); // C3 : 0
    ROW4(LOW); // C4 : 0
    ROW5(LOW); // C5 : 0
    ROW6(LOW); // C6 : 0
    ROW7(LOW); // C7 : 0
}

/* attend au moins 100ms que le DM163 soit initialisé, puis passe RST à l'état haut. */
static void delayRST(){
    delay(8*1000000);
    GPIOC->BSRR = GPIO_BSRR_BS3_Msk; // RST = PC3
}

/* Initialisation des broches */
void matrix_init(){
    clock_enable();
    pinMode();
    output_init();
    delayRST();
    init_bank0();
}

static rgb_color rgb(uint8_t r, uint8_t g, uint8_t b){
    rgb_color color;
    float c = 0.1; // Pourcentage d'intensité du LED
    color.r = (uint8_t) r*c;
    color.g = (uint8_t) g*c;
    color.b = (uint8_t) b*c;

    return color;
}

/* Premier test */
// colors source rgb : https://www.rapidtables.com/web/color
void test_pixels() {
    uint8_t row = 0;
    rgb_color r[8];
    rgb_color g[8];
    rgb_color b[8];

    // dégradé de rouge
    r[0] = rgb(255,160,122);
    r[1] = rgb(250,128,114);
    r[2] = rgb(205,92,92);
    r[3] = rgb(220,20,60);
    r[4] = rgb(178,34,34);
    r[5] = rgb(255,0,0);
    r[6] = rgb(139,0,0);
    r[7] = rgb(128,0,0);

    // dégradé de vert
    g[0] = rgb(50,205,50);
    g[1] = rgb(173,255,47);
    g[2] = rgb(34,139,34);
    g[3] = rgb(124,252,0);
    g[4] = rgb(127,255,0);
    g[5] = rgb(0,255,0);
    g[6] = rgb(0,128,0);
    g[7] = rgb(0,100,0);

    // dégradé de bleu
    b[0] = rgb(176,224,230);
    b[1] = rgb(135,206,250);
    b[2] = rgb(0,191,255);
    b[3] = rgb(30,144,255);
    b[4] = rgb(100,149,237);
    b[5] = rgb(65,105,225);
    b[6] = rgb(0,0,255);
    b[7] = rgb(0,0,139);

    rgb_color *color = g;
    while(1){
        mat_set_row(row++, color);
        
        delay(800000);

        if(row == 8){
            if(color == b)
                color = g;
            else if (color == g)  
                color = r;
            else color = b;
            row = 0;
        }
    }
}

/*
    Faites en sorte que fonction main affiche automatiquement cette image, 
    en cyclant sur les lignes suffisament vite pour que l'œil ait l'impression d'une image statique. 
*/
void display_image(const rgb_color * image){ //image = &_binary_image_raw_start
    for (int row = 0; row < 8; row++){
        mat_set_row(row, &image[8*row]);
    }
}