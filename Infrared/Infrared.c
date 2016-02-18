/*
 * Infrared.c
 *
 * Created: 2016/2/18 9:05:25
 *  Author: WuhanStudio
 */ 

#include "Infrared.h"

//***********************************************************************
//			���������
//***********************************************************************
uchar key;
uint temp_value;
uint temp,A;             		      	//����ı���,��ʾ���ݴ���
uchar code_value=0;
uchar key_code[4]; 
uint l,p;

//***********************************************************************
//			ң��������
//***********************************************************************

#define KEY_0     0x16                 //��0
#define KEY_1     0x0C                 //��1
#define KEY_2     0x18                 //��2
#define KEY_3     0x5E                 //��3
#define KEY_4     0x08                 //��4
#define KEY_5     0x1C                 //��5
#define KEY_6     0x5A                 //��6
#define KEY_7     0x42                 //��7
#define KEY_8     0x52                 //��8
#define KEY_9     0x4A                 //��9
#define KEY_POWER 0x45                 //��Դ
#define KEY_MODE  0x46                 //ģʽ
#define KEY_SOUND 0x47                 //����


//***********************************************************************
//			IO�˿ڳ�ʼ��
//***********************************************************************

void Infrared_init()
{
    RED_SET;
	RED_IN;
}

//*************************************************************************
//	    ��ʾ�ɼ��������ݵ�LED��
//*************************************************************************

void Display_Key(uint data_KEY)
{   
    //LED = data_KEY;      //��ֵ��ʾ��LED���ϣ������Ƶ���ʽ��ʾ��ֻʶ��0~9
	//LCD_write_char(0x0e,1,0X30+data_KEY);
}

//*************************************************************************
//			ң������ֵ������ֵ�ӳ���
//*************************************************************************
 void Key_Icode(void)
 {
   switch(key_code[2])
   {
    case KEY_0:key=0;break;
	case KEY_1:key=1;break;
	case KEY_2:key=2;break;
	case KEY_3:key=3;break;
	case KEY_4:key=4;break;
	case KEY_5:key=5;break;
	case KEY_6:key=6;break;
	case KEY_7:key=7;break;
	case KEY_8:key=8;break;
	case KEY_9:key=9;break;
	default:key=10;break;
   }
 }

//*************************************************************************
//			ң���������ӳ���
//*************************************************************************

void Red_Code()
{
	uchar i,j,k = 0;
	for(i = 0;i < 19;i++)
	{
		_delay_us(400);           //��ʱ400us
		if(RED_R)                //9ms���иߵ�ƽ�����ж�Ϊ���ţ��˳��������
			return;
	}
	
	while(!RED_R);            //�ȴ�9ms�͵�ƽ��ȥ

	for(i=0;i<5;i++)          //�Ƿ�������
	{
	  _delay_us(500);
	  if(!RED_R)
		 return;
	}

	while(RED_R);               //�ȴ�4.5ms�ߵ�ƽ��ȥ

	for(i = 0;i < 4;i++)        //����4���ֽڵ�����
	{
		for(j = 0;j < 8;j++)      //ÿ���ֽڵ�����8λ
		{
			while(!RED_R);         //�ȴ���ߵ�ƽ
			while(RED_R)           //����ߵ�ƽʱ��
			{
				_delay_us(100);
				k++;
				if(k >= 22)           //�ߵ�ƽʱ����������˳��������
					return;              
			}
			code_value>>=1;        //����һλ����
			if(k >= 8)
				code_value|=0x80;   	//�ߵ�ƽʱ�����0.56����Ϊ����1
			k = 0;                  //��ʱ����
		}
		key_code[i]=code_value;  //�ĸ��ֽڵ�����
	}
	
	Key_Icode();             //���ø�ֵ����
	Display_Key(key);        //��ʾ����ֵ 
}