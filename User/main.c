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

void SystemInit11(void)
{
	RCC->CR |= (uint32_t)0x00000001;
	RCC->CFGR |= (uint32_t)RCC_CFGR_PLLSRC_HSI_Div2;
	RCC->CFGR |= (uint32_t)RCC_CFGR_PLLMULL6;
	RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
	RCC->CR |= RCC_CR_PLLON;

	while((RCC->CR & RCC_CR_PLLRDY) == 0)
	{
	
	}
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
	RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
	{
		
	}
}

int main()
{
	SystemInit11();
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
	
	//SensorTypeCheck();
	LED_Warn(LED_OFF);
	
	GP_LEL2Current(0);
	uCurrentSensor = 1;
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
		//	RELAY_WARN(ON);
			RELAY_DOWN(OFF);
		}
		else if(ulCH4LELValue > LOWER_LIMIT*10)
		{
			RELAY_DOWN(ON);
	//		RELAY_WARN(OFF);
			RELAY_UP(OFF);
		}
		else 
		{
			RELAY_UP(OFF);
	//		RELAY_WARN(OFF);
			RELAY_DOWN(OFF);
		}
		
		if(ulCH4LELValue > WARN_LIMIT*10)
		{
			RELAY_WARN(ON);
		}
		else
		{
			RELAY_WARN(OFF);
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
