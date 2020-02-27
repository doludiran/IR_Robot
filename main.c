#include"clocks.h"
#include"io.h"
#include"lcd.h"
#include"remote.h"
#include"trig.h"

int main(void)
{
uint16_t dist;	
uint16_t code=0;
clockInit();
apbclock_en();
configMode();
init_lcd();
PWM_Init();
ultra_Config();
Tim_Init();
//delay(100000);
	
	
while(1)
{
	repeat = 1;
  dist=ultra_Read(); 
	commandto_lcd(LCD_LN1);
	Display_dist(dist);
	
	
	commandto_lcd(LCD_LN2);
	code = code_decode(repeat);
	
       show_hex(code);
		 

	
	  if (code==0xF894 )              //|| Move
		  {
       if  (OBS) 
	      {
	        Right=0;
					Move = 0;
					Forward=0;
	      }
			 else
			  {
					Right=0;
					Move = 1;
					Forward=1;		
 	      }
			}
	  else if(code == 0xF8D4 )
		    {
					Right=0;
					Move=1;
					Forward = 0;
	      }	
	  else if(code == 0xF8A4)
		    {        
	        Right=1;
					Move=1;
					Forward=0;
        }     	   
	  else if(code == 0xF8E4)
		    {
	      Right=1;
				Move=1;
				Forward=1;
	      }
			
    else
        {
	
	       Right=0;
				 Move = 0;
				 Forward=0;
       }	



     if(!Right && !Move && !Forward)
		 { 
		 all_stop();
		 }
     if (!Right && Move && Forward)
		 {
		 move_forward();
		 
		 }	  
		 if(!Right && Move && !Forward)
     {
			 move_back();
			 
		 }	
     if(Right && Move && !Forward)
		 {move_right();}
     if (Right && Move && Forward)
     {move_left();}		

     
}   
}