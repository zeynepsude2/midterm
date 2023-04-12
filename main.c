#include "stm32f4xx.h"

#define LED_PIN 14
#define DURATION 13530
#define TIMERNUMBER 13

void delay(uint32_t ms);

int main()
{

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;


    GPIOD->MODER |= (1 << (LED_PIN * 2));


    TIM6->PSC = 8399;
    TIM6->ARR = DURATION;


    TIM6->CR1 |= TIM_CR1_CEN;
    TIM6->DIER |= TIM_DIER_UIE;


    NVIC_SetPriority(TIM6_DAC_IRQn, 3);
    NVIC_EnableIRQ(TIM6_DAC_IRQn);

    while(1)
    {

    }
}

void TIM6_DAC_IRQHandler()
{
    if(TIM6->SR & TIM_SR_UIF)
    {

        TIM6->SR &= ~(TIM_SR_UIF);


        GPIOD->ODR ^= (1 << LED_PIN);


        TIM6->CR1 |= TIM_CR1_CEN;
    }
}
