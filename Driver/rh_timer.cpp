


#include "misc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#ifdef __cplusplus
extern "C"{
#endif

void rh_timer2__init(void){
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  
  NVIC_InitTypeDef nvic_config;
  nvic_config.NVIC_IRQChannel = TIM2_IRQn;
  nvic_config.NVIC_IRQChannelPreemptionPriority = 3;
  nvic_config.NVIC_IRQChannelSubPriority = 3;
  nvic_config.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init( &nvic_config);
  
  TIM_TimeBaseInitTypeDef  config;
  // Fclk         = 15MHz
  // 15MHz / 15000 = 1KHz
  config.TIM_Period            = 10000-1;
  config.TIM_CounterMode       = TIM_CounterMode_Up;
  config.TIM_Prescaler         = 10000-1;
  config.TIM_ClockDivision     = TIM_CKD_DIV1;
  config.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit( TIM2, &config);
  
  TIM_ITConfig( TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd( TIM2, ENABLE);
    
  
            
}


void TIM2_IRQHandler(void){
  if( RESET!=TIM_GetITStatus( TIM2, TIM_IT_Update)){
    TIM_ClearITPendingBit( TIM2, TIM_IT_Update);  
    GPIO_ToggleBits( GPIOC, GPIO_Pin_13);
  }

}


#ifdef __cplusplus
}
#endif