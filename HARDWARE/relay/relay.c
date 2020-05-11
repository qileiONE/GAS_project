#include "relay.h"

void RELAY_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); // ʹ��PB�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = RELAY_Pin_UP | RELAY_Pin_DOWN;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PC�˿�
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // ʹ��PB�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = RELAY_Pin_WARN;//RELAY_Pin_WARN;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(RELAY_GPIO_Port_WARN, &GPIO_InitStructure);  //��ʼ��PC�˿�
	
	GPIO_ResetBits(RELAY_GPIO_Port_WARN, RELAY_Pin_WARN);	
  GPIO_ResetBits(RELAY_GPIO_Port_UP, RELAY_Pin_UP);	 // 
  GPIO_ResetBits(RELAY_GPIO_Port_DOWN, RELAY_Pin_DOWN);	 //
}


