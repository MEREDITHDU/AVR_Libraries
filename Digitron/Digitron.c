/*
 * Digitron.c
 *
 * Created: 2016/2/18 9:16:13
 *  Author: WuhanStudio
 */ 
#include "Digitron.h"

//********����ֵ������******************//
void LED_process(unsigned int i,unsigned char *p)
{
	p[0]=i/1000;//ǧλ
	p[1]=i/100%10;//��λ
	p[2]=i/10%10;//ʮλ
	p[3]=i%10;//��λ
}

//**********��̬��ʾ����,����pΪ����ʾ��������**********//
void LED_display(unsigned char *p)
{
	unsigned char i,sel=0x01;//��λ:0x01��λ:0x10
	LED_DDR_SEL=0x0f;//��λ:0x0f��λ:0xf0
	LED_DDR_DATA=0xff;
	for (i=0;i<4;i++)
	{
		LED_SEL=sel;//PAΪλѡ,����:LED_SEL=sel;����:LED_SEL=~sel;
		LED_DATA=~LED_table[p[i]];
		//���ͱ�,����:LED_DATA=~LED_table[p[i]];����:LED_DATA=LED_table[p[i]];
		_delay_ms(2);
		sel=sel<<1;
	}
}

//**********����ܳ�ʼ������**********/
/*
void LED_init(void)
{
	LED_SEL|=0x0f;
	LED_DDR_SEL|=0x0f;
}
*/

//**********�������ʾ���ú���**********//
void LED(unsigned int i)
{
	LED_process(i,LED_dp);
	LED_display(LED_dp);

}