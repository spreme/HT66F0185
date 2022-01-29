#ifndef INIT_H_
#define INIT_H_

#include "HT66F0185.h"

#define 	u8			unsigned char
#define 	s8			signed char

#define 	u16			unsigned int
#define 	s16			signed int

#define     ENABLE        0X01             //1:ʹ��
#define     DISABLE       0X00             //0:����

#define     SET        0X01                //1��SET
#define     RESET      0X00                //0��RESET


//==============����ܶ�ѡ�������Ŷ���===================//
#define  	a  				_pc0       
#define  	b  				_pc1
#define  	c  				_pc2
#define  	d  				_pc3
#define  	e  				_pc4
#define  	f  				_pc5
#define  	g  				_pc6
#define   dp        _pa1

//==============�����λѡ�������Ŷ���===================//
#define  	bitcode1  		_pd0        
#define  	bitcode2  	  _pd1 
#define  	bitcode3  	  _pd2
#define  	bitcode4  		_pd3

//==============�����������Ŷ���===================//
#define 	keydown   			  _pb4     //����0 ����1
#define 	keydownmode   	  _pbc4    //0��� 1����
#define 	keydownmodepu   	_pbpu4   //����/��������������� 0������  1��ʹ��

#define 	keyset   			    _pb3
#define 	keysetmode   		  _pbc3
#define 	keysetmodepu   		_pbpu3

#define 	keyup    			    _pb2
#define 	keyupmode     		_pbc2
#define 	keyupmodepu     	_pbpu2
//==============�̵������������Ŷ���===================//
#define   buz                _pa7

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
uFlg uF1,uF2,uF3,uF4,uF5,uF6,uF7,uF8;  //�������������
//===========����Ϊ������ͽṹ���÷�===================// 

//============����ʱ���־λ===================//
#define uFlagtime          uF1.Flg

#define t10msflag          uF1.tFlg.Flg1
#define t20msflag          uF1.tFlg.Flg2
#define t100msflag         uF1.tFlg.Flg3
#define t500msflag         uF1.tFlg.Flg4
//#define buzflag            uF1.tFlg.Flg5
#define t10msflag1         uF1.tFlg.Flg6
#define t10sflag           uF1.tFlg.Flg7
#define countmsflag        uF1.tFlg.Flg8



//===========���尴����־λ===================//
#define uFlag2       	   uF2.Flg

#define keysstflag         uF2.tFlg.Flg2
#define keydownflag		   uF2.tFlg.Flg3
#define keysetflag		   uF2.tFlg.Flg4
#define keyupflag		   uF2.tFlg.Flg5
#define keyallflag		   uF2.tFlg.Flg6
#define keyconflag		   uF2.tFlg.Flg7
#define keynullflag		   uF2.tFlg.Flg1
#define min5flag		   uF2.tFlg.Flg8

//===========����������־λ===================//
#define uFlag3             uF3.Flg

#define buzopen			   uF3.tFlg.Flg1
#define alwaysflag         uF3.tFlg.Flg2
#define intflag            uF3.tFlg.Flg3
#define hz50flag           uF3.tFlg.Flg4
#define warmflag           uF3.tFlg.Flg5
#define warmjsflag         uF3.tFlg.Flg6
#define pekjsflag          uF3.tFlg.Flg7
#define lightflag          uF3.tFlg.Flg8

//��һλ�����
#define Digbuff1           uF4.Flg

#define Dig1a              uF4.tFlg.Flg1//
#define Dig1b              uF4.tFlg.Flg2//
#define Dig1c              uF4.tFlg.Flg3
#define Dig1d              uF4.tFlg.Flg4
#define Dig1e              uF4.tFlg.Flg5//
#define Dig1f              uF4.tFlg.Flg6
#define Dig1g              uF4.tFlg.Flg7


//�ڶ�λ�����
#define Digbuff2           uF5.Flg

#define Dig2a              uF5.tFlg.Flg1//
#define Dig2b              uF5.tFlg.Flg2//
#define Dig2c              uF5.tFlg.Flg3
#define Dig2d              uF5.tFlg.Flg4
#define Dig2e              uF5.tFlg.Flg5//
#define Dig2f              uF5.tFlg.Flg6
#define Dig2g              uF5.tFlg.Flg7

