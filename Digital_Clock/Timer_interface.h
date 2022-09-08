/*
 * Timer_0_ov_interface.h
 *
 *  Created on: Oct 22, 2021
 *      Author: mwael
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


#define TIMER0_ID                                      0
#define TIMER1_ID                                      1
#define TIMER2_ID                                      2

#define CMPA                                           0
#define CMPB                                           1


void Timer0_init(void);
void Timer1_init(void);
void Timer2_init(void);

U32 Overflow_time_calculate(U8 Timer_Id);
void Overflow_restart_count(U8 Timer_Id);
void set_comparematch_value(U8 Timer_Id,U8 ctc_value);
void Timer1_set_comparematch_value(U8 Compare_Register ,U16 ctc_value);

U8 Timer_callback(U8 Timer_Id,void(*ptr)(void));

#if TIMER1_USE_CMPB==1
U8 CompareB_callback(void(*ptr)(void));
#endif

#endif /* TIMER_INTERFACE_H_ */
