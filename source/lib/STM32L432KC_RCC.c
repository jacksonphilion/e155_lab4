// STM32L432KC_RCC.c
// Source code for RCC functions

#include "STM32L432KC_RCC.h"

void configurePLL() {
    // (src_clk) * (N/M) / R = outputFreq
    // (4 MHz)   * (N/M) / R = 10 MHz
    //      M: 1, N: 10, R: 4
    // Use MSI as PLLSRC, Default 4MHz

    // So, expected output of PLL (presumably to SYSCLK) is 80 MHz

    // TODO: Turn off PLL – RCC_CR PLLON (bit 24) to 0
    RCC->CR &= (~(0b1<<24));
    
    // TODO: Wait till PLL is unlocked (e.g., off) – RCC_CR PLLRDY (bit 25), Wait until PLLRDY is 0
    while ((RCC->CR >> 25) & 0b1) {}

    // Load configuration
    // TODO: Set PLL SRC to MSI – RCC_PLLCFGR[1:0] to 01 for MSI
    RCC->PLLCFGR |= 0b1;                // Set bit 0
    RCC->PLLCFGR &= (~(0b1<<1));        // Clear bit 1

    // TODO: Set PLLN – RCC_PLLCFGR[14:8] to 0001010 for N=10
    RCC->PLLCFGR &= (~(0b1111111<<8));  // Clear all bits
    RCC->PLLCFGR |= (0b0001010<<8);      // Set desired bits

    // TODO: Set PLLM – RCC_PLLCFGR[6:4] to 000 for M=1
    RCC->PLLCFGR &= (~(0b111<<4));        // Clear all bits

    // TODO: Set PLLR – RCC_PLLCFGR[26:25] to 01 for R=4
    RCC->PLLCFGR &= (~(0b11<<25));         // Clear all bits
    RCC->PLLCFGR |= (0b01<<25);            // Set to 01
    
    // TODO: Enable PLLR output – RCC_PLLCFGR[24] to 1 to enable PLLCLK output
    RCC->PLLCFGR |= (0b1<<24);

    // TODO: Turn PLL Back On – RCC_CR[24] set to 1 to turn PLL back on
    RCC->CR |= (0b1<<24);
    
    // TODO: Wait until PLL is locked – RCC_CR PLLRDY (bit 25), Wait until PLLRDY is 1
    while (!(((RCC->CR)>>25)&0b1)) {}
}

void configureClock_AndTIM2_6(){
    // Configure and turn on PLL
    configurePLL();

    // Select PLL as clock source
    // NOTE This works!

    RCC->CFGR |= (0b11 << 0);
    while(!((RCC->CFGR >> 2) & 0b11));

    // NOTE -- BELOW lines won't set bits

    /* The following lines of code enable the clock heading out to the peripherals.
    Input clock 10 MHz, output should be 2.5 MHz  */

    // Set AHB Prescaler – RCC_CFGR[7:4] to 1000 to be divided by 2
    RCC->CFGR &= (~(0b1111 << 4));        // Clear all bits
    RCC->CFGR |= (0b1000 << 4);           // Set bits to 1000

    // Set APB1 Prescaler – RCC_CFGR[10:8] to 100 to be divided by 2
    RCC->CFGR &= (~(0b111<<8));         // Clear all bits
    RCC->CFGR |= (0b100<<8);            // Set bits to 100

    // Enable clock to TIM2 and TIM6 – RCC_APB1ENR1 bits 0 and 4 set to 1 
    RCC->APB1ENR1 |= 0b1;               // Set bit 0 to 1
    RCC->APB1ENR1 |= (0b1<<4);          // Set bit 4 to 1




    // We never Set PCKL1 1x or 2x multiplier before it gets to TIM2,3,6,7
}

// Back when they were separate functions...
/*
void configureTIM2_6(){
    // This function assumes a running SYSCLK and enables the CLK to TIM2 and TIM6.
    // Note that this function divides SYSCLK by a factor of 4, in our case 80 -> 20 MHz.

    // Set AHB Prescaler – RCC_CFGR[7:4] to 1000 to be divided by 2
    RCC->CFGR &= (~(0b1111 << 4));        // Clear all bits
    RCC->CFGR |= (0b1000 << 4);           // Set bits to 100

    // Set APB1 Prescaler – RCC_CFGR[10:8] to 100 to be divided by 2
    RCC->CFGR &= (~(0b111<<8));         // Clear all bits
    RCC->CFGR |= (0b100<<8);            // Set bits to 100

    // Enable clock to TIM2 and TIM6 – RCC_APB1ENR1 bits 0 and 4 set to 1 
    RCC->APB1ENR1 |= 0b1;               // Set bit 0 to 1
    RCC->APB1ENR1 |= (0b1<<4);          // Set bit 4 to 1

    // NOTE ABOVE LINES CURRENTLY BROKEN - Not setting bits...


    // We never Set PCKL1 1x or 2x multiplier before it gets to TIM2,3,6,7
} */