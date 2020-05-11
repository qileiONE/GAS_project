
#include "key.h" 
#include "comm.h"
#include "timer.h"
#include "dis.h"
#include "led.h"
#include "delay.h"

 /*����ȷ����ʱ */
 void Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
} 

 /*	 ���ð����õ���I/O�� */
void Key_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE); //���������˿�PA��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	//PA7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //�˿�����Ϊ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//��ʼ���˿�
	
	//PB0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //�˿�����Ϊ��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);	//��ʼ���˿�
	
	
	key_bit = 0;
  key_value = 0x00;
  last_key_value = 0x00;
  key_value_ok = 0x00;
  key_count = 0;
	
}

 /* ����Ƿ��а������� */
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
		/*����Ƿ��а������� */
   	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	  {	   
	 	 /*��ʱ����*/
	  	Delay(5000);		
	   		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
					{	 
						/*�ȴ������ͷ� */
						while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
			 			return 	KEY_ON;	 
					}
			else
					return KEY_OFF;
		}
	else
		return KEY_OFF;
}


u8 Get_Key_Process( void )
{	
	if( SET_KEY_RESET( ) == 0 ){	  
		return KEY_VALUE_RESET;
	}	
	if( SET_KEY_ZERO( ) == 0){	  
		return KEY_VALUE_ZARO;
	}	
	return 0xff;	
}

void Key_Process(void)
{
	if( key_value_ok == 0xff )return ;
	if( key_value_ok == KEY_VALUE_RESET )
	{
		LED_Warn(LED_ON);
		GP_SensorSet(S_RESET);
		delay_ms(500);
		LED_Warn(LED_OFF);
	}
	if( key_value_ok == KEY_VALUE_ZARO && SET_KEY_ZERO( ) != 0 && key_time_5s_bit == 0)
	{
		LED_Warn(LED_ON);
		GP_SensorSet(S_ZERO);
		delay_ms(500);
		LED_Warn(LED_OFF);
	}
	if(key_time_5s_bit == 1)
	{
		LED_Warn(LED_ON);
		LCD_DisAll();
		GP_SensorSet(S_CORRECT);//S_ZERO
		key_time_5s_bit = 0;
		LCD_DisClear();
		delay_ms(500);
		LED_Warn(LED_OFF);
	}
	
	key_value_ok = 0xff;
}

