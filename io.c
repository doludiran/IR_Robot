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
 #include "io.h"
 
 void apbclock_en(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN |RCC_APB2ENR_IOPBEN |RCC_APB2ENR_IOPCEN |RCC_APB2ENR_AFIOEN;
}

void configMode(void)
{
    GPIOA->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_MODE10 |GPIO_CRH_MODE11 | GPIO_CRH_MODE12;
    GPIOA->CRH &= ~GPIO_CRH_CNF9 & ~GPIO_CRH_CNF10 & ~GPIO_CRH_CNF11 & ~GPIO_CRH_CNF12;
	  GPIOC->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_MODE8 ;
    GPIOC->CRH &= ~GPIO_CRH_CNF9 & ~GPIO_CRH_CNF8 ;
    GPIOA->CRL |=	GPIO_CRL_MODE0|GPIO_CRL_CNF0_1 ;
	  GPIOA->CRL &=	~GPIO_CRL_CNF0_0;
    GPIOA->CRL &=	0xF4FFFFFF; //Input digital
}

uint16_t read_sw1(void)
{
	  	 uint16_t sw;
	sw = (((GPIOA->IDR & (GPIO_IDR_IDR6 | GPIO_IDR_IDR7))>>6 )
	|((GPIOC->IDR & (GPIO_IDR_IDR10 | GPIO_IDR_IDR11)) >>8)) & 0x0F;
	
	                
	return (sw);
}


void write_led(void)
{
	    
 
		 if((GPIOB->IDR & GPIO_IDR_IDR8) == 0){
		        
		          move_forward();
		 
		 }
		 else if((GPIOB->IDR & GPIO_IDR_IDR9) == 0 ){
        			
              move_right();
			 }
     else if((GPIOC->IDR & GPIO_IDR_IDR12) == 0 ){
        			
              move_left();
		 }
     else if((GPIOA->IDR & GPIO_IDR_IDR5)== 0){ 
			        move_back();

			 }		 
	  else {all_stop();}
	 }

void move_forward()
{
		          //int i = 120000;
			        GPIOA->BSRR = GPIO_BSRR_BS9;
	            //delay(i);
              GPIOA->BSRR = GPIO_BSRR_BS11;	
		          //delay(i);
	            GPIOA->BSRR = GPIO_BSRR_BR10;
              GPIOA->BSRR = GPIO_BSRR_BR12;	
		          //delay(i); 
}

void move_right()
{
	            //int i=120000;
			        GPIOA->BSRR = GPIO_BSRR_BS9;
	            GPIOA->BSRR = GPIO_BSRR_BR10;
	            //delay(i);
	            GPIOA->BSRR = GPIO_BSRR_BR11;
              GPIOA->BSRR = GPIO_BSRR_BS12;	
		          //delay(i);
	            
              	
		          //delay(i);
              
}

void move_left()
{
	            GPIOA->BSRR = GPIO_BSRR_BR9;
	            //int i=120000;
			        GPIOA->BSRR = GPIO_BSRR_BS10;
	            //delay(i);
              GPIOA->BSRR = GPIO_BSRR_BS11;	
		          //delay(i);
	            
              GPIOA->BSRR = GPIO_BSRR_BR12;	
		          //delay(i);
              
}

void move_back()
{ 
	            GPIOA->BSRR = GPIO_BSRR_BR9;  
	            GPIOA->BSRR = GPIO_BSRR_BS10;
	            //int i=120000;
              GPIOA->BSRR = GPIO_BSRR_BR11; 
            	GPIOA->BSRR = GPIO_BSRR_BS12;
	            //delay(i);
              	
		         // delay(i);
	            
              	
		          //delay(i);
      
			 		 
}
	
void all_stop()
{
GPIOA->BSRR = GPIO_BSRR_BR9;
GPIOA->BSRR = GPIO_BSRR_BR10;
GPIOA->BSRR = GPIO_BSRR_BR11;
GPIOA->BSRR = GPIO_BSRR_BR12;	
}

void delay(uint32_t count)
{
    int i=0;
    for(i=0; i< count; ++i)
    {
    }
} 