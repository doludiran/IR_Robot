/******************************************************************************
* Name:    remote.c
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

#include"remote.h"

_Bool repeat = 1;
int counter = 0;
_Bool Forward = 1;
_Bool Right=0;
_Bool Move = 0;
_Bool OBS=0;

void Tim_Init()
{
	
RCC->APB2ENR |=RCC_APB2ENR_TIM1EN;
RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
	
GPIOA->CRH &=	0xFFFFFFF4; //Input digital
	
TIM1->CR1 |= TIM_CR1_CEN;                    //counter enabled
TIM1->CR2 |= TIM_CR2_TI1S;                   //TI1 selection
TIM1->PSC  = 23;
TIM1->ARR = 65535;
TIM1->CCMR1 |=TIM_CCMR1_CC1S_0;             // Select the active input for TIMx_CCR1
TIM1->CCER |= TIM_CCER_CC1P ;             // Select the active polarity for TI1FP1
TIM1->CCMR1 |=TIM_CCMR1_CC2S_1;            //Select the active input for TIMx_CCR2:
TIM1->CCER &= ~TIM_CCER_CC2P ;	            //Select the active polarity for TI1FP2
TIM1->SMCR = 0x0050;                      // Select the valid trigger input:
TIM1->SMCR |= TIM_SMCR_SMS_2 ;            //Configure the slave mode controller in reset mode:

//TIM1->EGR |= TIM_EGR_UG ;
//TIM1->DIER|=TIM_DIER_CC1IE|TIM_DIER_CC2IE|TIM_DIER_UIE ;
TIM1->CCER |= TIM_CCER_CC1E |TIM_CCER_CC2E ; //	Enable the captures:



}

uint16_t width_read()
{

if ((TIM1->SR & TIM_SR_CC2IF) == TIM_SR_CC2IF)
{

return TIM1->CCR2;
}
else return 0;
  

}

uint16_t period_read()
{
	if ((TIM1->SR & TIM_SR_CC1IF) == TIM_SR_CC1IF)
{
 
return TIM1->CCR1;
}
else return 0;
}


uint16_t code_decode(_Bool repeat)
{
	uint16_t width;
	uint16_t period;
	uint16_t bit_code = 0x0;
  int bit=0;
int bit_count=0;	
	int i;
	
//for (i= 0; i < 16; i++)
	
//{
	// delay(100000);
while (bit_count<16 && repeat)
{
if ((TIM1->SR & TIM_SR_UIF)==TIM_SR_UIF) 
{
	
	TIM1->SR &= ~TIM_SR_UIF;
	width=width_read();
  period=period_read();
		
	if((width!=0) ||(period !=0))
	{
   if ((width > 500)&&(width < 700))
	 {
     if ((period > 800) && (period < 1300))
		 {
			bit = 0;
			bit_count++;
			
		 }			 
		 else if ((period > 1800) && (period < 2300))
		 {
			 
		   bit = 1;
       bit_count++;			 
		 }
		 //else{i=0; bit_code=0; }//break;}
		bit_code = (bit_code << 1)| bit;

	 } 
	 //else{i=0; bit_code=0; break;}
  }
	counter++;
	if((counter == 20) || OBS)
	{
		counter =0;
		repeat = 0;

	}

	//else{i=0; bit_code=0; break;}

}
}
//}
if (bit_count ==16)
{return bit_code;}
else {return 0;}

}


void hex_val(uint8_t hexval)
{
 if (hexval < 0x0A){ datato_lcd(0x30 + hexval);}
 else {datato_lcd(0x41 + (hexval - 0x0A));}
}

void show_hex(uint16_t hexval)
{
  datato_lcd(0x30);
	datato_lcd(0x78);
	hex_val((hexval & 0xF000)>> 12 );
	hex_val((hexval & 0xF00)>> 8 );
	hex_val((hexval & 0xF0)>> 4 );
	hex_val((hexval & 0xF));
}
