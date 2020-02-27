/******************************************************************************
 * Name:    io.h
 * Description: STM32 peripherals initialization and functions
 * Version: V1.00
 * Author: Damilola Oludiran 
  some codes from lab1_lib.c written by Dave Duguid / Trevor Douglas
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *          V1.1 reformatted (kjn)
 *****************************************************************************/


void apbclock_en(void);
void configMode(void);
uint16_t read_sw1(void);
//int read_pb(void);
void write_led(void);
void delay(uint32_t count);
void all_stop(void);
void move_forward(void);
void move_right(void);
void move_left(void);
void move_back(void);