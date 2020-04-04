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

#define	KEY_VALUE_RESET			0x31							//
#define	KEY_VALUE_ZARO			0x32							//

#define SET_KEY_RESET()			 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)			//PA7	
#define SET_KEY_ZERO()			 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)			//PB0


extern u8  key_bit;
extern u8  key_value ;
extern u8  last_key_value;
extern u8  key_value_ok ;
extern u16  key_count ;
extern u16  key_time_5s_count ;
extern vu8  key_time_5s_bit ;
extern u8 	 key_res;

void Key_GPIO_Config(void);
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);
u8 Get_Key_Process( void );
void Key_Process(void);

#endif /* __LED_H */

