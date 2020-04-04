
#include "key.h" 
#include "comm.h"
#include "timer.h"
#include "dis.h"

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
	//PA7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //�˿�����Ϊ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//��ʼ���˿�

	//PB0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //�˿�����Ϊ��������
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
	//if( SET_KEY_ZERO( ) == 0){	  
	//	return KEY_VALUE_ZARO;
	//}	
	return 0xff;	
}

void Key_Process(void)
{
	unsigned char i;
	i = Get_Key_Process();
	
	if( key_value_ok == 0xff )return ;
	if( key_value_ok == KEY_VALUE_RESET )
	{
		GP_SensorSet(S_RESET);
	}
	if( key_value_ok == KEY_VALUE_ZARO )
	{
		GP_SensorSet(S_ZERO);
	}
	if(key_time_5s_bit == 1)
	{
		LCD_DisAll();
		GP_SensorSet(S_CORRECT);
		key_time_5s_bit = 0;
		LCD_DisClear();
	}
}

