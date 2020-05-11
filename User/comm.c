#include "comm.h"
#include "usart.h"
#include "config.h"
#include "timer.h"
#include "string.h"
#include "delay.h"
#include "dac.h"

u8 uCurrentSensor;  //
u8 uRevNumCount = 0; //
unsigned long ulCH4LELValue = 0;  //%LEL    放大10倍的数值
unsigned long ulCH4PPMValue = 0;  //PPM

//SUS316L
char ucSU_ZeroAd_Command[] = {0x3a,0x31,0x00,0x00,0x31,0x0d,0x0a};
char ucSU_Correct_Command[] = {0x3a,0x33,0x01,0x90,0xc4,0x0d,0x0a}; //40% {0x3a,0x33,0x00,0x1e,0xc4,0x0d,0x0a}; //3%
char ucSU_Reset_Command[] = {0x3a,0x35,0x00,0x00,0x35,0x0d,0x0a};

char ucSU_ZeroRev_data[] ={0x3a,0x32,0x31,0x63,0x0d,0x0a};
char ucSU_CorrectRev_data[] ={0x3a,0x34,0x31,0x65,0x0d,0x0a}; 
char ucSU_ResetRev_data[] ={0x3a,0x36,0x31,0x67,0x0d,0x0a};

//MIPEX_03
char ucMI_MeasuredDataMau_Command[] = {0x40,0x0D};
char ucMI_MeasuredDataAuto_Command[] = {0x40,0x2A,0x34,0x0D};  //?5s = 1.32 * 4
char ucMI_ZeroAd_Command[]={0x5A,0x45,0x52,0x4F,0x32,0x0D};//ZERO2
char ucMI_Correct_Command[]={0x43,0x41,0x4C,0x42,0x20,0x34,0x30,0x30,0x30,0x0D};//CALB 4000
char ucMI_Reset_Command[] = {0x49,0x4E,0x49,0x54,0x0D};//INIT

u8 REV_BUF[USART_REC_LEN];     //

void SensorTypeCheck(void)
{
	unsigned char len ;
//	res_time_count = 0;
//	res_end_flag = 0;
//	res_time_enable = 1;
	
	//看看是不是SUS316L
	
	uart_init(115200);
	delay_ms(200);
	res_time_count = 0;
	res_end_flag = 0;
	res_time_enable = 1;
	while(res_end_flag == 0)
	{
		if(GP_CommArrange()==OK)
		{
			len = strlen((char*)REV_BUF);
			if(len >= 24 && len <= 31)  //用长度判断
			{
				uCurrentSensor = SUS316L;
				res_time_enable = 0;
				return;
			}
		}
	}
	uart_init(9600);
	delay_ms(200);
	res_time_count = 0;
	res_end_flag = 0;
	res_time_enable = 1;
	while(res_end_flag == 0)
	{
		len = strlen((char*)REV_BUF);
		if(len >= 2 && len <= 4 && REV_BUF[0]==0x40)  //用长度判断
			{
				uCurrentSensor = MIPEX_03;
				res_time_enable = 0;
				return;
			}
	}
	
	//什么都没检测到
	uart_init(115200);
}

BYTE GP_CommArrange(void)
{
	DWORD dwRevsize = 0;
	WORD i;
	dwRevsize = USART_RX_STA;
	if(USART_RX_STA&0X8000)		//
	{
		dwRevsize &= 0x0fff;
		for(i=0;i<dwRevsize+1;i++)	
		{
//			if(USART_RX_BUF[i] == 0x01)
//			{
//				for(j=0;j<dwRevsize+1;j++)
//				{
//					REV_BUF[j] = USART_RX_BUF[i+j]; 	
//				}
//				break;
//			}
//			if(i == dwRevsize-1)
//			{
//				USART_RX_STA = 0; //
//				return ERROR_OTHER;
//			}	
			REV_BUF[i] = USART_RX_BUF[i]; 
			USART_RX_BUF[i] = 0;
		}
		//

		//
		USART_RX_STA = 0; //
		return OK;
	}
	return FREE_STATE;
}

void GP_CommProcess(void)
{
//	WORD wLen;
	//BYTE ret;
	unsigned char numbit;
	unsigned char i;
	//WORD numvalue[10] = {0};
	if(GP_CommArrange()==OK)
	{
		switch(uCurrentSensor)
		{
			case SUS316L:
				ulCH4LELValue = 0;
//				for(i=0;i<5;i++)
//				{
//					if(REV_BUF[i] == 0x2E)
//					{
//						numbit = i;
//						break;
//					}
//				}
				ulCH4LELValue = (REV_BUF[1]-0x30)*1000+(REV_BUF[2]-0x30)*100+(REV_BUF[3]-0x30)*10+(REV_BUF[4+1]-0x30);
//				switch(numbit)
//				{
//					case 0:
//						ulCH4LELValue += REV_BUF[0+1]-0x30;
//					break;
//					case 1:
//						ulCH4LELValue = (REV_BUF[0]-0x30)*10+(REV_BUF[1+1]-0x30);
//					break;
//					case 2:
//						ulCH4LELValue = (REV_BUF[0]-0x30)*100+(REV_BUF[1]-0x30)*10+(REV_BUF[2+1]-0x30);
//					break;
//					case 3:
//						ulCH4LELValue = (REV_BUF[0]-0x30)*1000+(REV_BUF[1]-0x30)*100+(REV_BUF[2]-0x30)*10+(REV_BUF[3+1]-0x30);
//					break;
//				}
				ulCH4PPMValue = ulCH4LELValue*50;
				break;
				
			case MIPEX_03:
				ulCH4LELValue = 0;
				ulCH4LELValue = (REV_BUF[1]*0xff+REV_BUF[2]);
				ulCH4PPMValue = ulCH4LELValue*50;
				break;
			
			default :
				break;
					
		}
	}
}

