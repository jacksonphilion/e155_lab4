/*********************************************************************

Jackson Philion, Oct.7.2024, jphilion@g.hmc.edu
For E155 Lab 4, Harvey Mudd College, taught by Prof Josh Brake.

This file and 

*********************************************************************/

#include "STM32L432KC_TIM.h"

void initTIM6() {
    /*
    To read out the UIF (update interrupt flag), which turns itself on and stays on whenever
    the timer overflows, you access TIM6_SR[0]. This is 0 if no recent overflow, or 1 if there
    has been an overflow since the last time this bit was cleared.

    To force an update event, resetting the counter and all that good stuff, set TIM6_EGR[0]
    to 1. This is auto-cleared by hardware after it has reset and restarted.
    */

    // Make sure TIM6 is off as we make changes – TIM6_CR1[0] clear to 0
    TIM6->CR1 &= ~0b1;          // Clear the 0th bit

    // Make sure that Buffer is off to the counterTop value – TIM6_CR1[7] clear to 0
    TIM6->CR1 &= (~(0b1<<7));   // Clear the 7th bit

    // Make sure that UIF Update Interrupt is off – TIM6_DIER[0] clear to 0
    TIM6->DIER &= (~0b1);       // Clear the 0th bit

    // Make sure that we can generate update events on counter overflow (UDIS) – TIM6_CR1[1] clear to 0
    TIM6->CR1 &= (~(0b1<<1));   // Set bit 1

    // Set Prescaler to (2,000 - 1), to get 20MHz CLK down to generate a 100µs delay.
    // To do this – TIM6_PSC[15:0] set to 0000011111001111  (which is 1,999)
    TIM6->PSC &= (~(0b1111111111111111));           // Clear bits 15:0
    TIM6->PSC |= 0b0000011111001111;                // Set bits to intended prescaler

    // Set the top of the counter value – TIM6_ARR[15:0] set to 0000000000001010
    // Set the top of the counter value to 10, dividing the signal again, giving a final delay output of 1ms total
    TIM6->ARR &= (~(0b1111111111111111));           // Clear bits 15:0
    TIM6->ARR |= 0b0000000000001010;                // Set bits to intended counter top

    // Make sure Counter is at zero – TIM6_CNT[15:0], clear bits
    TIM6->CNT &= (~(0b1111111111111111));   // Clear bits 15:0

    // Make sure the UIF Flag is down – TIM6_SR[0] clear to 0
    TIM6->SR &= (~0b1);                     // Clear bit 0

    // Turn TIM6 back on – TIM6_CR1[0] set to 1
    TIM6->CR1 |= 0b1;           // Set bit 0 to 1

    // Reinitialize the timer counter and update its registers – TIM6_EGR[0] set to 1
    TIM6->EGR |= 0b1;           // Set bit 0 to 1
}

initTIM2_PWM(uint32_t freq) {
    /* Function to initialize TIM2 in PWM mode, outputting a square wave at
    the given frequency "freq" in hertz. 
    
    If you input a frequency of 0, this function should instead turn off  */

    // Make sure TIM2 is off as we make changes – TIM2_CR1[0] clear to 0
    TIM2->CR1 &= ~0b1;          // Clear the 0th bit
    if (freq>0) {
        // Determine frequency with TIM2_ARR[31:0] register
        TIM2->ARR &= 0b0;       // Clear all bits of ARR
        TIM2->ARR |= freq;      // Set ARR=freq

        // Determine duty cycle with TIM2_CCRx
        TIM2->CCR1 &= 0b0;
        TIM2->CCR1 |= (freq/2);

        // Select PWM mode with TIMx_CCMRx[6:4] to either 110 (PWM mode 1) or ‘111 (PWM mode 2)
        TIM2->CCMR1 &= (~(0b111<<4));
        TIM2->CCMR1 |= (0b110<<4);

        // enable the corresponding preload register in capture/compare – TIM2_CCMR1[3] set to 1 
        TIM2->CCMR1 |= (0b1<<3);

        // emable the auto-reload preload register by setting TIM2_CR1[7] 
        TIM2->CR1 |= (0b1<<7);

        // OCx polarity is software programmable using the CCxP bit in the TIMx_CCER register as active high or low

        // Enable OC1 output with the CC1E bit in TIM2_CCER[0] (set to 1)
        TIM2->CCER |= (0b1);            // Bit 0 to 1

        // CMS bits in the TIMx_CR1[6:5] determines edge alignment of the PWM wave, 00 for edge aligned
        TIM2->CCR1 &= (~(0b11<<5));     // Clear just in case

        // DIR bit in the TIMx_CR1[4] register is 0 for upcounting mode
        TIM2->CR1 &= (~(0b1<<4));       // Clear just in case

        // Generate update event with TIMx_EGR
        TIM2->EGR |= 0b1;

        // Turn the timer back on
        TIM2->CR1 |= 0b1;          // Clear the 0th bit
    }
}



void delayMillis(uint32_t ms) {
    /*  */
    initTIM6();                         // Initialize Timer 6 to fun in 1ms loops
    TIM6->SR &= (~(0b1));                   // Ensure flag is down
    for(int i = 0; i<ms; i++) {
        while (~(TIM6->SR & 0b1)) {}        // While the flag is down, wait
        TIM6->SR &= (~(0b1));               // After flag is up, reset it down
    }
}

void playNote(uint32_t freq, uint32_t milliseconds)
{
    if (freq>0){
        initTIM2_PWM(freq);                 // turn on PWM at given frequency "freq"
        delayMillis(milliseconds);          // leave the note on for time "milliseconds"
        initTIM2_PWM(0b0);                  // turn off PWM and TIM2 by passing in freq=0
    }
    else {delayMillis(milliseconds);}
}