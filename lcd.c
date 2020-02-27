 
  /******************************************************************************
 * Name:    io.c
 * Description: STM32 peripherals initialization and functions
 * Version: V1.00
 * Author:Damilola Oludiran 
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
 #include "stm32f10x.h"
// #include "clocks.h"
#include "io.h"
 #include"trig.h"
 #include"lcd.h"
 void init_lcd(void)
{
	  //configure output modes
    GPIOB->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1 |GPIO_CRL_MODE5;
    GPIOB->CRL &= ~GPIO_CRL_CNF0 & ~GPIO_CRL_CNF1 & ~GPIO_CRL_CNF5;
	
	  GPIOC->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1| GPIO_CRL_MODE2| GPIO_CRL_MODE3| GPIO_CRL_MODE4 
	                |GPIO_CRL_MODE5| GPIO_CRL_MODE6| GPIO_CRL_MODE7;
    GPIOC->CRL &= ~GPIO_CRL_CNF0 & ~GPIO_CRL_CNF1 & ~GPIO_CRL_CNF2 & ~GPIO_CRL_CNF3 & ~GPIO_CRL_CNF4 
               & ~GPIO_CRL_CNF5 & ~GPIO_CRL_CNF6 & ~GPIO_CRL_CNF7;
	  
	  //initializing lcd
	  commandto_lcd(LCD_8B2L);
	  delay(30000);
	  commandto_lcd(LCD_8B2L);
    delay(8000);	
	  commandto_lcd(LCD_8B2L);
	  commandto_lcd(LCD_8B2L);
	  commandto_lcd(LCD_DCB);
    commandto_lcd(LCD_CLR);
    commandto_lcd(LCD_MCR);  
	
}

/*
* Name: commandToLCD
* Type: PUBLIC
* Parameters: a single byte of command information for the LCD controller
* Returns: nothing
* Description: This function generates control timing and data signals to send one command byte to the LCD
*/
void commandto_lcd(uint8_t command)
{
GPIOB->BSRR = LCD_CM_ENA;                //RS low, E high
	
GPIOC->ODR &= 0xFF00;                   //GOOD: clears the low bits without affecting high bits
GPIOC->ODR |= command;                   //GOOD: only affects lowest 8 bits of Port C
delay(8000);
GPIOB->BSRR = LCD_CM_DIS;              //RS low, E low
delay(80000);
}
 
void datato_lcd(uint8_t data)
{
GPIOB->BSRR = LCD_DM_ENA;                //RS low, E high
	
GPIOC->ODR &= 0xFF00;                   //GOOD: clears the low bits without affecting high bits
GPIOC->ODR |= data;                   //GOOD: only affects lowest 8 bits of Port C
delay(8000);
GPIOB->BSRR = LCD_DM_DIS;              //RS low, E low
delay(80000);
}

void stringto_lcd(void)
{
	
	char name[6] = "RANGE:";
	
  int i;
	
 
			for (i = 0;i < 6; i++)
	{
		datato_lcd(name[i]);
	}
	


}