/*
 * DS1820.h
 *
 * Created: 2016/2/18 8:55:40
 *  Author: WuhanStudio
 */ 


#ifndef DS1820_H_
#define DS1820_H_
#include "avr/io.h"
#define F_CPU 16000000UL
#include <util/delay.h>

//DS18B20���ƶ˿ڶ��壬������PF3��
#define DQ_IN	        DDRF &= ~(1 << PF3)		//�������룬DS18B20�ӵ�Ƭ��PF3��
#define DQ_OUT	        DDRF |= (1 << PF3)		//�������
#define DQ_CLR	        PORTF &= ~(1 << PF3)	//�õ͵�ƽ
#define DQ_SET	        PORTF |= (1 << PF3)		//�øߵ�ƽ
#define DQ_R	        PINF & (1 << PF3)		//����ƽ

unsigned char DS18B20_Reset();                //��ʼ���͸�λ

unsigned char DS18B20_read_byte();
void DS18B20_write_byte(unsigned char value);

void DS18B20_start();
unsigned int DS18B20_read_temp();
void data_do(unsigned int temp_d);

#endif /* DS1820_H_ */