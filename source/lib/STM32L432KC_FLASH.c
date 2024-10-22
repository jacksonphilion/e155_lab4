// STM32L432KC_FLASH.c
// Source code for FLASH functions
// See main.c for more

#include "STM32L432KC_FLASH.h"

void configureFlash() {
    FLASH->ACR |= (0b100); // Set to 4 waitstates
    FLASH->ACR |= (1 << 8); // Turn on the ART
}