/*
 * IIC.c
 *
 * Created: 2016/2/17 16:47:09
 *  Author: WuhanStudio
 */ 

#include "IIC.h"

/*--------------------------------------------------------------------
�������ƣ�I2C Start
�����ܣ�
ע�����
��ʾ˵����
��    �룺
��    �أ�
--------------------------------------------------------------------*/
bool I2C_Start()     
{
 I2CStart();      
 I2CWaitAck();
 if( I2CChkAck()!=I2C_START ) 
  return I2C_ERR;
 return I2C_CRR;
}

/*--------------------------------------------------------------------
�������ƣ�I2C ReStart
�����ܣ�
ע�����
��ʾ˵����
��    �룺
��    �أ�
--------------------------------------------------------------------*/
bool I2C_Restart()     
{
 I2CStart();      
 I2CWaitAck();
 if( I2CChkAck()!=I2C_RESTART ) 
  return I2C_ERR;
 return I2C_CRR;
}

/*--------------------------------------------------------------------
�������ƣ�I2C(TWI)���� 7λ ����д��ַ: XXXX XXX0
�����ܣ�
ע�����
��ʾ˵����
��    �룺
��    �أ�
--------------------------------------------------------------------*/
bool I2C_SendWrDAdr(uint8 wrDAdr) 
{
 I2CSendByte(wrDAdr);   //���� ����д��ַ
 I2CWaitAck();
 if( I2CChkAck()!=I2C_MT_SLA_ACK )  
  return I2C_ERR;
 return I2C_CRR;  
}

/*--------------------------------------------------------------------
�������ƣ�I2C(TWI)���� 10λ ����д��ַ: 1111 0XX0, XXXX XXXX
�����ܣ�
ע�����
��ʾ˵�������� ���� 7λ ����д��ַ: XXXX XXX0
��    �룺
��    �أ�
--------------------------------------------------------------------*/
bool I2C_SendWrDAdr_(uint16 wrDAdr) 
{
 if( (wrDAdr&0xF000) == 0xF000 )						//�ж��Ƿ�Ϊ 10λ ������ַ
  if( I2C_SendWrDAdr( (uint8)wrDAdr>>8 )==I2C_ERR )		//���� ����λ������д��ַ
   return I2C_ERR;
 if( I2C_SendWrDAdr( (uint8)wrDAdr )==I2C_ERR )			//���� ����λ������д��ַ
  return I2C_ERR;
 return I2C_CRR;
}

/*--------------------------------------------------------------------
�������ƣ�I2C(TWI)���� 7λ ��������ַ: XXXX XXX1
�����ܣ�
ע�����
��ʾ˵����
��    �룺
��    �أ�
--------------------------------------------------------------------*/
bool I2C_SendRdDAdr(uint8 rdDAdr) 
{
 I2CSendByte(rdDAdr);   //���� ��������ַ
 I2CWaitAck();
 if( I2CChkAck()!=I2C_MR_SLA_ACK )  
  return I2C_ERR;
 return I2C_CRR; 
}

/*--------------------------------------------------------------------
�������ƣ�I2C(TWI)���� 10λ ��������ַ: 1111 0XX0, XXXX XXXX
�����ܣ�
ע�����
��ʾ˵����
��    �룺
��    �أ�
--------------------------------------------------------------------*/
bool I2C_SendRdDAdr_(uint8 rdDAdr) 
{
 if( (rdDAdr&0xF000) == 0xF000 )						//�ж��Ƿ�Ϊ 10λ ������ַ
  if( I2C_SendWrDAdr( (uint8)rdDAdr>>8 )==I2C_ERR )		//���� ����λ����������ַ
   return I2C_ERR;
 if( I2C_SendWrDAdr( (uint8)rdDAdr )==I2C_ERR )			//���� ����λ����������ַ
  return I2C_ERR;
 return I2C_CRR;
}

/*--------------------------------------------------------------------
�������ƣ�I2C(TWI)��������
�����ܣ�
ע�����
��ʾ˵����
��    �룺
��    �أ�
--------------------------------------------------------------------*/
bool I2C_SendDat(uint8 configDat) 
{
 I2CSendByte(configDat);   
 I2CWaitAck();
 if( I2CChkAck()!=I2C_MT_DATA_ACK ) 
  return I2C_ERR;
 return I2C_CRR; 
}

