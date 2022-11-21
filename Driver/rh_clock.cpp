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

#include "./rh_common.hpp"
#include "./rh_clock.hpp"

#ifdef __cplusplus
extern "C"{
#endif

typedef union{
  struct{
    uint32_t    HSION     : 1;
    uint32_t    HSIRDY    : 1;
    uint32_t    Reserved2 : 1;
    uint32_t    HSITRIM   : 5;
    uint32_t    HSICAL    : 8;
    uint32_t    HSEON     : 1;
    uint32_t    HSERDY    : 1;
    uint32_t    HSEBYP    : 1;
    uint32_t    CSSON     : 1;
    uint32_t    Reserved23_20 : 4;
    uint32_t    PLLON     : 1;
    uint32_t    PLLRDY    : 1;
    uint32_t    PLLI2SON  : 1;
    uint32_t    PLLI2SRDY : 1;
    uint32_t    Reserved31_28 : 4;
  }bit;
  uint32_t data;
}*RCC_CR;

typedef union{
  struct{
    uint32_t PLLM          : 6;
    uint32_t PLLN          : 9;
    uint32_t reserved15    : 1;
    uint32_t PLLP          : 2;
    uint32_t reserved21_18 : 4;
    uint32_t PLLSRC        : 1;
    uint32_t reserved23    : 1;
    uint32_t PLLQ          : 4;
    uint32_t reserved31_28 : 4;
  }bit;
  uint32_t data;
}*RCC_PLLCFGR;

typedef union{
  struct{
    uint32_t       SW          : 2;
    const uint32_t SWS         : 2;
    uint32_t       HPRE        : 4;
    uint32_t       reserved9_8 : 2;
    uint32_t       PPRE1       : 3;
    uint32_t       PPRE2       : 3;
    uint32_t       RTCPRE      : 5;
    uint32_t       MCO1        : 2;
    uint32_t       I2SSRC      : 1;
    uint32_t       MCO1PRE     : 3;
    uint32_t       MCO2PRE     : 3;
    uint32_t       MCO2        : 2;
  }bit;
  uint32_t data;
}*RCC_CFGR;

typedef union{
  struct{
    uint32_t   LSIRDYF         : 1;
    uint32_t   LSERDYF         : 1;
    uint32_t   HSIRDYF         : 1;
    uint32_t   HSERDYF         : 1;
    uint32_t   PLLRDYF         : 1;
    uint32_t   PLLI2SRDYF      : 1;
    uint32_t   Reserved6       : 1;
    uint32_t   CSSF            : 1;
    uint32_t   LSIRDYIE        : 1;
    uint32_t   LSERDYIE        : 1;
    uint32_t   HSIRDYIE        : 1;
    uint32_t   HSERDYIE        : 1;
    uint32_t   PLLRDYIE        : 1;
    uint32_t   PLLI2SRDYIE     : 1;
    uint32_t   Reserved15_14   : 2;
    uint32_t   LSIRDYC         : 1;
    uint32_t   LSERDYC         : 1;
    uint32_t   HSIRDYC         : 1;
    uint32_t   HSERDYC         : 1;
    uint32_t   PLLRDYC         : 1;
    uint32_t   PLLI2SRDYC      : 1;
    uint32_t   Reserved22      : 1;
    uint32_t   CSSC            : 1;
    uint32_t   Reserved31_24   : 8;
  }bit;
  uint32_t data;
}*RCC_CIR;

void rh_clock__view(void){
#if 0  
  RCC_CR       reg_cr      = (RCC_CR)&RCC->CR;
  RCC_PLLCFGR  reg_pllcfgr = (RCC_PLLCFGR)&RCC->PLLCFGR;
  RCC_CFGR     reg_cfgr    = (RCC_CFGR)&RCC->CFGR;
#else
  uint32_t tmp[3] = { 0x03037c83, 0x27405419, 0xff99100a };
  RCC_CR       reg_cr      = (RCC_CR)&tmp[0];
  RCC_PLLCFGR  reg_pllcfgr = (RCC_PLLCFGR)&tmp[1];
  RCC_CFGR     reg_cfgr    = (RCC_CFGR)&tmp[2];
#endif
}



void rh_clock__init(void){
  // Reset Clock
  SCB->CPACR   |= ((3UL << 10*2)|(3UL << 11*2));
  RCC->CR      |= (uint32_t)0x00000001;
  RCC->CFGR     = 0x00000000;
  RCC->CR      &= (uint32_t)0xFEF6FFFF;
  RCC->PLLCFGR  = 0x24003010;
  RCC->CR      &= (uint32_t)0xFFFBFFFF;
  RCC->CIR      = 0x00000000;

  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  PWR->CR      |= PWR_CR_VOS;


  {// RCC clock control register
    RCC_CR reg_ptr = (RCC_CR)(&(RCC->CR));
    reg_ptr->bit.HSEON  = 1;
    reg_ptr->bit.HSEBYP = 1;
    while(false==reg_ptr->bit.HSERDY);
  }
  
  {// RCC PLL configuration register
    RCC_PLLCFGR reg_ptr = (RCC_PLLCFGR)(&(RCC->PLLCFGR));
    reg_ptr->bit.PLLSRC = 1;       // Bit  22    PLLSRC   ; 1: HSE clock selected as PLL and PLLI2S clock entry
    reg_ptr->bit.PLLN   = 400U;    // Bits 14:6  PLLN     ; Main PLL (PLL) multiplication factor for VCO
    reg_ptr->bit.PLLM   = 25U;     // Bits 5:0   PLLM     ; Division factor for the main PLL (PLL) input clock
    reg_ptr->bit.PLLP   = 1U;      // Bits 17:16 PLLP     ; Main PLL (PLL) division factor for main system clock [01: PLLP = 4]
    reg_ptr->bit.PLLQ   = 8U;      // Bits 27:24 PLLQ     ; Main PLL (PLL) division factor for USB OTG FS, and SDIO clocks
  }

  {// RCC clock configuration register
    RCC_CFGR reg_ptr    =  (RCC_CFGR)(&(RCC->CFGR));       
    reg_ptr->bit.HPRE   = 0;       // Bits 7:4    HPRE        ; AHB prescaler                         [0xxx: system clock not divided]
    reg_ptr->bit.PPRE1  = 4;       // Bits 12:10  PPRE1       ; APB Low speed prescaler (APB1)        [100: AHB clock divided by 2]
    reg_ptr->bit.PPRE2  = 4;       // Bits 15:13  PPRE2       ; APB high-speed prescaler (APB2)       [0xx: AHB clock not divided]
    reg_ptr->bit.RTCPRE = 0;       // Bits 20:16  RTCPRE      ; HSE division factor for RTC clock     [11001: HSE/25 = 1MHz]
    reg_ptr->bit.MCO1   = 0;       // Bits 22:21  MCO1        ; Microcontroller clock output 1        [00: HSI clock selected]
    reg_ptr->bit.I2SSRC = 0;       // Bit  23     I2SSRC      ; I2S clock selection                   [1: External clock mapped on the I2S_CKIN pin]
    reg_ptr->bit.MCO1PRE= 0;       // Bits 26:24  MCO1PRE     ; MCO1 prescale                         [111: division by 5]
    reg_ptr->bit.MCO2PRE= 0;       // Bits 29:27  MCO1PRE     ; MCO2 prescale                         [111: division by 5]
    reg_ptr->bit.MCO2   = 0;       // Bits 31:30  MCO2[1:0]   ; Microcontroller clock output 2        [11: PLL clock selected]
  }

  {// RCC clock control register
    RCC_CR reg_ptr = (RCC_CR)(&(RCC->CR));
    reg_ptr->bit.PLLON = 1;
    while(false==reg_ptr->bit.PLLRDY);
  }

  FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_2WS;

  {// RCC clock configuration register
    RCC_CFGR reg_ptr    =  (RCC_CFGR)(&(RCC->CFGR));  
    reg_ptr->bit.SW     = 2;       // Bits 1:0    SW          ; System clock switch                   [10: PLL selected as system clock]
    while(2!=reg_ptr->bit.SWS);
  }
  

  {// RCC clock control register
    RCC_CR reg_ptr = (RCC_CR)(&(RCC->CR));
    reg_ptr->bit.CSSON  = 1;       // Bit 19     CSSON        ; Clock security system enable
  }

  

  // RCC Backup domain control register

  // RCC clock control & status register

  // RCC spread spectrum clock generation register
  
  // RCC PLLI2S configuration register 

  // RCC Dedicated Clocks Configuration Register



  
  SCB->VTOR = FLASH_BASE | 0x00;
}

#ifdef __cplusplus
}
#endif


