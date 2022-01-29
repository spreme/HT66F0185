#ifndef INIT_H_
#define INIT_H_

#include "HT66F0185.h"

#define 	u8			unsigned char
#define 	s8			signed char

#define 	u16			unsigned int
#define 	s16			signed int

#define     ENABLE        0X01             //1:ʹ��
#define     DISABLE       0X00             //0:����

#define     SET           0X01                //1��SET
#define     RESET         0X00                //0��RESET

//==============LED�ƿ������Ŷ���===================//
#define  	LED1  				_pc0       
#define  	LED2  				_pc1
#define  	LED3  				_pc2
#define  	LED4  				_pc3
#define  	LED5  				_pc4
#define  	LED6  				_pc5
#define  	LED7  				_pc6
#define   LED8          _pa1

//==============����ܿ������Ŷ���===================//

//==============�����������Ŷ���===================//


//==============���������Ŷ���===================//
#define   buz           _pb4
/******************************************************************************************/
/*---------------------�����־λ-----------------------*/
typedef union uFLG{
    u8 Flg ;     //������������           �������Ա
    struct FLAG{        //λ����
        u8   Flg1   : 1;
        u8   Flg2   : 1;
        u8   Flg3   : 1;
        u8   Flg4   : 1;
        u8   Flg5   : 1;
        u8   Flg6   : 1;
        u8   Flg7   : 1;
        u8   Flg8   : 1;
    }tFlg;  
}uFlg;
uFlg uF1,uF2,uF3;  //�������������
//===========����Ϊ������ͽṹ���÷�===================// 

//============����ʱ���־λ===================//
#define uFlagtime          uF1.Flg

#define t10msflag          uF1.tFlg.Flg1
#define t20msflag          uF1.tFlg.Flg2
#define t100msflag         uF1.tFlg.Flg3
#define t500msflag         uF1.tFlg.Flg4
#define buzflag            uF1.tFlg.Flg5
#define t1sflag            uF1.tFlg.Flg6
#define t10sflag           uF1.tFlg.Flg7
#define countmsflag        uF1.tFlg.Flg8

//===========���尴����־λ===================//
#define uFlag2       	   uF2.Flg

#define keysstflag       uF2.tFlg.Flg2
#define keydownflag		   uF2.tFlg.Flg3
#define keysetflag		   uF2.tFlg.Flg4
#define keyupflag		     uF2.tFlg.Flg5
#define keyallflag		   uF2.tFlg.Flg6
#define keyconflag		   uF2.tFlg.Flg7
#define keynullflag		   uF2.tFlg.Flg1
#define min5flag		     uF2.tFlg.Flg8

//===========����������־λ===================//
#define uFlag3             uF3.Flg

#define buzopen			       uF3.tFlg.Flg1
#define alwaysflag         uF3.tFlg.Flg2
#define intflag            uF3.tFlg.Flg3
#define hz50flag           uF3.tFlg.Flg4
#define warmflag           uF3.tFlg.Flg5
#define warmjsflag         uF3.tFlg.Flg6
#define pekjsflag          uF3.tFlg.Flg7
#define lightflag          uF3.tFlg.Flg8

//==============��������ͱ���==================//
volatile u16 tms;
volatile u8 tms1;
volatile u8 tms2;
volatile u8 tms3;
volatile u8 tms4;
volatile u8 t10s;
volatile u8 t2s;

volatile u8 data;
volatile u8 step;
volatile u8 step1;
volatile u8 step2;
volatile u8 step3;
volatile u8 keystep;
volatile s8 value;

//==============���ϱ�����ʾ���Ա�ĳЩ������δ֪�����ظ���==================//

u8 bbRam;
u16 bbTime;
u8 bbCnt;

s8 bBbSound;

//#define BB(A,B,C)			{bbRam=A; bbTime=B; bbCnt=30;bBbSound=bbTime;buzopen=1;alwaysflag=C;}
#define BBB(A,B,C)			{bbRam=A; bbTime=B;bbCnt=70;/*alwaysflag=C;*/}

/****************************************************************************************
=========================================================================================
����ܱ��4λ����ܣ���5��com�ڣ�����һλ��ʾ����ַ�
��ֵ��  0	 1	   2 	3	4	  5   6    7    8    9     a   b    c    d    e    f
������ 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e    ,0xff, 0xfd, 0xfb, 0xef, 0Xdf
������ 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71    ,0x00, 0x02, 0x04, 0x10, 0X20
========================================================================================
******************************************************************************************/
 //			     ��ֵ��  0	   1	 2 	 3	  4	    5   6    7    8    9     A   B    C    D    E    F    ����  ¯1s  ¯1  ¯2s  ¯2    ��
//const static u8 num[21]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e ,0xff, 0xfd, 0xfb, 0xef, 0Xdf};																								                        
const static u8 num[21]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71 ,0x00, 0x02, 0x04, 0x10, 0x20};
//                ��ţ�  0 	1	 2    3   4     5    6   7     8    9   10   11   12   13   14   15     16    17    18   19     20    21
/****************************************************************************************/
typedef enum
{
  GPIO_Pin_0    = ((u8)0x01),   /*!< Pin 0 selected */
  GPIO_Pin_1    = ((u8)0x02),   /*!< Pin 1 selected */
  GPIO_Pin_2    = ((u8)0x04),   /*!< Pin 2 selected */
  GPIO_Pin_3    = ((u8)0x08),   /*!< Pin 3 selected */
  GPIO_Pin_4    = ((u8)0x10),   /*!< Pin 4 selected */
  GPIO_Pin_5    = ((u8)0x20),   /*!< Pin 5 selected */
  GPIO_Pin_6    = ((u8)0x40),   /*!< Pin 6 selected */
  GPIO_Pin_7    = ((u8)0x80),   /*!< Pin 7 selected */
  GPIO_Pin_LNib = ((u8)0x0F),   /*!< Low nibble pins selected */
  GPIO_Pin_HNib = ((u8)0xF0),   /*!< High nibble pins selected */
  GPIO_Pin_All  = ((u8)0xFF)    /*!< All pins selected */
}GPIO_Pin_TypeDef;

typedef enum
{
  GPIO_Mode_INT      = (u8)0x01,   
  GPIO_Mode_OUT      = (u8)0x00,  

}GPIO_Mode_TypeDef;


#endif