#include "gpio.h"

void GP_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	// Enable GPIO clock
	RCC_GPIOA_CLK_ENABLE();
//	RCC_GPIOB_CLK_ENABLE();
//	RCC_GPIOC_CLK_ENABLE();
//	RCC_GPIOD_CLK_ENBALE();
//	RCC_GPIOE_CLK_ENABLE();	

   	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);

	//WARNING 
	GPIO_InitStructure.GPIO_Pin = WARNING_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(WARNING_GPIO_Port, &GPIO_InitStructure); 
	 
	GPIO_ResetBits(WARNING_GPIO_Port, WARNING_Pin);

}

void Warning_alarm_ON(void)
{
	 GPIO_SetBits(WARNING_GPIO_Port, WARNING_Pin);
}

void Warning_alarm_OFF(void)
{
	GPIO_ResetBits(WARNING_GPIO_Port, WARNING_Pin);
}


void GP_OLED_GPIO_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	//OLED
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOD3,6

} 



