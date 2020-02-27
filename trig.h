/******************************************************************************
* Name:    trig.h
* Description:  Ultrasoni range finder function initializations
* Version: V1.00
* Author: Damilola Oludiran

*
* This software is supplied "AS IS" without warranties of any kind.
*
*
*----------------------------------------------------------------------------
* History:
*          V1.00 Initial Version
*          V1.1 reformatted (kjn)
*****************************************************************************/
#include"stdint.h"
#include"stm32f10x.h"

void ultra_Config(void);
uint16_t ultra_Read(void);
void PWM_Init(void);
void Display_dist(uint16_t dist);
