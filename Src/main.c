#include "main.h"
int main(void) {
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    //PA1 output push pull
    GPIOA->MODER &= ~GPIO_MODER_MODE1_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE1_1;
    //PA2 input pullup
    GPIOA->MODER &= ~GPIO_MODER_MODE2_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE2_0;
    GPIOA->PUPDR |= GPIO_PUPDR_PUPD1_1;

    uint8_t button_down = 0;
    while (1) {
        uint32_t idr_val = ~GPIOA->IDR;
        if (idr_val & (1 << BUTTON_PIN)) {
            if (!button_down) {
                GPIOA->ODR ^= (1 << LED_PIN);
            }
            button_down = 1;
        }
        else {
            button_down = 0;
        }
    }    
}