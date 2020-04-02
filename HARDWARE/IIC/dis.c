#include "dis.h"
#include "delay.h"
#include "IIC.h"
#include "stdio.h"


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


