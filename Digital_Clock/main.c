/*
 * main.c
 *
 *  Created on: Oct 15, 2021
 *      Author: mwael
 */
#include"STD.Types.h"
#define F_CPU 8000000
#include"util/delay.h"
#include"DIO_interface.h"
#include"Timer_0_ov_interface.h"
#include"LCD_interface.h"
#define AM 0
#define PM 1

U8 sec;
void main(void){
/*********************************************************************Setup of initial time***************************************************************************/
	sec=0;       //variable that express seconds that is increased in the time_value function in Timer_ov_program.c file(initially =0)
	U8 next=sec;  //variable that is compared with seconds in while(1) loop to increase minute value
	U8 min=53;  //variable that express minute and it's increament(initially=53) 
	U8 hr=10;   //variable that express hour and it's increament(initially=10) 
	U8 state=PM;  //variable that express time state if it's PM or AM
/*********************************************************************Showing time on LCD*****************************************************************************/
	LCD_init();

	LCD_string_pos("PM",0,9);

	LCD_write_no(sec,0,7);
	LCD_write_no(0,0,6);

	LCD_string_pos(":",0,5);

	LCD_write_no(min,0,3);

	LCD_string_pos(":",0,2);

	LCD_write_no(hr,0,0);

	Timer_ov_init(1000);     //Setting timer count into 1000 millisecond
	callback(time_value);    //callback function that takes function time value in Timer_ov driver as an input

while(1){
/**********************************************************************First case of changing second time************************************************************/
if((sec>next)&&(sec!=60)&&(sec<10)){
	next++;
LCD_write_no(sec,0,7);
}
/**********************************************************************Second case of changing second time***********************************************************/
if((sec>next)&&(sec!=60)&&(sec>9)){
	next++;
LCD_write_no(sec,0,6);
}
/***********************************************************************First case of changing minute time************************************************************/
if((sec==60)&&(min<9)){
	sec=0;
	next=0;
	min++;
	LCD_write_no(sec,0,7);
	LCD_write_no(0,0,6);

	LCD_write_no(min,0,4);
}
/***********************************************************************Second case of changing minute time************************************************************/
if((sec==60)&&(min>8)){
	if(min<59){
	sec=0;
	next=0;
	min++;
	LCD_write_no(sec,0,7);
	LCD_write_no(0,0,6);

	LCD_write_no(min,0,3);
}
	else if(min==59){
		min++;
	}
}
/***********************************************************************First case of changing hour time**************************************************************/
if((min==60)&&(hr<9)){
	    sec=0;
	    next=0;
	    min=0;
	    hr++;

		LCD_write_no(sec,0,7);
		LCD_write_no(0,0,6);

		LCD_write_no(min,0,4);
		LCD_write_no(0,0,3);

		LCD_write_no(hr,0,1);
}
/***********************************************************************Second case of changing hour time**************************************************************/
if((min==60)&&(hr>8)&&(hr<11)){
	    sec=0;
	    next=0;
	    min=0;
            hr++;

		LCD_write_no(sec,0,7);
		LCD_write_no(0,0,6);

		LCD_write_no(min,0,4);
		LCD_write_no(0,0,3);

		LCD_write_no(hr,0,0);
}
/***********************************************************************Third case of changing hour time**************************************************************/
if((hr==12)&&(min==60)){
	    sec=0;
	    next=0;
	    min=0;
            hr=1;

		LCD_write_no(sec,0,7);
		LCD_write_no(0,0,6);

		LCD_write_no(min,0,4);
		LCD_write_no(0,0,3);

		LCD_write_no(hr,0,1);
		LCD_write_no(0,0,0);
}
/****************************************************************Fourth case of changing hour time(From AM to PM)*****************************************************/
if((hr==11)&&(state==AM)&&(min==60)){
	   sec=0;
           next=0;
           min=0;
           hr=12;
           state=PM;

			LCD_string_pos("PM",0,9);

			LCD_write_no(sec,0,7);
			LCD_write_no(0,0,6);

			LCD_write_no(min,0,4);
			LCD_write_no(0,0,3);

			LCD_write_no(hr,0,0);
}
/****************************************************************Fifth case of changing hour time(From PM to AM)******************************************************/
if((hr==11)&&(state==PM)&&(min==60)){
	     sec=0;
             next=0;
             min=0;
	     hr=12;
             state=AM;

			LCD_string_pos("AM",0,9);

			LCD_write_no(sec,0,7);
			LCD_write_no(0,0,6);

			LCD_write_no(min,0,4);
			LCD_write_no(0,0,3);

			LCD_write_no(hr,0,0);
}

}
}

