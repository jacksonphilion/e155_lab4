// STM32L432KC_GPIO.c
// Source code for GPIO functions

#include "STM32L432KC_GPIO.h"

////////////////////////  Turn PA5 to PWM output of TIM2_CH1  ///////////////

void pinOutputPWM(){
    /* TIM2_CH1 comes out by AF1 through Port A PA0, PA5, or PA15.
    I will choose PA5 as it is broken out by the ribbon cable. */

    // To set pin PA5 to Alternate Function 1, connecting it to TIM2_CH1, the PWM output.
    pinModeGPIOA(5, GPIO_ALT);

    // Set which alternate function is connected – GPIOA_AFRL[23:20] to 0001 for AF1
    GPIOA->AFRL &= (~(0b1111<<20));     // Clear all bits
    GPIOA->AFRL |= (0b0001<<20);        // Set bits to AF1

    /* Select the type, pull-up/pull-down, and output speed respectively via GPIOA_OTYPER, GPIOA_PUPDR, GPIOA_OSPEEDER */
    // Make sure pin 5 is in push-pull configuration
    GPIOA->OTYPER &= (~(0b1<<5));

    // Set speed to low because that seems okay? GPIOA_OSPEEDR[11:10] clear to 00
    GPIOA->OSPEEDR &= (~(0b11<<10));

    // PWM should be setting our output, so turn off pin 5 PU and PD res's. GPIOA_PUPDR[11:10] clear to 00
    GPIOA->PUPDR &= (~(0b11<<10));
}


////////////////////////  GPIO A Function Bank  /////////////////////////////

void pinModeGPIOA(int pin, int function) {
    switch(function) {
        case GPIO_INPUT:
            GPIOA->MODER &= ~(0b11 << 2*pin);
            break;
        case GPIO_OUTPUT:
            GPIOA->MODER |= (0b1 << 2*pin);
            GPIOA->MODER &= ~(0b1 << (2*pin+1));
            break;
        case GPIO_ALT:
            GPIOA->MODER &= ~(0b1 << 2*pin);
            GPIOA->MODER |= (0b1 << (2*pin+1));
            break;
        case GPIO_ANALOG:
            GPIOA->MODER |= (0b11 << 2*pin);
            break;
    }
}

int digitalReadGPIOA(int pin) {
    return ((GPIOA->IDR) >> pin) & 1;
}

void digitalWriteGPIOA(int pin, int val) {
    GPIOA->ODR |= (1 << pin);
}

void togglePinGPIOA(int pin) {
    // Use XOR to toggle
    GPIOA->ODR ^= (1 << pin);
}

////////////////////////  GPIO B Function Bank  /////////////////////////////

void pinModeGPIOB(int pin, int function) {
    switch(function) {
        case GPIO_INPUT:
            GPIOB->MODER &= ~(0b11 << 2*pin);
            break;
        case GPIO_OUTPUT:
            GPIOB->MODER |= (0b1 << 2*pin);
            GPIOB->MODER &= ~(0b1 << (2*pin+1));
            break;
        case GPIO_ALT:
            GPIOB->MODER &= ~(0b1 << 2*pin);
            GPIOB->MODER |= (0b1 << (2*pin+1));
            break;
        case GPIO_ANALOG:
            GPIOB->MODER |= (0b11 << 2*pin);
            break;
    }
}

int digitalReadGPIOB(int pin) {
    return ((GPIOB->IDR) >> pin) & 1;
}

void digitalWriteGPIOB(int pin, int val) {
    GPIOB->ODR |= (1 << pin);
}

void togglePinGPIOB(int pin) {
    // Use XOR to toggle
    GPIOB->ODR ^= (1 << pin);
}