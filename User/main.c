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
	delay_init();	    	 //	  
	NVIC_Configuration(); 	 //
	TIM2_NVIC_Configuration(); 
	TIM2_Configuration();
	uart_init(115200);
	LED_GPIO_Config();
	IIC_Init();
	DAC_Configuration();
	PCF8576_Ini(MODE_E,NOGLITTER);
	delay_ms(300);	
	LCD_DisAll();
	delay_ms(1000);	
	LCD_DisClear();
	DAC_Voltage_OutPut(1.5);
	
	SensorTypeCheck();
	
//	uCurrentSensor = 1;
	time_enable = 1;
	time_count_num = 100;
	
	dis_time_enable = 1;
	dis_time_count =0 ;
	while(1)
	{	
		GP_CommProcess();
		//display
		if(dis_renew == 0)
		{
			LCD_DisLELValue(ulCH4LELValue);
		}
		else if(dis_renew == 1)
		{
			LCD_DisPPMValue(ulCH4PPMValue);
		}
			
	}
}
