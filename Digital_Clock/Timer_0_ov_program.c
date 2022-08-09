/*
 * Timer_0_ov_program.c
 *
 *  Created on: Oct 22, 2021
 *      Author: mwael
 */
#include"STD.Types.h"
#include"bit_calc.h"
#include"Timer_0_ov_private.h"
#include"Timer_0_ov_interface.h"
#include"LCD_interface.h"

void (*ptr_timer) (void)=0;
U16 TCNT0_register_value;


void Timer_ov_init(U16 time_milliseconds){
    time_calculate(time_milliseconds);
	TCNT0 =TCNT0_register_value;

	TCCR0 = 0b00000010;
	//prescaler=8
	//Normal mode
	set_bit(TIMSK,0); // Interrupt Enable
	set_bit(SREG,7); // Enable GIE
}
U32 time_calculate(U16 time_millisecond){
    F32 count;
    count=(1000.0*time_millisecond)/256;
    TCNT0_register_value=(256*(1-(count-(U32)count)));
    return ((U32)count+1);
}
void restart_count(void){
	TCNT0=TCNT0_register_value;
}


void callback(void(*ptr)(void)){
	ptr_timer=ptr;
}

void __vector_11(void){
ptr_timer();
}
