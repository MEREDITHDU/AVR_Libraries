/*
 * EEPROM.h
 *
 * Created: 2016/2/16 14:36:10
 *  Author: WuhanStudio
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#define F_CPU 16000000UL
#include <util/delay.h>

/**
	��ָ����EEPROM��ַ������һ���ֽ�
**/
char read_char_eeprom(unsigned int EPADD);

/**
	��ָ����EEPROM��ַ��д��һ���ֽ�
**/
void write_char_eeprom(unsigned int EPADD, char EPDATA);

/**
	��ָ����EEPROM��ַ��д��һ���ַ���
**/
char * read_str_eeprom(unsigned int EPADD,unsigned int length);

/**
	��ָ����EEPROM��ַ������һ���ַ���
**/
void write_str_eeprom(unsigned int EPADD,char* EPDATA);

char * DATA;
#endif /* EEPROM_H_ */