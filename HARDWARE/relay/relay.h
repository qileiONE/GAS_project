#ifndef __RELAY_H
#define	__RELAY_H

#include "sys.h"

#define RELAY_Pin_WARN 					GPIO_Pin_5
#define RELAY_GPIO_Port_WARN 				GPIOB

#define RELAY_Pin_UP 					GPIO_Pin_3
#define RELAY_GPIO_Port_UP 				GPIOB


#define RELAY_Pin_DOWN 					GPIO_Pin_4
#define RELAY_GPIO_Port_DOWN 				GPIOB

#define ON  1
#define OFF 0

#define RELAY_WARN(a)	if (a)	\
					GPIO_SetBits(RELAY_GPIO_Port_WARN,RELAY_Pin_WARN);\
					else		\
					GPIO_ResetBits(RELAY_GPIO_Port_WARN,RELAY_Pin_WARN)
					
#define RELAY_UP(a)	if (a)	\
					GPIO_SetBits(RELAY_GPIO_Port_UP,RELAY_Pin_UP);\
					else		\
					GPIO_ResetBits(RELAY_GPIO_Port_UP,RELAY_Pin_UP)
					
#define RELAY_DOWN(a)	if (a)	\
					GPIO_SetBits(RELAY_GPIO_Port_DOWN,RELAY_Pin_DOWN);\
					else		\
					GPIO_ResetBits(RELAY_GPIO_Port_DOWN,RELAY_Pin_DOWN)					


					
void RELAY_GPIO_Config(void);
					
#endif




