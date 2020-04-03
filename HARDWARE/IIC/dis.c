#include "dis.h"
#include "delay.h"
#include "IIC.h"
#include "stdio.h"


unsigned char ucUPnumpos[5] = {0x1e,0x1c,0x1a,0x18,0x16};//{0x06,0x18,0x1a,0x1c,0x1e};//
unsigned char ucUPnumcode[10] = {0xf5,0x60,0xd3,0xf2,0x66,0xb6,0xb7,0xe0,0xf7,0xf6};

unsigned char ucDOWNLELcode[11] = {0x00,0x00,0x00,0x01,0x78,0xda,0x80,0x9a,0x14,0xa8,0x02};
unsigned char ucDOWNPPMcode[11] = {0x00,0x00,0x00,0x00,0x00,0x0e,0x12,0xb2,0x16,0xb0,0x1c};


void PCF8576_WriteCommand(unsigned char command)
{
	IIC_Start();                  
	IIC_Send_Byte(PCF8576);                
	IIC_Wait_Ack();                     
	IIC_Send_Byte(command);                
	IIC_Wait_Ack();
	IIC_Stop();                  
}

void PCF8576_WritePoint(unsigned char suba,unsigned char dat)
{
	IIC_Start();  
	IIC_Send_Byte(PCF8576);  
	IIC_Wait_Ack();       
	IIC_Send_Byte(suba);   
	IIC_Wait_Ack();  
	IIC_Send_Byte(dat);   
	IIC_Wait_Ack(); 
	IIC_Stop();
}

void PCF8576_WriteStr(unsigned char suba,unsigned char *str,unsigned char no)
{
	unsigned char i;
	IIC_Start();  
	IIC_Send_Byte(PCF8576);  
	IIC_Wait_Ack();       
	IIC_Send_Byte(suba);   
	IIC_Wait_Ack();  
	
	for(i=0;i<no;i++)
	{
		IIC_Send_Byte(*str);   
		IIC_Wait_Ack(); 
		str++;
	}
	IIC_Stop();
}

void PCF8576_Ini(unsigned char mode,unsigned char glitter)
{
	mode = (mode&0x1f)|0x40;
	PCF8576_WriteCommand(mode);
	glitter = (glitter&0x07)|0x70;
	PCF8576_WriteCommand(glitter);
}

void PCF8576_Point(unsigned addr,unsigned char dat)
{
	PCF8576_WriteCommand(0x60);
	addr = addr&0x3f;
	PCF8576_WritePoint(addr,dat);
}

void PCF8576_Disp(unsigned addr,unsigned char *str,unsigned char no)
{
	PCF8576_WriteCommand(0x60);
	addr = addr&0x3f;
	PCF8576_WriteStr(addr,str,no);
}


void LCD_DisNum(unsigned long disnum)
{
	unsigned char up_none_disp[5] = {0x00};
	PCF8576_Disp(0x16,up_none_disp,5);
	if(disnum >= 200000)
	{
		return;
	}
	else if(disnum >= 100000)
	{
		disnum = disnum - 100000;
		PCF8576_Point(ucUPnumpos[0],ucUPnumcode[disnum/10000%10]);
		PCF8576_Point(ucUPnumpos[1],ucUPnumcode[disnum/1000%10]);
		PCF8576_Point(ucUPnumpos[2],ucUPnumcode[disnum/100%10]);
		PCF8576_Point(ucUPnumpos[3],ucUPnumcode[disnum/10%10]);
		PCF8576_Point(ucUPnumpos[4],ucUPnumcode[disnum/1%10]|0x08); //点亮最高位 “1”
	}
	else
	{
		if(disnum > 9999)
		{
			PCF8576_Point(ucUPnumpos[0],ucUPnumcode[disnum/10000%10]);
			PCF8576_Point(ucUPnumpos[1],ucUPnumcode[disnum/1000%10]);
			PCF8576_Point(ucUPnumpos[2],ucUPnumcode[disnum/100%10]);
			PCF8576_Point(ucUPnumpos[3],ucUPnumcode[disnum/10%10]);
			PCF8576_Point(ucUPnumpos[4],ucUPnumcode[disnum/1%10]); 
		}
		else if(disnum > 999)
		{
			PCF8576_Point(ucUPnumpos[1],ucUPnumcode[disnum/1000%10]);
			PCF8576_Point(ucUPnumpos[2],ucUPnumcode[disnum/100%10]);
			PCF8576_Point(ucUPnumpos[3],ucUPnumcode[disnum/10%10]);
			PCF8576_Point(ucUPnumpos[4],ucUPnumcode[disnum/1%10]); 
		}
		else if(disnum > 99)
		{
			PCF8576_Point(ucUPnumpos[2],ucUPnumcode[disnum/100%10]);
			PCF8576_Point(ucUPnumpos[3],ucUPnumcode[disnum/10%10]);
			PCF8576_Point(ucUPnumpos[4],ucUPnumcode[disnum/1%10]); 
		}
		else if(disnum > 9)
		{
			PCF8576_Point(ucUPnumpos[3],ucUPnumcode[disnum/10%10]);
			PCF8576_Point(ucUPnumpos[4],ucUPnumcode[disnum/1%10]); 
		}
		else 
		{
			PCF8576_Point(ucUPnumpos[4],ucUPnumcode[disnum/1%10]); 
		}
	}
}

void LCD_DisClear(void)
{
	unsigned char none_disp[21] = {0x00};  
	PCF8576_Disp(0x00, none_disp, 20);
}

void LCD_DisAll(void)
{
	unsigned char i;
	unsigned char all_disp[21] = {0};  
	for(i=0;i<20;i++)
	{
		all_disp[i]=0xff; 
	}
	PCF8576_Disp(0x00, all_disp, 20);
}

void LCD_DisLEL(void)
{
	PCF8576_Disp(0x00,ucDOWNLELcode,11);
}


void LCD_DisPPM(void)
{
	PCF8576_Disp(0x00,ucDOWNPPMcode,11);
}


void LCD_DisLELValue(unsigned long lelvalue)
{
		if(lelvalue == 0)
		{
			PCF8576_Point(ucUPnumpos[3],ucUPnumcode[0]);
			PCF8576_Point(ucUPnumpos[4],ucUPnumcode[0]); 
			LCD_DisLEL();
		}
		else
		{
			LCD_DisNum(lelvalue);
			LCD_DisLEL();
		}
}

void LCD_DisPPMValue(unsigned long ppmvalue)
{
	LCD_DisNum(ppmvalue);
	LCD_DisPPM();
}

