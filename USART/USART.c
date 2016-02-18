/*
 * USART.c
 *
 * Created: 2016/2/16 16:20:07
 *  Author: WuhanStudio
 */ 
#include <avr/io.h>
#include "USART.h"

/**
	���ڳ�ʼ������
**/
void USART_init()
{
  UCSR0A=0x00;                                 //������ģʽ 
  UCSR0B=0x18;                                 //�����ж��������ͽ����ͼĴ������жϹرգ����ò�ѯ����ģʽ
  UCSR0C=0x86;                                 //�첽���ڣ���У��λ��1ֹͣλ��8����λ                                
  UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);              //дUCSRC�Ĵ���,�첽ͨ����У�飬8λ����1λֹͣλ 
  UBRR0H=BAUDRATE_H;                           //д�����ʵ�ֵ 
  UBRR0L=BAUDRATE_L; 
}

/**
	���ڶ�ȡһ���ַ�
**/
char read_char_USART()
{
	char TEMP = -1;
	while((UCSR0A&0x80)!=0x80);
	TEMP = UDR0;	
	return TEMP;
}

/**
	���ڷ���һ���ַ�
**/
void send_char_USART(char DATA)
{
	while(!(UCSR0A&(1<<UDRE0)));		//�ȴ����ͼĴ�����
	UDR0=DATA;							//д�뷢������
	while(!(UCSR0A&(1<<TXC0)));			//�ȴ��������
	UCSR0A|=(1<<TXC0);
}

/**
	���ڶ�ȡһ���ַ���
**/
char * read_str_USART(unsigned int length)
{
	if(length==0) length = 50;
	
	unsigned int count = 0;	
	char TEMP[length];	
	uDATA = TEMP;
	
	char READ = read_char_USART();	
	while(READ!=' ' && count<length)
	{
		TEMP[count] = READ;
		count++;
		READ = read_char_USART();
	}
	TEMP[count] = '\0';
	
	return uDATA;
}

/**
	���ڷ���һ���ַ���
**/
void send_str_USART(char * DATA)
{
	while(*DATA!='\0')
	{
		send_char_USART(*DATA);
		DATA++;
	}
}