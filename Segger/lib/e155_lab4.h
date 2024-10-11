/* 
// e155_lab4.h

This file acts as a single consolidation header, calling all the
relevant .h and .c files to be included in the main.c file for
lab4. Jackson Philion, jphilion@g.hmc.edu, Oct.10.2024
For Harvey Mudd College, E155, Professor Joshua Brake */

// Note that only the .c files are included, as they each #include their own .h

#include "STM32L432KC_FLASH.c"

#include "STM32L432KC_GPIO.c"

#include "STM32L432KC_RCC.c"

#include "STM32L432KC_TIM.c"