//����λ�����
#define Digbuff3           uF6.Flg

#define Dig3a              uF6.tFlg.Flg1//
#define Dig3b              uF6.tFlg.Flg2//
#define Dig3c              uF6.tFlg.Flg3
#define Dig3d              uF6.tFlg.Flg4
#define Dig3e              uF6.tFlg.Flg5//
#define Dig3f              uF6.tFlg.Flg6
#define Dig3g              uF6.tFlg.Flg7

//����λ�����
#define Digbuff4           uF7.Flg

#define Dig4a              uF7.tFlg.Flg1//
#define Dig4b              uF7.tFlg.Flg2//
#define Dig4c              uF7.tFlg.Flg3
#define Dig4d              uF7.tFlg.Flg4
#define Dig4e              uF7.tFlg.Flg5//
#define Dig4f              uF7.tFlg.Flg6
#define Dig4g              uF7.tFlg.Flg7

//P
#define Digbuff5           uF8.Flg

#define Dig5a              uF8.tFlg.Flg1//
#define Dig5b              uF8.tFlg.Flg2//
#define Dig5c              uF8.tFlg.Flg3
#define Dig5d              uF8.tFlg.Flg4
#define Dig5e              uF8.tFlg.Flg5//
#define Dig5f              uF8.tFlg.Flg6
#define Dig5g              uF8.tFlg.Flg7


//==============��������ͱ���==================//
volatile s8 alarm_hour;
volatile s8 alarm_min;
volatile s8 alarm_second;

volatile s8 peking_hour;
volatile s8 peking_min;
volatile s8 peking_second;

volatile s8 peking_second1;
volatile s8 peking_min1;

volatile s8 bj_min;
volatile s8 bj_second;


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

volatile u16 sum;
volatile u16 sum1;

volatile u8 wei;

volatile u8 num1=1;
volatile u8 num2=2;
volatile u16 num3;
volatile u16 num4;

//==============���ϱ�����ʾ���Ա�ĳЩ������δ֪�����ظ���==================//

u8 bbRam;
u16 bbTime;
u8 bbCnt;
s8 bBbSound;

//#define BB(A,B,C)			{bbRam=A; bbTime=B; bbCnt=30;bBbSound=bbTime;buzopen=1;alwaysflag=C;}
#define BBB(A,B,C)			{bbRam=A; bbTime=B;bbCnt=C;/*alwaysflag=C;bbCnt=70*/} 

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
const static u8 num[21]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71 ,0x00, 0x02, 0x04, 0x10, 0x20};//                ��ţ�  0 	1	 2    3   4     5    6   7     8    9   10   11   12   13   14   15     16    17    18   19     20    21
/****************************************************************************************/

//#define  GPIO_Pin_0     ((u8)0x01)   /*!< Pin 0 selected */
//#define  GPIO_Pin_1     ((u8)0x02)   /*!< Pin 1 selected */
//#define  GPIO_Pin_2     ((u8)0x04)   /*!< Pin 2 selected */
//#define  GPIO_Pin_3     ((u8)0x08)   /*!< Pin 3 selected */
//#define  GPIO_Pin_4     ((u8)0x10)   /*!< Pin 4 selected */
//#define  GPIO_Pin_5     ((u8)0x20)   /*!< Pin 5 selected */
//#define  GPIO_Pin_6     ((u8)0x40)   /*!< Pin 6 selected */
//#define  GPIO_Pin_7     ((u8)0x80)   /*!< Pin 7 selected */
//#define  GPIO_Pin_LNib  ((u8)0x0F)   /*!< Low nibble pins selected */
//#define  GPIO_Pin_HNib  ((u8)0xF0)   /*!< High nibble pins selected */
//#define  GPIO_Pin_All   ((u8)0xFF)    /*!< All pins selected */
//
//
//#define  GPIO_Mode_In       (u8)0x01   
//#define  GPIO_Mode_OUT      (u8)0x00 

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