#if 0

void rh_clock__init(void){
  // Reset Clock
  SCB->CPACR   |= ((3UL << 10*2)|(3UL << 11*2));
  RCC->CR      |= (uint32_t)0x00000001;
  RCC->CFGR     = 0x00000000;
  RCC->CR      &= (uint32_t)0xFEF6FFFF;
  RCC->PLLCFGR  = 0x24003010;
  RCC->CR      &= (uint32_t)0xFFFBFFFF;
  RCC->CIR      = 0x00000000;

  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  PWR->CR      |= PWR_CR_VOS;


  {// RCC clock control register
    // RCC_CR reg_ptr = (RCC_CR)(&(RCC->CR));
    // reg_ptr->bit.HSEON = 1;
    // while(false==reg_ptr->bit.HSERDY);
  }
  
  {// RCC PLL configuration register
    RCC_PLLCFGR reg_ptr = (RCC_PLLCFGR)(&(RCC->PLLCFGR));
    reg_ptr->bit.PLLSRC = 0;       // Bit  22    PLLSRC   ; 0: HSI clock selected as PLL and PLLI2S clock entry
    reg_ptr->bit.PLLN   = 400U;    // Bits 14:6  PLLN     ; Main PLL (PLL) multiplication factor for VCO
    reg_ptr->bit.PLLM   = 16U;     // Bits 5:0   PLLM     ; Division factor for the main PLL (PLL) input clock
    reg_ptr->bit.PLLP   = 1U;      // Bits 17:16 PLLP     ; Main PLL (PLL) division factor for main system clock [00: PLLP = 2]
    reg_ptr->bit.PLLQ   = 8U;      // Bits 27:24 PLLQ     ; Main PLL (PLL) division factor for USB OTG FS, and SDIO clocks
  }

  {// RCC clock configuration register
    RCC_CFGR reg_ptr    =  (RCC_CFGR)(&(RCC->CFGR));       
    reg_ptr->bit.HPRE   = 0;       // Bits 7:4    HPRE        ; AHB prescaler                         [0xxx: system clock not divided]
    reg_ptr->bit.PPRE1  = 4;       // Bits 12:10  PPRE1       ; APB Low speed prescaler (APB1)        [100: AHB clock divided by 2]
    reg_ptr->bit.PPRE2  = 0;       // Bits 15:13  PPRE2       ; APB high-speed prescaler (APB2)       [0xx: AHB clock not divided]
    reg_ptr->bit.RTCPRE = 0;       // Bits 20:16  RTCPRE      ; HSE division factor for RTC clock     [11001: HSE/25 = 1MHz]
    reg_ptr->bit.MCO1   = 0;       // Bits 22:21  MCO1        ; Microcontroller clock output 1        [00: HSI clock selected]
    reg_ptr->bit.I2SSRC = 0;       // Bit  23     I2SSRC      ; I2S clock selection                   [1: External clock mapped on the I2S_CKIN pin]
    reg_ptr->bit.MCO1PRE= 0;       // Bits 26:24  MCO1PRE     ; MCO1 prescale                         [111: division by 5]
    reg_ptr->bit.MCO2PRE= 0;       // Bits 29:27  MCO1PRE     ; MCO2 prescale                         [111: division by 5]
    reg_ptr->bit.MCO2   = 0;       // Bits 31:30 MCO2[1:0]    ; Microcontroller clock output 2            [11: PLL clock selected]
  }

  {// RCC clock control register
    RCC_CR reg_ptr = (RCC_CR)(&(RCC->CR));
    reg_ptr->bit.PLLON = 1;
    while(false==reg_ptr->bit.PLLRDY);
  }

  FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_2WS;

  {// RCC clock configuration register
    RCC_CFGR reg_ptr    =  (RCC_CFGR)(&(RCC->CFGR));  
    reg_ptr->bit.SW     = 2;       // Bits 1:0    SW          ; System clock switch                   [10: PLL selected as system clock]
    while(2!=reg_ptr->bit.SWS);
  }
  
  RCC_PLLCFGR reg_ptr = (RCC_PLLCFGR)(&(RCC->PLLCFGR));

  // RCC clock interrupt register

  // RCC Backup domain control register

  // RCC clock control & status register

  // RCC spread spectrum clock generation register
  
  // RCC PLLI2S configuration register 

  // RCC Dedicated Clocks Configuration Register



  
  SCB->VTOR = FLASH_BASE | 0x00;
}

#endif