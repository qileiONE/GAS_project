#include <stm32f10x.h>
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "exti.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_dma.h"
#include "string.h"
#include "led.h"
#include "comm.h"
#include "gpio.h"
#include "dis.h"
#include "IIC.h"
#include "dac.h"

int main()
{
	unsigned char i;
	unsigned long shuzi = 9999;
	delay_init();	    	 //	  
	NVIC_Configuration(); 	 //
	TIM2_NVIC_Configuration(); 
	TIM2_Configuration(); 		
	//uart3_init(9600);
	LED_GPIO_Config();
	IIC_Init();
	DAC_Configuration();
	PCF8576_Ini(MODE_E,NOGLITTER);
	delay_ms(300);	
	LCD_DisAll();
	delay_ms(1000);	
	LCD_DisClear();
	LCD_DisPPM();
	DAC_Voltage_OutPut(1.5);
	while(1)
	{
		
	}
}
