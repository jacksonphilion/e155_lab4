// STM32L432KC_RCC.c
// Source code for RCC functions

#include "STM32L432KC_RCC.h"

void configurePLL() {
    // Set clock to 80 MHz:  Output freq = (src_clk) * (N/M) / R
    // (4 MHz) * (N/M) / R = 80 MHz
    // M: 1, N: 40, R: 2
    // Use MSI as PLLSRC, Default 4MHz

    // TODO: Turn off PLL – RCC_CR PLLON (bit 24) to 0
    RCC->CR &= (~(0b1<<24));
    
    // TODO: Wait till PLL is unlocked (e.g., off) – RCC_CR PLLRDY (bit 25), Wait until PLLRDY is 0
    while ((RCC->CR >> 25) & 0b1) {}

    // Load configuration
    // TODO: Set PLL SRC to MSI – RCC_PLLCFGR[1:0] to 01 for MSI
    RCC->PLLCFGR |= 0b1;                // Set bit 0
    RCC->PLLCFGR &= (~(0b1<<1));        // Clear bit 1

    // TODO: Set PLLN – RCC_PLLCFGR[14:8] to 0010100 for N=40
    RCC->PLLCFGR &= (~(0b1111111<<8));  // Clear all bits
    RCC->PLLCFGR |= (0b101000<<8);      // Set desired bits

    // TODO: Set PLLM – RCC_PLLCFGR[6:4] to 000 for M=1
    RCC->PLLCFGR &= (~0b111<<4);        // Clear all bits

    // TODO: Set PLLR – RCC_PLLCFGR[26:25] to 00 for R=2
    RCC->PLLCFGR &= (0b11<<25);         // Clear all bits
    
    // TODO: Enable PLLR output – RCC_PLLCFGR[24] to 1 to enable PLLCLK output
    RCC->PLLCFGR |= (0b1<<24);

    // TODO: Turn PLL Back On – RCC_CR[24] set to 1 to turn PLL back on
    RCC->CR |= (0b1<<24);
    
    // TODO: Wait until PLL is locked – RCC_CR PLLRDY (bit 25), Wait until PLLRDY is 1
    while (~(((RCC->CR)>>25)&0b1)) {}
}

void configureClock(){
    // Configure and turn on PLL
    configurePLL();

    // Select PLL as clock source
    RCC->CFGR |= (0b11 << 0);
    while(!((RCC->CFGR >> 2) & 0b11));
}

void configureClockTIM2_6(){
    /* This function assumes a running SYSCLK and enables the CLK to TIM2 and TIM6.
    Note that this function divides SYSCLK by a factor of 4, in our case 80 -> 20 MHz.*/

    // Set APB1 Prescaler – RCC_CFGR[10:8] to 100 to be divided by 2
    RCC->CFGR &= (~(0b111<<8));         // Clear all bits
    RCC->CFGR |= (0b100<<8);            // Set bits to 100

    // Set AHB Prescaler – RCC_CFGR[7:4] to 1000 to be divided by 2
    RCC->CFGR &= (~(0b1111<<4));        // Clear all bits
    RCC->CFGR |= (0b1000<<4);           // Set bits to 100

    // Enable clock to TIM2 and TIM6 – RCC_APB1ENR1 bits 0 and 4 set to 1 
    RCC->APB1ENR1 |= 0b1;               // Set bit 0 to 1
    RCC->APB1ENR1 |= (0b1<<4);          // Set bit 4 to 1

    // We never Set PCKL1 1x or 2x multiplier before it gets to TIM2,3,6,7

}