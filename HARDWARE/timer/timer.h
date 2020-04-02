#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
#include "config.h"

#define START_TIME  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);TIM_Cmd(TIM4, ENABLE)
#define STOP_TIME  TIM_Cmd(TIM4, DISABLE);RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , DISABLE)

////////////////////////////////////////////////////////////////////////////////// 	
extern void TIM2_NVIC_Configuration(void); /* TIM2 ∂® ±≈‰÷√ */
extern void TIM2_Configuration(void); 
//void TIM7_Int_Init(u16 arr,u16 psc);
#endif
