#include "timer.h"
#include "irq.h"
#include "matrix.h"

void timer_init(int max_us){
    // active l'horloge du timer TIM2 (chercher le bon ENR du RCC)
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN_Msk; 

    // effacer d'éventuels flags dans le registre de statut (TIMx_SR) et mettre à zéro la valeur du compteur (TIMx_CNT)
    TIM2->SR = 0x00000000;
    TIM2->CNT = 0x00000000;

    // changer le prescaler du timer (TIMx_PSC) pour compter à la microseconde
    TIM2->PSC = (SYSCLK/SECOND) - 1; 
    
    // modifier la valeur d'auto chargement (TIMx_ARR) en fonction du paramètre de la fonction
    TIM2->ARR =  max_us;

    // configurer le timer pour avoir le bon mode de fonctionnement, sans l'activer
    TIM2->CR1 |= TIM_CR1_CKD_1;// mode compteur (upcounter)

    // autoriser la génération d'une interruption sur l'événement de mise à jour du timer (TIMx_DIER)
    TIM2->DIER |= TIM_DIER_UIE_Msk;

    // autoriser l'interruption de TIM2 au niveau du NVIC (attention, il faudra avoir un nouveau handler comme décrit dans la suite)
    NVIC_EnableIRQ(28);

    // activer le timer
    TIM2->CR1 |= TIM_CR1_CEN;
}

// Faites maintenant en sorte que l'affichage de la matrice soit géré par des interruptions du timer
extern volatile uint8_t frames[192];
void TIM2_IRQHandler(){
    if(TIM2->SR & TIM_SR_UIF_Msk){
        display_image((rgb_color *)frames);
        TIM2->SR &= ~(TIM_SR_UIF_Msk); // Update interrupt Flag
    }
}
