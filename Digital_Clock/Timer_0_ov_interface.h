/*
 * Timer_0_ov_interface.h
 *
 *  Created on: Oct 22, 2021
 *      Author: mwael
 */

#ifndef TIMER_0_OV_INTERFACE_H_
#define TIMER_0_OV_INTERFACE_H_
void Timer_ov_init(U16 time_millisec);
U32 time_calculate(U16 time_millisecond);
void restart_count(void);
void callback(void(*ptr)(void));
void __vector_11(void) __attribute__((signal));
#endif /* TIMER_0_OV_INTERFACE_H_ */
