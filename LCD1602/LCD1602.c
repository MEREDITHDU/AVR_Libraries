/*
 * LCD1602.c
 *
 * Created: 2016/2/17 8:42:03
 *  Author: WuhanStudio
 */ 
#include "LCD1602.h"

/**
	LCD1602д������
**/
void LCD_write_data(unsigned char data) 
{
	RS_SET;
	RW_CLR;
	EN_SET;
	Data_IO = data;
	_delay_ms(5);
	EN_CLR;
}

/**
	LCD1602д������
**/
void LCD_write_com(unsigned char com) 
{	
	RS_CLR;
	RW_CLR;
	EN_SET;
	Data_IO = com;
	_delay_ms(5);
	EN_CLR;
}

/**
	LCD1602��ʼ��
**/
void LCD_init(void) 
{
	Data_IO = 0xFF;				       //��ƽ����
	Data_DDR = 0xFF;				   //�������
	PORTA = 0xFF;                      //��ƽ����
	DDRA = 0xFF;                       //���������1602Һ�������߶˿�����	
	
	LCD_write_com(0x38);				//��ʾģʽ����
	_delay_ms(5);
	LCD_write_com(0x08);				//��ʾ�ر�
	_delay_ms(5);
    LCD_write_com(0x01);				//��ʾ����
	_delay_ms(5);
    LCD_write_com(0x06);				//��ʾ����ƶ�����
	_delay_ms(5);
	LCD_write_com(0x0C);				//��ʾ�����������
    _delay_ms(5);
}

/**
	LCD1602����
**/
void LCD_clear(void) 
{
	LCD_write_com(0x01);
	_delay_ms(5);
}

/**
	LCD1602��ʾһ���ַ�
**/
void LCD_write_char(unsigned char x,unsigned char y,char data) 
{
    if (y == 0) 
    	LCD_write_com(0x80 + x);
    else 
    	LCD_write_com(0xC0 + x);
    LCD_write_data(data);  
}

/**
	LCD1602��ʾһ���ַ���
**/
void LCD_write_str(unsigned char x,unsigned char y,char *s) 
{	
    if (y == 0) 
    	LCD_write_com(0x80 + x);
    else 
    	LCD_write_com(0xC0 + x);    
    while (*s) 
    {
    	LCD_write_data( *s);
    	s ++;
    }
}