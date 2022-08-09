/*
 * Timer_0_ov_private.h
 *
 *  Created on: Oct 22, 2021
 *      Author: mwael
 */

#ifndef TIMER_0_OV_PRIVATE_H_
#define TIMER_0_OV_PRIVATE_H_
#define TCCR0 *((volatile U8*)0X53)
#define TCNT0 *((volatile U8*)0X52)
#define TIMSK *((volatile U8*)0X59)
#define SREG *((volatile U8*)0X5F)
#define OCR0 *((volatile U8*)0X5C)

#endif /* TIMER_0_OV_PRIVATE_H_ */
