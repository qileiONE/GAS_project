#ifndef __CONFIG_H
#define	__CONFIG_H

#include "stm32f10x.h"


#define VERSION		0X01

#define DIS_TIME  	1000 //1000ms PPM 和 LEL切换显示时间
#define RESPONSE_TIME		2000   //2000ms 2s 传感器超时回复时间

//#define    //校准直接到comm.c文件中改发送的数据

#define UPPER_LIMIT 	80   //阈值上限  80%LEL 
#define LOWER_LIMIT   10		//阈值下限	0%LEL


#define IN
#define OUT
#define INOUT

#define CHAR	char
#define UCHAR	unsigned char
#define BYTE	unsigned char

#define SHORT	short				// 2byte
#define USHORT	unsigned short		// 2byte
#define WORD	unsigned short		// 2byte
#define INT		int					// 4byte	
#define UINT	unsigned int		// 4byte
#define DWORD	unsigned int		// 4byte
//#define BOOL	unsigned char		// 1byte
#define LONG	long				// 4byte
#define ULONG	unsigned long		// 4byte


#define OK					0x00
#define TURE 				1
#define FALSE				0


#define ERROR_BASE			0x00
#define ERROR_NODEVICE  	ERROR_BASE+0x01
#define ERROR_TIMEOUT		ERROR_BASE+0x02
#define ERROR_OTHER			0xff

#define FREE_STATE			0xfe


#define RCC_GPIOA_CLK_ENABLE()	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // enable the PA clock  
#define RCC_GPIOB_CLK_ENABLE()	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); // enable the PB clock  
#define RCC_GPIOC_CLK_ENABLE()	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // enable the PC clock  
#define RCC_GPIOD_CLK_ENBALE()	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // enable the PD clock  
#define	RCC_GPIOE_CLK_ENABLE()	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE); // enable the PE clock  
#define RCC_GPIOF_CLK_ENABLE()	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOF, ENABLE); // enable the PF clock  



enum SensorType
{
	SUS316L = 1,
	MIPEX_03,

	SensorType_NULL
};
enum SensorSet
{
	S_RESET = 1,
	S_ZERO ,
	S_CORRECT,
	
	SensorSet_NULL
};


struct ComPara_Device
{
	u32 com_Baud;
	u8	com_data;
	u8	com_stop;
};



#endif /* __CONFIG_H */



