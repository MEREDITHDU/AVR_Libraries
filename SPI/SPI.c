/*
 * SPI.c
 *
 * Created: 2016/2/17 16:46:42
 *  Author: WuhanStudio
 */ 

#include "SPI.h"

void SPI_init()
{
	DDRB |= 0xF0;		// ��PB4-PB7����Ϊ�����MISO������ģʽ�»��Զ����ó�����
	SPCR = 0x53;		// ��λ���ȣ�ʱ������ 1/128 FOSC, SPI ģʽ 0
	SPSR = 0x00;		
}

void tran_SPI(unsigned char DATA)
{
	SPDR = DATA;				// ��ֵд��SPDR
	while((	SPSR&0X80)==0);		// �ȴ�SPIF��1
	SPI_TEMP = SPDR;				// ����SPDR���յ������ݣ�����������SPIFλ
}

void write_char(unsigned char ADD,unsigned char SA_DATA)
{
	SS_SET;					// ����Ƭѡ
	_delay_us(2);
	tran_SPI(0x02);        // д���� 101+ADD
	tran_SPI(0x80|ADD);	   // 10λ�����Ҫ������д��
	tran_SPI(SA_DATA);	   // д������
	SS_CLR;				   // ����Ƭѡ��оƬ�ڲ���ʼ��д����
	_delay_ms(5);
}

unsigned char read_char(unsigned char ADD)
{
	SS_SET;
	_delay_us(2);
	tran_SPI(0x03);		// д���� 110+ADD
	tran_SPI(ADD);		// 10λ���Ҫ������д��
	
	SPCR=0x57;
	tran_SPI(0x00);
	SPCR = 0x53;
	SS_CLR;
	
	return SPI_TEMP;
}

