#include "init.h"
#include "HT66F0185.h"
		
//===========================PA�˿ڳ�ʼ������=========================================//
	void GPIOA_INIT(u8 GPIO_Pin,u8 GPIO_Mode,u8 wakeup,u8 GPIO_BitVal)  //u8 Ϊ�޷����ַ���
	{
		if ((u8)GPIO_Mode == (u8)0x01)   //paΪ������ʱ
		 {
		 	_pac|=GPIO_Pin;             //��pa����GPIO_PinΪ���룬����λpac ��ͬʱ������������
		 	_papu|=GPIO_Pin;
		 }
		else
		 {
			_pac&=(u8)(~GPIO_Pin);      //��pa����Ϊ����� 
			_papu&=(u8)(~GPIO_Pin);	
		 }
		 
		if (GPIO_BitVal != RESET)       //����
		 {
		  	 _pa|=GPIO_Pin;
		 }
		else
		 {
		 	 _pa&=(u8)(~GPIO_Pin);   

		 }	 	
	}
//===========================PB�˿ڳ�ʼ������=========================================//
	void GPIOB_INIT(u8 GPIO_Pin,u8 GPIO_Mode,u8 GPIO_BitVal)
	{
		 
		if ((u8)GPIO_Mode == (u8)0x01)
		 {
		 	_pbc|=GPIO_Pin;
		 	_pbpu|=GPIO_Pin;
		 }
		else
		 {
			_pbc&=(u8)(~GPIO_Pin);
			_pbpu&=(u8)(~GPIO_Pin);	
		 }
		 
		if (GPIO_BitVal != RESET)
		 {
		  	 _pb|=GPIO_Pin;
		 }
		else
		 {
		 	 _pb&=(u8)(~GPIO_Pin);
		 }	 	
	}
//===========================PC�˿ڳ�ʼ������=========================================//
	void GPIOC_INIT(u8 GPIO_Pin,u8 GPIO_Mode,u8 GPIO_BitVal)
	{
		 
		if ((u8)GPIO_Mode == (u8)0x01)
		 {
		 	_pcc|=GPIO_Pin;
		 	_pcpu|=GPIO_Pin;
		 }
		else
		 {
			_pcc&=(u8)(~GPIO_Pin);
			_pcpu&=(u8)(~GPIO_Pin);	
		 }
		 
		if (GPIO_BitVal != RESET)
		 {
		  	 _pc|=GPIO_Pin;
		 }
		else
		 {
		 	 _pc&=(u8)(~GPIO_Pin);
		 }	 	
	}

//===========================PD�˿ڳ�ʼ������=========================================//
	void GPIOD_INIT(u8 GPIO_Pin,u8 GPIO_Mode,u8 GPIO_BitVal)
	{
		 
		if ((u8)GPIO_Mode == (u8)0x01)
		 {
		 	_pdc|=GPIO_Pin;
		 	_pdpu|=GPIO_Pin;
		 }
		else
		 {
			_pdc&=(u8)(~GPIO_Pin);
			_pdpu&=(u8)(~GPIO_Pin);	
		 }
		 
		if (GPIO_BitVal != RESET)
		 {
		  	 _pd|=GPIO_Pin;
		 }
		else
		 {
		 	 _pd&=(u8)(~GPIO_Pin);
		 }	 	
	}
	
//===========================���ݴ洢��ʹ������=========================================//
void clr_ram_en(unsigned char t)
{
	_dmbp0 = t;
	_mp1 = 0x80;
	while(_mp1!=0)
	{
		_iar1 = 0;
		_mp1++;
	}
}	
//===========================ʱ�ӳ�ʼ������=========================================//
	void Init_clock(void)
	{
	  	_smod=0x01;            //ѡ��gao��ʱ��Ϊϵͳʱ�� �ڲ�8Mhz
	  	while(!_hto);          //�ȴ�����������λ
	  	_wdtc=0x57;            //ʹ�ܿ��Ź�
	  	_acerl=0x00;		   //ȡ��A/D����
	  	_tmpc=0x00;            //ȡ�������������TM ����/ �����������ű���ԭ������
	  	_cpc=0x08;             //�Ƚ���������ڲ�ʹ��
	  	_integ=0x00;			//�����ⲿ�жϱ��ؿ��Ƴ���
	  	_int0e=0;				//INTO�жϳ���
	  	_emi = 0;   			//�ر����ж�

//=========LCD���ƼĴ��������趨Ϊ��������=====================//		
		_slcdc0 = 0;	
		_slcdc1 = 0;
		_slcdc2 = 0;
		_slcdc3 = 0;
		_slcdc4 = 0;
/***********TM0************/
	  	_tm0c0=0x10;			//ѡ��ϵͳʱ��fsys��Ϊt1ʱ��fint=8MHZ	
	  	_tm0c1=0xc1;			//��ʱģʽ��aƥ��
	  	_tm0al=0xf8;			//��ʱ��ֵ  0x5f8=1528
	  	_tm0ah=0x05;            //1528/8MHZ=191us
	  	_t0af=0;				//��t�жϱ�־λ
	  	_t0on=1;				//������ʱ
	  	_mf0e=1;				//���๦���ж�
	  	_t0ae=1;	    		//��t0�ж�
/***********ʱ��0************/	  
	  	//_tbc=0b10000111;       //ʱ����ʱ������ʹ�� fTBCʱ��Դ LXT��������
	  	//_tb0f=0;               //ʱ��0�ж������־����
	  	//_tb0e=1;               //ʱ��0�жϿ���λʹ��
	  	
	  	_emi=1;		  			//�����ж�
	  	
	  	GCC_CLRWDT();	       //������Ź�
		clr_ram_en(0);         //���ݴ洢��ѡ��BANK0
		clr_ram_en(1);         //���ݴ洢��ѡ��BANK1

	}


