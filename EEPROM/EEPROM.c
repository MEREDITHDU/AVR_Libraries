/*
 * EEPROM.c
 *
 * Created: 2016/2/16 14:21:32
 *  Author: WuhanStudio
 */ 
#include <avr/io.h>
#include "EEPROM.h"
char read_char_eeprom(unsigned int EPADD)
{
	while((EECR&0x02)==1);  // �ȴ���һ��д��������
	EEAR = EPADD;			// ���õ�ַ
	EECR |= 0x01;			// ����������
	return EEDR;
}

void write_char_eeprom(unsigned int EPADD,char EPDATA)
{
	while((EECR&0x02)==1); // �ȴ���һ��д��������
	EEAR = EPADD;		   // ���õ�ַ	
	EEDR = EPDATA;		   // ��������
	EECR |= 0x04;		   // ��дʹ��
	EECR |= 0x02;          // ����д����
}

char * read_str_eeprom(unsigned int EPADD,unsigned int length)
{
	if(length==0) length = 50;
	unsigned int count = 0;	
	char temp[length];
	DATA = temp;
	
	while(read_char_eeprom(EPADD)!='\0'&& count<length)
	{
		temp[count] = read_char_eeprom(EPADD);				
		count++;
		EPADD++;
	}
	temp[count] = '\0';
	return DATA;
}

void write_str_eeprom(unsigned int EPADD,char* EPDATA)
{
	while(*EPDATA!='\0')
	{ 
		write_char_eeprom(EPADD,*EPDATA);
		EPADD++;
		EPDATA++;	
		_delay_ms(10);
	}
}