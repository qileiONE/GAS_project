#ifndef __COMM_H
#define __COMM_H

#include "sys.h"
#include "config.h"

extern u8 uCurrentSensor;  //
extern u8 uRevNumCount; //
extern unsigned long ulCH4LELValue;  //%LEL    �Ŵ�10������ֵ
extern unsigned long ulCH4PPMValue;  //PPM
void GP_CommProcess(void);

#endif


