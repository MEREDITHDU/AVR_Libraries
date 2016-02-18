/*
 * USART.h
 *
 * Created: 2016/2/16 16:20:17
 *  Author: WuhanStudio
 */ 


#ifndef USART_H_
#define USART_H_
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
#define F_CPU 16000000UL

#define BAUDRATE           9600                                     //���ò����ʵĴ�С
#define BAUD_SETTING   (uint)((ulong)F_CPU/(16*(ulong)BAUDRATE)-1)  //�����ʼ��㹫ʽ
#define BAUDRATE_H         (uchar)(BAUD_SETTING>>8)                 //��ȡ��λ
#define BAUDRATE_L         (uchar)(BAUD_SETTING) 
void USART_init();

char read_char_USART();
void send_char_USART(char DATA);

char * read_str_USART(unsigned int length);
void send_str_USART(char * DATA);

char * uDATA;

#endif /* USART_H_ */