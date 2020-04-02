#ifndef __GPIO_H
#define	__GPIO_H

#include "stm32f10x.h"
#include "config.h"

#define WARNING_Pin 			GPIO_Pin_6
#define WARNING_GPIO_Port 		GPIOA

void GP_GPIO_Init(void);
void Warning_alarm_ON(void);
void Warning_alarm_OFF(void);

#endif /* __GPIO_H */


