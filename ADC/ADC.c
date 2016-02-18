/*
 * ADC.c
 *
 * Created: 2016/2/17 16:36:09
 *  Author: WuhanStudio
 */ 

#include "ADC.h"

void ADC_init()
{
	ADMUX = 0x40;			   // ����Ҷ��룬AVCCΪ��׼��ѹ��*ͨ��0*
	ADCSRA = 0xA7;			   // 128Ԥ��Ƶ����ֹ�жϣ�ʹ���Զ�ת��
	SFIOR = 0x00;		       // ����ת��ģʽ
	_delay_ms(1);
	ADCSRA = ADCSRA | 0x40;   // ����һ��ADת�� 
}

float ADC_Convert()
{
	float CVAL;
	unsigned int TEMP = 0;
	
	AL = ADCL;
	AH = ADCH;
	
	TEMP = TEMP|AH;
	TEMP = TEMP<<8;
	TEMP = TEMP|AL;
	
	CVAL = TEMP;				// ת�����Ϊ0-1023
	CVAL = CVAL*5/1023*1000;
	
	return CVAL; 
}