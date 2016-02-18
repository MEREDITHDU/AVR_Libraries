/*
 * Timer0.h
 *
 * Created: 2016/2/17 10:26:03
 *  Author: WuhanStudio
 */ 

#include <avr/interrupt.h>

#ifndef TIMER0_H_
#define TIMER0_H_

void TC0_init()
{
	SREG = 0x80;    // �����ж�
	TIMSK = 0x01;   // ��T/C0����ж�
	TCNT0 = 99;		// ��ֵ
	TCCR0 = 0x05;	// T/C0Ԥ��Ƶ��1/1024
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 99;
	// �ն˳���
}

#endif /* TIMER0_H_ */