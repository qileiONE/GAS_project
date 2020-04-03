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
/* TIM2中断优先级配置 */
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

/*中断周期为10ms*/
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period=10000;	//自动重装载寄存器周期的值(计数值) 
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler= (24 - 1);	//时钟预分频数 24M/24      
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式 
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);	// 清除溢出中断标志 
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);	// 开启时钟    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);	//先关闭等待使用  
	START_TIME;
}	 
void TIM2_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)//是更新中断
	{	 			   
		//USART_RX_STA|=1<<15;	//标记接收完成
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIM7更新中断标志    
		//TIM_Cmd(TIM2, DISABLE);  //关闭TIM7 
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



