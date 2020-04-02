#ifndef __DIS_H
#define __DIS_H
#include "sys.h" 
 
#define MODE_LP		0x10 
#define MODE_E  	0x08 
#define MODE_B  	0x04 
#define MODE_M1 	0x02 
#define MODE_M0     0x01 
 
#define GLITTER_A   0x04 
#define GLITTER_BF1 0x02 
#define GLITTER_BF0 0x01 
 
#define NOGLITTER   0x00 
 
#define PCF8576 0x70          	/* Æ÷¼þµØÖ· */ 


void PCF8576_Ini(unsigned char mode,unsigned char glitter);
void PCF8576_Point(unsigned addr,unsigned char dat);
void PCF8576_Disp(unsigned addr,unsigned char *str,unsigned char no);

#endif
