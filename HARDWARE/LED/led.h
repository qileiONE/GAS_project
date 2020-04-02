#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"
#include "config.h"


#define LED_Pin_Working 					GPIO_Pin_8
#define LED_GPIO_Port_Working 				GPIOB

#define LED_Pin_Warn 					GPIO_Pin_5
#define LED_GPIO_Port_Warn 				GPIOB

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define ON  1
#define OFF 0

#define LED_Working(a)	if (a)	\
					GPIO_SetBits(LED_GPIO_Port_Working,LED_Pin_Working);\
					else		\
					GPIO_ResetBits(LED_GPIO_Port_Working,LED_Pin_Working)
					
#define LED_Warn(a)	if (a)	\
					GPIO_SetBits(LED_GPIO_Port_Warn,LED_Pin_Warn);\
					else		\
					GPIO_ResetBits(LED_GPIO_Port_Warn,LED_Pin_Warn)


void LED_GPIO_Config(void);

#endif /* __LED_H */
