/*
 * PWM.c
 *
 * Created: 2016/2/17 9:34:40
 *  Author: WuhanStudio
 */ 
#include "PWM.h"

void PWM_init()
{
	TCCR0 = 0x61;  // ��λ����PWMģʽ
}

/**
	OC0 �������PWM��
**/
void PWM(unsigned int value)
{
	OCR0 = value;
}