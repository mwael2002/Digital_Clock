/*
 * Timer_0_ov_private.h
 *
 *  Created on: Oct 22, 2021
 *      Author: mwael
 */

#ifndef TIMER_0_OV_PRIVATE_H_
#define TIMER_0_OV_PRIVATE_H_
#define TCCR0 *((U8*)0X53)
#define TCNT0 *((U8*)0X52)
#define TIMSK *((U8*)0X59)
#define SREG *((U8*)0X5F)

#endif /* TIMER_0_OV_PRIVATE_H_ */
