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
#include "key.h"
#include "relay.h"


int main()
{
	delay_init();	    	 //	  
	NVIC_Configuration(); 	 //
	TIM2_NVIC_Configuration(); 
	TIM2_Configuration();
	uart_init(115200);
//	GP_CommProcess();
	LED_GPIO_Config();
	IIC_Init();
	DAC_Configuration();
	Key_GPIO_Config();
	RELAY_GPIO_Config();
	PCF8576_Ini(MODE_E,NOGLITTER);
	LED_Warn(LED_OFF);
	//delay_ms(300);	
	LCD_DisAll();
	delay_ms(500);	
	LCD_DisClear();
	//DAC_Voltage_OutPut(1.5);
	
	SensorTypeCheck();
	LED_Warn(LED_ON);
	
	GP_LEL2Current(0);
	//uCurrentSensor = 1;
//	time_enable = 1;
//	time_count_num = 100;
	
	dis_time_enable = 1;
	dis_time_count =0 ;

	key_value_ok = 0xff;
	
	ulCH4LELValue = 0;
	ulCH4PPMValue = 0;
	
	RELAY_UP(OFF);
	RELAY_WARN(OFF);
	RELAY_DOWN(OFF);
	while(1)
	{	
		GP_CommProcess();
		if(ulCH4LELValue >= UPPER_LIMIT*10)
		{
			RELAY_UP(ON);
			RELAY_WARN(ON);
		}
		else if(ulCH4LELValue < LOWER_LIMIT*10)
		{
			RELAY_DOWN(ON);
		}
		
		Key_Process();
		//GP_CommProcess();
		//display
		if(dis_renew == 0)
		{
			LCD_DisLELValue(ulCH4LELValue);
			GP_LEL2Current(ulCH4LELValue);
		}
		else if(dis_renew == 1)
		{
			LCD_DisPPMValue(ulCH4PPMValue);
		}
			
	}
}
