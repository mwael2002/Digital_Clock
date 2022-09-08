/*
 * main.c
 *
 *  Created on: Oct 15, 2021
 *      Author: mwael
 */
#include"DIO_interface.h"
#include"Timer_interface.h"
#include "GIE_interface.h"
#include"LCD_interface.h"
#include "STD_Types.h"

#define AM 0
#define PM 1

U8 sec;
U8 next;
U8 min;
U8 hr;
U8 AM_PM_state;


U8 sec;
U16 desired_count;
void time_value(void);
void set_current_time(U8 current_hr,U8 current_min,U8 current_sec,U8 current_AM_PM_state);


void main(void){

	LCD_init();

    set_current_time(11,59,50,PM);

    desired_count=Overflow_time_calculate(TIMER1_ID);
    Timer1_init();
    Timer_callback(TIMER1_ID,time_value);
    Global_Int_En_Dis(Global_Int_Enable);


while(1){

if((sec>next)&&(sec!=60)&&(sec<10)){
	next++;
LCD_write_no_pos(sec,0,7);
}
if((sec>next)&&(sec!=60)&&(sec>9)){
	next++;
LCD_write_no_pos(sec,0,6);
}

if((sec==60)&&(min<9)){
	sec=0;
	next=0;
	min++;
	LCD_write_no_pos(sec,0,7);
	LCD_write_no_pos(0,0,6);

	LCD_write_no_pos(min,0,4);
}

if((sec==60)&&(min>8)){
	if(min<59){
	sec=0;
	next=0;
	min++;
	LCD_write_no_pos(sec,0,7);
	LCD_write_no_pos(0,0,6);

	LCD_write_no_pos(min,0,3);
}
	else if(min==59){
		min++;
	}
}

if((min==60)&&(hr<9)){
	    sec=0;
	    next=0;
	    min=0;
		hr++;

		LCD_write_no_pos(sec,0,7);
		LCD_write_no_pos(0,0,6);

		LCD_write_no_pos(min,0,4);
		LCD_write_no_pos(0,0,3);

		LCD_write_no_pos(hr,0,1);
}
if((min==60)&&(hr>8)&&(hr<11)){
	    sec=0;
	    next=0;
	    min=0;
		hr++;

		LCD_write_no_pos(sec,0,7);
		LCD_write_no_pos(0,0,6);

		LCD_write_no_pos(min,0,4);
		LCD_write_no_pos(0,0,3);

		LCD_write_no_pos(hr,0,0);
}

if((hr==12)&&(min==60)){
	    sec=0;
	    next=0;
	    min=0;
		hr=1;

		LCD_write_no_pos(sec,0,7);
		LCD_write_no_pos(0,0,6);

		LCD_write_no_pos(min,0,4);
		LCD_write_no_pos(0,0,3);

		LCD_write_no_pos(hr,0,1);
		LCD_write_no_pos(0,0,0);
}

if((hr==11)&&(AM_PM_state==0)&&(min==60)){
	        sec=0;
		    next=0;
		    min=0;
		    hr=12;
            AM_PM_state=PM;

			LCD_write_string_pos("PM",0,9);

			LCD_write_no_pos(sec,0,7);
			LCD_write_no_pos(0,0,6);

			LCD_write_no_pos(min,0,4);
			LCD_write_no_pos(0,0,3);

			LCD_write_no_pos(hr,0,0);
}

if((hr==11)&&(AM_PM_state==1)&&(min==60)){
	        sec=0;
		    next=0;
		    min=0;
		    hr=12;
            AM_PM_state=AM;

			LCD_write_string_pos("AM",0,9);

			LCD_write_no_pos(sec,0,7);
			LCD_write_no_pos(0,0,6);

			LCD_write_no_pos(min,0,4);
			LCD_write_no_pos(0,0,3);

			LCD_write_no_pos(hr,0,0);
}

}
}


void set_current_time(U8 current_hr,U8 current_min,U8 current_sec,U8 current_AM_PM_state){
	hr=current_hr;
	min=current_min;
	next=sec=current_sec;
	current_AM_PM_state=AM_PM_state;


	if(current_AM_PM_state==AM){
	LCD_write_string_pos("AM",0,9);
	}
	else{
	LCD_write_string_pos("AM",0,9);
	}

	LCD_write_string_pos(":",0,8);

	if(current_sec<10){
	LCD_write_no_pos(current_sec,0,7);
	LCD_write_no_pos(0,0,6);
	}

	else{
    LCD_write_no_pos(current_sec,0,6);
	}

	LCD_write_string_pos(":",0,5);

	if(current_min<10){
	LCD_write_no_pos(current_min,0,4);
    LCD_write_no_pos(0,0,3);
		}
	else{
	LCD_write_no_pos(current_min,0,3);
	}

	LCD_write_string_pos(":",0,2);

	if(current_hr<10){
	LCD_write_no_pos(current_hr,0,1);
	LCD_write_no_pos(0,0,0);
		}
	else{
	LCD_write_no_pos(current_hr,0,0);
	}

}


void time_value(void){
	static U16 count=0;

	count++;

	if(count==desired_count){
		sec++;
		Overflow_restart_count(TIMER1_ID);
		count=0;

	}
	}

