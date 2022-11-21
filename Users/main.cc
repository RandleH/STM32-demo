#include <stdio.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C"{
#endif

static inline bool isLittleEndian(void){
    int x = 1;
    return (*((char*)&x))==1;
}



#ifdef __cplusplus
}
#endif

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "rh_clock.hpp"
#include "rh_timer.hpp"

int main( int argc, char const *argv[]){

  // rh_clock__init();
   
  rh_clock__view();
  /* Configure C13 pin(PC13) in output function */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 
   
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  
  RCC_ClocksTypeDef clk_info;
  RCC_GetClocksFreq( &clk_info);

  rh_timer2__init();
  
  while(1){
    
  }


}



