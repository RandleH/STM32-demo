  /*
  *=============================================================================
  *=============================================================================
  *                    Supported STM32F40xxx/41xxx devices
  *-----------------------------------------------------------------------------
  *        System Clock source                    | PLL (HSE)
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                             | 168000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                               | 168000000
  *-----------------------------------------------------------------------------
  *        AHB Prescaler                          | 1
  *-----------------------------------------------------------------------------
  *        APB1 Prescaler                         | 4
  *-----------------------------------------------------------------------------
  *        APB2 Prescaler                         | 2
  *-----------------------------------------------------------------------------
  *        HSE Frequency(Hz)                      | 25000000
  *-----------------------------------------------------------------------------
  *        PLL_M                                  | 25
  *-----------------------------------------------------------------------------
  *        PLL_N                                  | 336
  *-----------------------------------------------------------------------------
  *        PLL_P                                  | 2
  *-----------------------------------------------------------------------------
  *        PLL_Q                                  | 7
  *-----------------------------------------------------------------------------
  *        PLLI2S_N                               | NA
  *-----------------------------------------------------------------------------
  *        PLLI2S_R                               | NA
  *-----------------------------------------------------------------------------
  *        I2S input clock                        | NA
  *-----------------------------------------------------------------------------
  *        VDD(V)                                 | 3.3
  *-----------------------------------------------------------------------------
  *        Main regulator output voltage          | Scale1 mode
  *-----------------------------------------------------------------------------
  *        Flash Latency(WS)                      | 5
  *-----------------------------------------------------------------------------
  *        Prefetch Buffer                        | ON
  *-----------------------------------------------------------------------------
  *        Instruction cache                      | ON
  *-----------------------------------------------------------------------------
  *        Data cache                             | ON
  *-----------------------------------------------------------------------------
  *        Require 48MHz for USB OTG FS,          | Disabled
  *        SDIO and RNG clock                     |
  *-----------------------------------------------------------------------------
  *=============================================================================
  */

#include "stm32f4xx.h"

void rh_clock__init(void){
  // Reset Clock
  RCC->CR |= RCC_CR_HSION;
  while( false==(RCC->CR & RCC_CR_HSIRDY) ){}
  RCC->CFGR     = (uint32_t)0x00000000;
  RCC->CR      &= (uint32_t)0xFEF6FFFF;
  RCC->PLLCFGR  = (uint32_t)0x24003010;
  RCC->CR      &= (uint32_t)0xFFFBFFFF;
  RCC->CIR      = (uint32_t)0x00000000;


  // RCC clock control register
  RCC->CR |= RCC_CR_HSEON;
  while( false==(RCC->CR & RCC_CR_HSERDY) ){}



  RCC->CR = ...;  // RCC_CR_PLLI2SON  Disable   ; PLLI2S enable 
  RCC->CR = ...;  // RCC_CR_PLLON     Enable    ; Main PLL (PLL) enable
  RCC->CR = ...;  // RCC_CR_CSSON     Enable    ; Clock security system enable
  RCC->CR = ...;  // RCC_CR_HSEBYP              ; HSE clock bypass
  RCC->CR = ...;  // RCC_CR_HSEON               ; HSE clock enable
  RCC->CR = ...;  // RCC_CR_HSION     Disable

  // RCC PLL configuration register
  union{
    struct{
      uint32_t reserved31_28 : 4;
      uint32_t PLLQ          : 4;
      uint32_t reserved23    : 1;
      uint32_t PLLSRC        : 1;
      uint32_t reserved21_18 : 4;
      uint32_t PLLP          : 2;
      uint32_t reserved15    : 1;
      uint32_t PLLN          : 9;
      uint32_t PLLM          : 6;
    }bit;
    uint32_t data;
  }PLLCFGR;
  PLLCFGR = RCC->PLLCFGR;
  


  RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;  // RCC_PLLCFGR_PLLSRC  ; HSE oscillator clock selected as PLL and PLLI2S clock entry
  static uint32_t PLL_N = 200U;
  static uint32_t PLL_M = 25U;
  static uint32_t PLL_P = 1U;
  RCC->PLLCFGR 

  // RCC clock configuration register
  RCC->CFGR       // RCC_CFGR_SW                ; PLL selected as system clock

  // RCC clock interrupt register

  // RCC Backup domain control register

  // RCC clock control & status register

  // RCC spread spectrum clock generation register
  
  // RCC PLLI2S configuration register 

  // RCC Dedicated Clocks Configuration Register
}


