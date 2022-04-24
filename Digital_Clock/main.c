/*
 * main.c
 *
 *  Created on: Oct 15, 2021
 *      Author: mwael
 */
#include"D:/C/STD.Types.h"
#define F_CPU 8000000
#include"util/delay.h"
#include"DIO_interface.h"
#include"Timer_0_ov_interface.h"
#include"LCD_interface.h"
#define AM 0
#define PM 1

U8 sec;
void main(void){
	sec=0;
	U8 next=sec;
	U8 min=53;
	U8 hr=10;
	U8 state=PM;

	DIO_set_pin_direction(Group_A,7,OUTPUT);
	LCD_init();

	LCD_string_pos("PM",0,9);

	LCD_write_no(sec,0,7);
	LCD_write_no(0,0,6);

	LCD_string_pos(":",0,5);

	LCD_write_no(min,0,3);

	LCD_string_pos(":",0,2);

	LCD_write_no(hr,0,0);

	Timer_ov_init(1000);
	callback(time_value);

while(1){

if((sec>next)&&(sec!=60)&&(sec<10)){
	next++;
LCD_write_no(sec,0,7);
}
if((sec>next)&&(sec!=60)&&(sec>9)){
	next++;
LCD_write_no(sec,0,6);
}

if((sec==60)&&(min<9)){
	sec=0;
	next=0;
	min++;
	LCD_write_no(sec,0,7);
	LCD_write_no(0,0,6);

	LCD_write_no(min,0,4);
}

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

if((hr==11)&&(state==0)&&(min==60)){
	        sec=0;
		    next=0;
		    min=0;
		    hr=12;
            state=1;

			LCD_string_pos("PM",0,9);

			LCD_write_no(sec,0,7);
			LCD_write_no(0,0,6);

			LCD_write_no(min,0,4);
			LCD_write_no(0,0,3);

			LCD_write_no(hr,0,0);
}

if((hr==11)&&(state==1)&&(min==60)){
	        sec=0;
		    next=0;
		    min=0;
		    hr=12;
            state=0;

			LCD_string_pos("AM",0,9);

			LCD_write_no(sec,0,7);
			LCD_write_no(0,0,6);

			LCD_write_no(min,0,4);
			LCD_write_no(0,0,3);

			LCD_write_no(hr,0,0);
}

}
}