//===========================��ʱ��0�ж����=========================================//
	DEFINE_ISR(isr_TM0, 0x0c)   //��ʱ��0�жϺ���  191us
	{
    _t0af=0;       //t0�ж������־����
    _emi=1;        //�����ж�
    step3++;
		if(step3>5)
		 {
			step3=0;		
			bitcode1=1; 						//pb0
			bitcode2=1; 						//pb1
			bitcode3=1; 						//pb2
			bitcode4=1;							//pa4
			a=1;								//pc2
			b=1;								//pb6
			c=1;								//pc4
			d=1;								//pc5
			e=1;								//pa1
			f=1;								//pa3
			g=1;				 				//pa6
			
			wei++;
		  switch (wei)						//wei Ϊuchar����
         {
          case 1: //a
              {
								if(Dig1a)bitcode1=0; 
								if(Dig2a)bitcode2=0; 
								if(Dig3a)bitcode3=0; 
								if(Dig4a)bitcode4=0; 
								a=0;
              }break;
          case 2: //b
              {
								if(Dig1b)bitcode1=0; 
								if(Dig2b)bitcode2=0; 
								if(Dig3b)bitcode3=0; 
								if(Dig4b)bitcode4=0; 
								b=0;		
              }break;
	        case 3: //c
              {
								if(Dig1c)bitcode1=0; 
								if(Dig2c)bitcode2=0; 
								if(Dig3c)bitcode3=0; 
								if(Dig4c)bitcode4=0; 
								c=0;		
              } break ;
	        case 4: //d
              {
								if(Dig1d)bitcode1=0; 
								if(Dig2d)bitcode2=0; 
								if(Dig3d)bitcode3=0; 
								if(Dig4d)bitcode4=0; 
								d=0;		
              }break ;
          case 5: //e
              {
								if(Dig1e)bitcode1=0; 
								if(Dig2e)bitcode2=0; 
								if(Dig3e)bitcode3=0; 
								if(Dig4e)bitcode4=0; 
								e=0;	
              }break ;
          case 6: //f
              {
								if(Dig1f)bitcode1=0; 
								if(Dig2f)bitcode2=0; 
								if(Dig3f)bitcode3=0; 
								if(Dig4f)bitcode4=0; 
								f=0;		
              }break ;
          case 7: //g
              {
								if(Dig1g)bitcode1=0; 
								if(Dig2g)bitcode2=0; 
								if(Dig3g)bitcode3=0; 
								if(Dig4g)bitcode4=0; 
								wei=0;
								g=0;	
              }break ;
	       }
		 }			
	}

//===========================������=========================================//		
	void main()
	{
	   GCC_DELAY(100);  //��ʱ��ϵͳ�ȶ�
	   
	   Init_clock();   //��ʼ��ʱ��
//======================�˿ڳ�ʼ��==============================//	   
	   GPIOA_INIT(GPIO_Pin_All,GPIO_Mode_OUT,DISABLE,RESET);
	   GPIOB_INIT(GPIO_Pin_All,GPIO_Mode_OUT,RESET);
	   GPIOC_INIT(GPIO_Pin_All,GPIO_Mode_OUT,SET);	   
	   GPIOD_INIT(GPIO_Pin_All,GPIO_Mode_OUT,SET);

	   GPIOB_INIT(GPIO_Pin_3|GPIO_Pin_6,GPIO_Mode_INT,SET);
	   GPIOA_INIT(GPIO_Pin_1,GPIO_Mode_OUT,DISABLE,SET);
	   
	   num1=0;
	   num2=1;
	   num3=2;
	   num4=3; 
	   Digbuff1 =num[num1];   //�����1��ʾ
		 Digbuff2 =num[num2];   //�����2��ʾ
	 	 Digbuff3 =num[num3];   //�����3��ʾ
		 Digbuff4 =num[num4];   //�����4��ʾ
//======================END====================================//
	   while(1)
		 {
		 	GCC_CLRWDT();          //ι��		 	
//=====================����ܸ�����ʾ=========================//		  	

//========================END==================================//
		 }
	}