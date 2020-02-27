/******************************************************************************
* Name:    remote.h
* Description: IR remote control initialization and functions
* Version: V1.00
* Author: Damilola Oludiran
*
* This software is supplied "AS IS" without warranties of any kind.
*
*
*----------------------------------------------------------------------------
* History:
*          V1.00 Initial Version
*
*****************************************************************************/

#include"stdint.h"
#include"stm32f10x.h"
#include"lcd.h"

extern _Bool repeat;
extern int counter;
extern _Bool Forward;
extern _Bool Right;
extern _Bool Move;
extern _Bool OBS;

void Tim_Init(void);
uint16_t width_read(void);
uint16_t period_read(void);
uint16_t code_decode(_Bool repeat);
void hex_val(uint8_t hexval);
void show_hex(uint16_t hexval);
