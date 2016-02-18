/*
 * Infrared.h
 *
 * Created: 2016/2/18 9:05:11
 *  Author: WuhanStudio
 */ 


#ifndef INFRARED_H_
#define INFRARED_H_
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define uchar unsigned char
#define uint unsigned int

//����һ�廯����ͷ1838���ƶ˿ڶ��壬������PF2��
#define RED_IN	        DDRF &= ~(1 << PF2)		//�������룬�������ͷ�ӵ�Ƭ��PF2��
#define RED_OUT	        DDRF |= (1 << PF2)		//�������
#define RED_CLR	        PORTF &= ~(1 << PF2)	//�õ͵�ƽ
#define RED_SET	        PORTF |= (1 << PF2)		//�øߵ�ƽ
#define RED_R	        (PINF & (1 << PF2))		//����ƽ

void Infrared_init();
void Display_Key(uint data_KEY);
void Key_Icode(void);
void Red_Code();



#endif /* INFRARED_H_ */