void GP_SensorSet(unsigned char s_s)
{
	unsigned char i;
	unsigned char len;
	switch(uCurrentSensor)
	{
		case SUS316L:
		{
			switch(s_s)
			{
				case S_RESET:
				{
					len = 7;//strlen(ucSU_Reset_Command);
					for(i=0;i<len;i++)
					{
						UART1SendByte(ucSU_Reset_Command[i]);
					}
					res_time_count = 0;
					res_end_flag = 0;
					res_time_enable = 1;
					while(res_end_flag == 0) //等待接收
					{
						if(GP_CommArrange()==OK)
						{
							if(strcmp((char*)REV_BUF,ucSU_ResetRev_data))
							{
								res_time_count = 0;
								res_end_flag = 1;
								res_time_enable = 0;
								break;
							}
						}
					}	
				}
					break;
				case S_ZERO:
				{
					len = 7;//strlen(ucSU_ZeroAd_Command);
					for(i=0;i<len;i++)
					{
						UART1SendByte(ucSU_ZeroAd_Command[i]);
					}
					res_time_count = 0;
					res_end_flag = 0;
					res_time_enable = 1;
					while(res_end_flag == 0) //等待接收
					{
						if(GP_CommArrange()==OK)
						{
							if(strcmp((char*)REV_BUF,ucSU_ZeroRev_data))
							{
								res_time_count = 0;
								res_end_flag = 1;
								res_time_enable = 0;
								break;
							}
						}
					}	
				}
					break;
				
				case S_CORRECT:
				{
					len = 7;//strlen(ucSU_Correct_Command);
					for(i=0;i<len;i++)
					{
						UART1SendByte(ucSU_Correct_Command[i]);
					}
					res_time_count = 0;
					res_end_flag = 0;
					res_time_enable = 1;
					while(res_end_flag == 0) //等待接收
					{
						if(GP_CommArrange()==OK)
						{
							if(strcmp((char*)REV_BUF,ucSU_CorrectRev_data))
							{
								res_time_count = 0;
								res_end_flag = 1;
								res_time_enable = 0;
								break;
							}
						}
					}	
				}
				break;
				
				default:
					break;
				
			}
		}
			break;
		
		case MIPEX_03:
		{	
			switch(s_s)
			{
				case S_RESET:
				{
					len = strlen(ucMI_Reset_Command);
					for(i=0;i<len;i++)
					{
						UART1SendByte(ucMI_Reset_Command[i]);
					}
					res_time_count = 0;
					res_end_flag = 0;
					res_time_enable = 1;
					while(res_end_flag == 0) //等待接收
					{
						if(GP_CommArrange()==OK)
						{
							//f(strcmp((char*)REV_BUF,ucMI_ResetRev_data))
							//{
								res_time_count = 0;
								res_end_flag = 1;
								res_time_enable = 0;
								break;
							//}
						}
					}	
				}
					break;
				case S_ZERO:
				{
					len = strlen(ucMI_ZeroAd_Command);
					for(i=0;i<len;i++)
					{
						UART1SendByte(ucMI_ZeroAd_Command[i]);
					}
					res_time_count = 0;
					res_end_flag = 0;
					res_time_enable = 1;
					while(res_end_flag == 0) //等待接收
					{
						if(GP_CommArrange()==OK)
						{
							//f(strcmp((char*)REV_BUF,ucMI_ZeroRev_data))
							//{
								res_time_count = 0;
								res_end_flag = 1;
								res_time_enable = 0;
								break;
							//}
						}
					}	
				}
					break;
				case S_CORRECT:
				{
					len = strlen(ucMI_Correct_Command);
					for(i=0;i<len;i++)
					{
						UART1SendByte(ucMI_Correct_Command[i]);
					}
					res_time_count = 0;
					res_end_flag = 0;
					res_time_enable = 1;
					while(res_end_flag == 0) //等待接收
					{
						if(GP_CommArrange()==OK)
						{
							//f(strcmp((char*)REV_BUF,ucMI_CorrectRev_data))
							//{
								res_time_count = 0;
								res_end_flag = 1;
								res_time_enable = 0;
								break;
							//}
						}
					}	
				}
					break;
				default:
					break;
			}
		}
			break;
		
		default:
			break;
	}
}

//
void GP_CurrentSet(float g_ma)
{
	if(g_ma > 20)
	{
		g_ma = 20;
	}
	if(g_ma < 4)
	{
		g_ma = 4;
	}
	DAC_Voltage_OutPut((float)(g_ma/10.0));
}

float out_ma;
void GP_LEL2Current(unsigned long lelvalue)
{
	double out_ma;
	out_ma = (LEL_MAX - LEL_MIN)*10/16;
	out_ma = lelvalue / out_ma;
	out_ma += 4;
	GP_CurrentSet(out_ma);
}

//void GP_SensorReset(void)
//{
//	unsigned char i;
//	unsigned char len;
//	switch(uCurrentSensor)
//	{
//		case SUS316L:
//			len = 
//			break;
//	}
//	UART1SendByte();
//}
