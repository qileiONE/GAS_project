#ifndef __KEY_H
#define	__KEY_H

#include "stm32f10x.h"
 /*******
 *按键按下标置
 KEY_ON 0
 KEY_OFF 1
 ********/
#define KEY_ON	0
#define KEY_OFF	1

#define SET_KEY_UP()			( GPIOA->IDR & 0x0040 )			//PA7	
#define SET_KEY_DOWN()			( GPIOB->IDR & 0x0000 )			//PB0

void Key_GPIO_Config(void);
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);

#endif /* __LED_H */

