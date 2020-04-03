#include "comm.h"
#include "usart.h"
#include "config.h"

u8 uCurrentSensor;  //
u8 uRevNumCount = 0; //
unsigned long ulCH4LELValue = 0;  //%LEL    放大10倍的数值
unsigned long ulCH4PPMValue = 0;  //PPM

//SUS316L
unsigned char ucSU_ZeroAd_Command[] = {0x3a,0x31,0x00,0x00,0x31,0x0d,0x0a};
unsigned char ucSU_Correct_Command[] = {0x3a,0x33,0x01,0x90,0xc4,0x0d,0x0a};
unsigned char ucSU_Reset_Command[] = {0x3a,0x35,0x00,0x00,0x35,0x0d,0x0a};

//MIPEX_03
unsigned char ucMI_MeasuredDataMau_Command[] = {0x40,0x0D};
unsigned char ucMI_MeasuredDataAuto_Command[] = {0x40,0x2A,0x34,0x0D};  //?5s = 1.32 * 4
unsigned char ucMI_ZeroAd_Command[]={0x5A,0x45,0x52,0x4F,0x32,0x0D};//ZERO2
unsigned char ucMI_Correct_Command[]={0x43,0x41,0x4C,0x42,0x20,0x34,0x30,0x30,0x30,0x0D};//CALB 4000
unsigned char ucMI_Reset_Command[] = {0x49,0x4E,0x49,0x54,0x0D};//INIT

u8 REV_BUF[USART_REC_LEN];     //

void SensorTypeCheck(void)
{
		
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
				for(i=0;i<5;i++)
				{
					if(REV_BUF[i] == 0x2E)
					{
						numbit = i;
						break;
					}
				}
				switch(numbit)
				{
					case 0:
						ulCH4LELValue += REV_BUF[0+1]-0x30;
					break;
					case 1:
						ulCH4LELValue = (REV_BUF[0]-0x30)*10+(REV_BUF[1+1]-0x30);
					break;
					case 2:
						ulCH4LELValue = (REV_BUF[0]-0x30)*100+(REV_BUF[1]-0x30)*10+(REV_BUF[2+1]-0x30);
					break;
					case 3:
						ulCH4LELValue = (REV_BUF[0]-0x30)*1000+(REV_BUF[1]-0x30)*100+(REV_BUF[2]-0x30)*10+(REV_BUF[3+1]-0x30);
					break;
				}
				ulCH4PPMValue = ulCH4LELValue*500;
				break;
		}
	}
}


