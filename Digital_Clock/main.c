/*
 * main.c
 *
 *  Created on: Oct 15, 2021
 *      Author: mwael
 */
#include"STD.Types.h"
#include"DIO_interface.h"
#include"Timer_0_ov_interface.h"
#include"LCD_interface.h"
#define AM 0
#define PM 1

U8 sec;
U16 desired_count;
void time_value(void);
void main(void){
	sec=0;
	U8 next=sec;
	U8 min=53;
	U8 hr=10;
	U8 state=PM;

	DIO_set_pin_direction(Group_A,7,OUTPUT);
	LCD_init();

	LCD_write_string_pos("PM",0,9);

	LCD_write_no_pos(sec,0,7);
	LCD_write_no_pos(0,0,6);

	LCD_write_string_pos(":",0,5);

	LCD_write_no_pos(min,0,3);

	LCD_write_string_pos(":",0,2);

	LCD_write_no_pos(hr,0,0);

    desired_count=time_calculate(1000);

    Timer_ov_init(1000);
    callback(time_value);

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

if((hr==11)&&(state==0)&&(min==60)){
	        sec=0;
		    next=0;
		    min=0;
		    hr=12;
            state=1;

			LCD_write_string_pos("PM",0,9);

			LCD_write_no_pos(sec,0,7);
			LCD_write_no_pos(0,0,6);

			LCD_write_no_pos(min,0,4);
			LCD_write_no_pos(0,0,3);

			LCD_write_no_pos(hr,0,0);
}

if((hr==11)&&(state==1)&&(min==60)){
	        sec=0;
		    next=0;
		    min=0;
		    hr=12;
            state=0;

			LCD_write_string_pos("AM",0,9);

			LCD_write_no_pos(sec,0,7);
			LCD_write_no_pos(0,0,6);

			LCD_write_no_pos(min,0,4);
			LCD_write_no_pos(0,0,3);

			LCD_write_no_pos(hr,0,0);
}

}
}
void time_value(void){
	static U16 count=0;

	count++;

	if(count==desired_count){
		sec++;
		restart_count();
		count=0;

	}
	}