/*--------------------------------------------------------------------
�������ƣ�I2C(TWI)���������Ҳ�����Ӧ��
�����ܣ�
ע�����
��ʾ˵����
��    �룺
��    �أ�
--------------------------------------------------------------------*/
bool I2C_RcvNAckDat(uint8 *pRdDat) 
{
 I2CRcvNckByte();
 I2CWaitAck();
 if( I2CChkAck()!=I2C_MR_DATA_NACK )
  return I2C_ERR;
 *pRdDat=TWDR;
 return I2C_CRR;
}

/*--------------------------------------------------------------------
�������ƣ�I2C(TWI)���������Ҳ���Ӧ��
�����ܣ�
ע�����
��ʾ˵����
��    �룺
��    �أ�
--------------------------------------------------------------------*/
bool I2C_RcvAckDat(uint8 *pRdDat) 
{
 I2CRcvAckByte();     
 I2CWaitAck();
 if( I2CChkAck()!=I2C_MR_DATA_ACK )
  return I2C_ERR;
 *pRdDat=TWDR;
 return I2C_CRR;
}

/*--------------------------------------------------------------------
�������ƣ�I2C(TWI)д������дһ������
�����ܣ�
ע�����
��ʾ˵����
��    �룺wrDAdr: write device-address д������ַ
   wordAdr: word address �ֵ�ַ
   dat: data ����
��    �أ�
--------------------------------------------------------------------*/
bool I2C_Write(uint16 wrDAdr,uint8 wordAdr,uint8 dat)
{
 if( I2C_Start()==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendWrDAdr_(wrDAdr)==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendDat(wordAdr)==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendDat(dat)==I2C_ERR )
  return I2C_ERR;

 I2C_Stop();

 return I2C_CRR;
}

/*--------------------------------------------------------------------
�������ƣ�I2C(TWI)д������дN������
�����ܣ�
ע�����
��ʾ˵����
��    �룺wrDAdr: write device-address д������ַ
   wordAdr: word address �ֵ�ַ
   *pWrDat: p->write data д������ָ��
   num: number д�����ݸ���
��    �أ�
--------------------------------------------------------------------*/
//bool I2C_Write_(uint16 wrDAdr,uint8 wordAdr,
//      uint8 *pWrDat,uint8 num)
//{
//
//} 

/*--------------------------------------------------------------------
�������ƣ�I2C(TWI)����������һ������
�����ܣ�
ע�����
��ʾ˵����
��    �룺wrDAdr: write device-address д������ַ
   wordAdr: word address �ֵ�ַ
   rdDAdr: read device-address ��������ַ
   *pRdDat: p->read data ��ȡ����ָ��
��    �أ�
--------------------------------------------------------------------*/
bool I2C_Read(uint16 wrDAdr,uint8 wordAdr,
     uint8 rdDAdr,uint8 *pRdDat)
{
 if( I2C_Start()==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendWrDAdr_(wrDAdr)==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendDat(wordAdr)==I2C_ERR )
  return I2C_ERR;

 if( I2C_Restart()==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendRdDAdr(rdDAdr)==I2C_ERR )
  return I2C_ERR;

 if( I2C_RcvNAckDat(pRdDat)==I2C_ERR )
  return I2C_ERR;

 I2C_Stop();

 return I2C_CRR;
}

/*--------------------------------------------------------------------
�������ƣ�I2C(TWI)����������N������
�����ܣ�
ע�����
��ʾ˵����
��    �룺wrDAdr: write device-address д������ַ
   wordAdr: word address �ֵ�ַ
   rdDAdr: read device-address ��������ַ
   *pRdDat: p->read data ��ȡ����ָ��
   num: number ��ȡ���ݸ���
��    �أ�
--------------------------------------------------------------------*/
bool I2C_Read_(uint16 wrDAdr,uint8 wordAdr,
      uint8 rdDAdr,uint8 *pRdDat,uint8 num)
{
  uint8 i;
 
 if( I2C_Start()==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendWrDAdr_(wrDAdr)==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendDat(wordAdr)==I2C_ERR )
  return I2C_ERR;

 if( I2C_Restart()==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendRdDAdr(rdDAdr)==I2C_ERR )
  return I2C_ERR;

 for(i=0;i<num-1;i++)
  if( I2C_RcvAckDat(pRdDat+i)==I2C_ERR )
   return I2C_ERR;
 
 if( I2C_RcvNAckDat(pRdDat+i)==I2C_ERR )
   return I2C_ERR;

 I2C_Stop();
 
 return I2C_CRR;
}