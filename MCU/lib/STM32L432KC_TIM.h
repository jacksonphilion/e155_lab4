/*********************************************************************

Jackson Philion, Oct.7.2024, jphilion@g.hmc.edu
For E155 Lab 4, Harvey Mudd College, taught by Prof Josh Brake.

This file and 

*********************************************************************/

/*
We need to set the:
• Counter Register (TIMx_CNT)
• Prescaler Register (TIMx_PSC)
• Auto-Reload Register (TIMx_ARR)
• Counter Enable – CEN in the TIMx_CR1 register, Bit 0 (1 to enable, 0 to disable)
• Disable Shadow Buffer – (ARPE) in the TIMx_CR1 register, Bit 7 (0 to disable buffer)
*/

#include <stdint.h>

#define __IO volatile

#define TIM2_BASE (0x40000000UL)

#define TIM6_BASE (0x40001000UL)

typedef struct
{
    __IO uint32_t CR1;          /*!< TIM 2 Control Register 1,              Address offset: 0x00 */
    __IO uint32_t CR2;          /*!< TIM 2 Control Register 2,              Address offset: 0x04 */
    __IO uint32_t SMCR;         /*!< TIM 2 Slave Mode Control Register,     Address offset: 0x08 */
    __IO uint32_t DIER;         /*!< TIM 2 DMA Interrupt Enable,            Address offset: 0x0C */
    __IO uint32_t SR;           /*!< TIM 2 Status Register,                 Address offset: 0x10 */
    __IO uint32_t EGR;          /*!< TIM 2 Event Generation Register,       Address offset: 0x14 */
    __IO uint32_t CCMR1;        /*!< TIM 2 Capture Compare Mode Register 1, Address offset: 0x18 */
    __IO uint32_t CCMR2;        /*!< TIM 2 Capture Compare Mode Register 2, Address offset: 0x1C */
    __IO uint32_t CCER;         /*!< TIM 2 Capture Compare Enable Register, Address offset: 0x20 */
    __IO uint32_t CNT;          /*!< TIM 2 Counter,                         Address offset: 0x24 */
    __IO uint32_t PSC;          /*!< TIM 2 Prescaler,                       Address offset: 0x28 */
    __IO uint32_t ARR;          /*!< TIM 2 Auto-Reload Register,            Address offset: 0x2C */
    uint32_t      Reserved;     /*!< Reserved,                              Address offset: 0x30 */
    __IO uint32_t CCR1;         /*!< TIM 2 Capture Compare Register 1,      Address offset: 0x34 */
    __IO uint32_t CCR2;         /*!< TIM 2 Capture Compare Register 2,      Address offset: 0x38 */
    __IO uint32_t CCR3;         /*!< TIM 2 Capture Compare Register 3,      Address offset: 0x3C */
    __IO uint32_t CCR4;         /*!< TIM 2 Capture Compare Register  4,     Address offset: 0x40 */
    uint32_t      Reserved;     /*!< Reserved,                              Address offset: 0x44 */
    __IO uint32_t DCR;          /*!< TIM 2 DMA Control Register,            Address offset: 0x48 */
    __IO uint32_t DMAR;         /*!< TIM 2 DMA Address for full transfer,   Address offset: 0x4C */
    __IO uint32_t OR1;          /*!< TIM 2 Option Register 1,               Address offset: 0x50 */
    uint32_t      Reserved;     /*!< Reserved,                              Address offset: 0x54 */
    uint32_t      Reserved;     /*!< Reserved,                              Address offset: 0x58 */
    uint32_t      Reserved;     /*!< Reserved,                              Address offset: 0x5C */
    __IO uint32_t OR2;          /*!< TIM 2 Option Register 2,               Address offset: 0x60 */
} TIM2_TypeDef;

typedef struct
{
    __IO uint32_t CR1;     /*!< TIM 6 Control Register 1,          Address offset: 0x00 */
    __IO uint32_t CR2;     /*!< TIM 6 Control Register 2,          Address offset: 0x04 */
    uint32_t      Reserved;     /*!< Reserved,                          Address offset: 0x08 */
    __IO uint32_t DIER;    /*!< TIM 6 DMA Interrupt Enable,        Address offset: 0x0C */
    __IO uint32_t SR;      /*!< TIM 6 Status Register,             Address offset: 0x10 */
    __IO uint32_t EGR;     /*!< TIM 6 Event Generation Register,   Address offset: 0x14 */
    uint32_t      Reserved;     /*!< Reserved,                          Address offset: 0x18 */
    uint32_t      Reserved;     /*!< Reserved,                          Address offset: 0x1C */
    uint32_t      Reserved;     /*!< Reserved,                          Address offset: 0x20 */
    __IO uint32_t CNT;     /*!< TIM 6 Counter,                     Address offset: 0x24 */
    __IO uint32_t PSC;     /*!< TIM 6 Prescaler,                   Address offset: 0x28 */
    __IO uint32_t ARR;     /*!< TIM 6 Auto-Reload Register,        Address offset: 0x2C */
} TIM6_TypeDef;

#define TIM2 ((TIM2_TypeDef *) TIM2_BASE)

#define TIM6 ((TIM6_TypeDef *) TIM6_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void initTIM6(); 
void initTIM2_PWM(uint32_t freq); 
void delayMillis(uint32_t ms);
void playNote(uint32_t freq);