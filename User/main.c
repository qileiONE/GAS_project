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

int main()
{
	unsigned char i;
	unsigned char none_disp[21] = {0};           // 
	unsigned char all_disp[21] = {0};
	const unsigned char  screen1[]=  {0xff,0xf0,0x00,0x00,0x08,0x08,0x0f,0x38,0x08,0x00,0x00, 0x08,0x08,0x00,0x00,0x0f,0xf0,0x0f,0x00,0x00,0x00 };
	delay_init();	    	 //	  
	NVIC_Configuration(); 	 //
	TIM2_NVIC_Configuration(); 
	TIM2_Configuration(); 		
	//uart3_init(9600);
	LED_GPIO_Config();
	IIC_Init();
	PCF8576_Ini(MODE_E,NOGLITTER);
	
	for(i=0; i<20; i++)   
  	{ 
  		all_disp[i]=0xff; 
		none_disp[i] = 0x00;
  	}   
	PCF8576_Disp(0x00, all_disp, 20);
	delay_ms(500);
	//PCF8576_Disp(0x00, none_disp, 20);
	delay_ms(200);




	delay_ms(300);	
	while(1)
	{
			LED_Warn(ON);
//			PCF8576_Disp(0x00, none_disp, 20);
//			PCF8576_Point(ucUPdatapos[2], ucUPdatacode[2]);
//			PCF8576_Point(ucUPdatapos[3], ucUPdatacode[3]);	
//		//	PCF8576_Point(ucUPpointpos[8],ucUPpointcode[8]);
//			PCF8576_Point(ucUPdatapos[4], ucUPdatacode[6]);
			
			delay_ms(1000);
			PCF8576_Disp(0x00, none_disp, 20);
			LED_Warn(OFF);
//			PCF8576_Point(ucUPdatapos[0], ucUPdatacode[1]);
//			PCF8576_Point(ucUPdatapos[1], ucUPdatacode[1]);	
//			PCF8576_Point(ucUPdatapos[2], ucUPdatacode[8]);	
//			PCF8576_Point(ucUPdatapos[3], ucUPdatacode[0]);
//			PCF8576_Point(ucUPdatapos[4], ucUPdatacode[0]);	
			//DIS_PPM();
			delay_ms(1000);
		
			
	}
}
