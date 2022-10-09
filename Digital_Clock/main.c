/*
 * main.c
 *
 *  Created on: Oct 15, 2021
 *      Author: mwael
 */
#include "STD_Types.h"
#include "DIO_interface.h"
#include "Timer_interface.h"
#include "GIE_interface.h"
#include "LCD_interface.h"
#include "Keypad_interface.h"

#define AM 13
#define PM 14

U8 sec;
U8 next;
U8 min;
U8 hr;
U8 AM_PM_state;


U8 sec;
U16 desired_count;

void time_value(void);
void set_current_time(void);

void sec_change(void);
void min_change(void);
void hour_change(void);

void main(void){


	KPD_init();
	LCD_init();

    set_current_time();

    desired_count=Overflow_time_calculate(TIMER1_ID);
    Timer1_init();
    Timer_callback(TIMER1_ID,time_value);
    Global_Int_En_Dis(Global_Int_Enable);


while(1){

sec_change();
min_change();
hour_change();

}
}


void set_current_time(void){

    U8 Entered_no=0;

	LCD_write_string_pos("Choose hour",1,0);

    for(U8 hr_count=0;hr_count<2;hr_count++){

    	do{

    		Entered_no=KPD_status();

    	}while(Entered_no==No_pressed_key);

    	hr=hr*10+Entered_no;
    	LCD_write_no_pos(Entered_no,0,hr_count);
    }



    LCD_write_string_pos("Choose minute",1,0);
    LCD_write_string_pos(":",0,2);

    for(U8 min_count=3;min_count<5;min_count++){

    	do{

    		Entered_no=KPD_status();

    	}while(Entered_no==No_pressed_key);

    	min=min*10+Entered_no;
    	LCD_write_no_pos(Entered_no,0,min_count);
    }

    LCD_write_string_pos("Choose second",1,0);
    LCD_write_string_pos(":",0,5);

    for(U8 sec_count=6;sec_count<8;sec_count++){

    	do{

    		Entered_no=KPD_status();

    	}while(Entered_no==No_pressed_key);

    	sec=sec*10+Entered_no;
    	LCD_write_no_pos(Entered_no,0,sec_count);
    }


    LCD_write_string_pos("13:AM or 14:PM",1,0);


	do{

		AM_PM_state=KPD_status();

	}while(AM_PM_state==No_pressed_key);


    LCD_clear();


	if(hr<10){
	LCD_write_no_pos(hr,0,1);
	LCD_write_no_pos(0,0,0);
		}
	else{
	LCD_write_no_pos(hr,0,0);
	}

	LCD_write_string_pos(":",0,2);

	if(min<10){
	LCD_write_no_pos(min,0,4);
    LCD_write_no_pos(0,0,3);
		}
	else{
	LCD_write_no_pos(min,0,3);
	}

	LCD_write_string_pos(":",0,5);

	if(sec<10){
	LCD_write_no_pos(sec,0,7);
	LCD_write_no_pos(0,0,6);
	}

	else{
    LCD_write_no_pos(sec,0,6);
	}

    if(AM_PM_state==AM){
	LCD_write_string_pos("AM",0,9);
	}
	else{
	LCD_write_string_pos("PM",0,9);
	}

}






void sec_change(void){
	if((sec>next)&&(sec!=60)&&(sec<10)){
		next++;
	LCD_write_no_pos(sec,0,7);
	}
	else if((sec>next)&&(sec!=60)&&(sec>9)){
		next++;
	LCD_write_no_pos(sec,0,6);
	}
}

void min_change(void){
	if((sec==60)&&(min<9)){
		sec=0;
		next=0;
		min++;
		LCD_write_no_pos(sec,0,7);
		LCD_write_no_pos(0,0,6);

		LCD_write_no_pos(min,0,4);
	}

	else if((sec==60)&&(min>8)){
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
}

void hour_change(void){

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
	else if((min==60)&&(hr>8)&&(hr<11)){
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

	else if((hr==12)&&(min==60)){
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

	else if((hr==11)&&(AM_PM_state==AM)&&(min==60)){
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

	else if((hr==11)&&(AM_PM_state==PM)&&(min==60)){
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





void time_value(void){
	static U16 count=0;

	count++;

	if(count==desired_count){
		sec++;
		Overflow_restart_count(TIMER1_ID);
		count=0;

	}
	}
