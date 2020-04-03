//#include "stm32f10x.h"
#include "timer.h"
#include "usart.h"
#include "exti.h"
u16 time_count=0;
u16 time_count_num = 0;
u16	time_end_flag = 0;
u16	time_enable = 0;

u16 dis_time_count = 0;
u16 dis_time_enable = 0;
u16 dis_renew = 0; //0 LEL  1 ppm

u16 res_time_count = 0;
u16 res_time_enable = 0;
u16 res_end_flag = 0; 

u8 Rev_end_flag = FALSE;
/* TIM2�ж����ȼ����� */
void TIM2_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*�ж�����Ϊ10ms*/
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period=10000;	//�Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) 
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
    TIM_TimeBaseStructure.TIM_Prescaler= (24 - 1);	//ʱ��Ԥ��Ƶ�� 24M/24      
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ 
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);	// �������жϱ�־ 
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);	// ����ʱ��    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);	//�ȹرյȴ�ʹ��  
	START_TIME;
}	 
void TIM2_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)//�Ǹ����ж�
	{	 			   
		//USART_RX_STA|=1<<15;	//��ǽ������
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIM7�����жϱ�־    
		//TIM_Cmd(TIM2, DISABLE);  //�ر�TIM7 
		dis_time_count++;
		time_count++;
		if(time_enable == 1)
		{
			if(time_count >= time_count_num)
			{
				time_end_flag = 1;
				time_enable = 0;
			//	time_count = 0;
			}
		}
		if(dis_time_enable == 1)
		{
			if((dis_time_count >=(DIS_TIME/10))&& (dis_time_count < (DIS_TIME/10)*2))
			{
				dis_renew = 0;
			}
			if(dis_time_count > ((DIS_TIME/10)*2))
			{
				dis_renew = 1;
				dis_time_count = 0;
			}
		}
		if(res_time_enable == 1)
		{
			res_time_count ++;
			if(res_time_count >= (RESPONSE_TIME/10))
			{
				res_end_flag = 1;
				res_time_enable = 0;
				res_time_count = 0;
			}
			
		}
	}	    
}



