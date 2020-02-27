
/******************************************************************************
* Name:    trig.c
* Description: Ultrasonic range finder initialization and functions
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

#include"trig.h"
#include"lcd.h"
#include"remote.h"
		
void PWM_Init(){	
	
RCC->APB1ENR |=RCC_APB1ENR_TIM2EN;
	
TIM2->CR1 |= TIM_CR1_CEN; 
TIM2->CR2 |= TIM_CR2_OIS1;
TIM2->EGR |= TIM_EGR_UG ;
TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 |TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE |TIM_CCMR1_OC1FE; 
TIM2->CCER |=TIM_CCER_CC1E;
TIM2->PSC  = 2399;
TIM2->ARR  =1000;
TIM2->CCR1	=10;
	
TIM2->BDTR |= TIM_BDTR_MOE |TIM_BDTR_OSSI; 
TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
}

void ultra_Config(void)
{
RCC->APB1ENR |=RCC_APB1ENR_TIM3EN;
TIM3->CR1 |= TIM_CR1_CEN;                    //counter enabled
TIM3->CR2 |= TIM_CR2_TI1S;                   //TI1 selection
TIM3->PSC  = 23;
TIM3->ARR = 65535;
TIM3->CCMR1 |=TIM_CCMR1_CC1S_0;             // Select the active input for TIMx_CCR1
TIM3->CCER &= ~TIM_CCER_CC1P ;             // Select the active polarity for TI1FP1
TIM3->CCMR1 |=TIM_CCMR1_CC2S_1;            //Select the active input for TIMx_CCR2:
TIM3->CCER |= TIM_CCER_CC2P ;	            //Select the active polarity for TI1FP2
TIM3->SMCR = 0x0050;                      // Select the valid trigger input:
TIM3->SMCR |= TIM_SMCR_SMS_2 ;            //Configure the slave mode controller in reset mode:

//TIM1->EGR |= TIM_EGR_UG ;
//TIM3->DIER|=TIM_DIER_CC1IE|TIM_DIER_CC2IE;
TIM3->CCER |= TIM_CCER_CC1E |TIM_CCER_CC2E ; //	Enable the captures:


}


uint16_t ultra_Read()
{

uint16_t period;
uint16_t width;
uint16_t dist;
	

if ((TIM3->SR & TIM_SR_CC2IF) == TIM_SR_CC2IF)
{
period = TIM3->CCR1;
width = TIM3->CCR2;	
dist =(width/58);
	
if((dist!=0) && (dist < 14))
{OBS=1;}
else{OBS=0;}
return dist; } 
//else return 0;


}


void Display_dist(uint16_t dist)
{
	uint16_t dec = dist;
	stringto_lcd();
	
	dec = (dec % 100);
	datato_lcd(0x30 + (dec/10));
	
	dec = dec % 10;
	datato_lcd(0x30 + dec);
	datato_lcd('C');
	datato_lcd('M');
}

