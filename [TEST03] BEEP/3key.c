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
  	_smod=0x01;       //ѡ��gao��ʱ��Ϊϵͳʱ�� �ڲ�8Mhz
  	while(!_hto);     //�ȴ�����������λ
  	_wdtc=0x57;       //ʹ�ܿ��Ź�
  	_acerl=0x00;		  //ȡ��A/D����
  	_tmpc=0x00;       //ȡ�������������TM ����/ �����������ű���ԭ������
  	_cpc=0x08;        //�Ƚ���������ڲ�ʹ��
  	_integ=0x00;			//�����ⲿ�жϱ��ؿ��Ƴ���
  	_int0e=0;				  //INTO�жϳ���
  	_emi = 0;   			//�ر����ж�

//=========LCD���ƼĴ��������趨Ϊ��������=====================//		
		_slcdc0 = 0;	//�趨Ϊ�������Ź���
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
  	_tbc=0b10000111;       //ʱ����ʱ������ʹ�� fTBCʱ��Դ LXT��������
  	_tb0f=0;               //ʱ��0�ж������־����
  	_tb0e=1;               //ʱ��0�жϿ���λʹ��  	
  	_emi=1;		  			//�����ж�
	  	
	  GCC_CLRWDT();	         //������Ź�
		clr_ram_en(0);         //���ݴ洢��ѡ��BANK0
		clr_ram_en(1);         //���ݴ洢��ѡ��BANK1

	}

//===========================ʱ����ʱ���ж����=========================================//
	DEFINE_ISR(isr_TBS0, 0x1C)       //ʱ����ʱ���жϺ���  
	{	
		_tb0f=0;
		
			
	}

//===========================��ʱ��0�ж����=========================================//
	DEFINE_ISR(isr_TM0, 0x0c)   //��ʱ��0�жϺ���  191us
	{
    _t0af=0;       //t0�ж������־����
    _emi=1;        //�����ж�
    tms++;
    if(tms>=5236)
    {
    	tms=0;
    	buz=~buz;
    }
	  
	}
//===========================����������=========================================//

//===========================������=========================================//		
	void main()
	{
	   GCC_DELAY(100);  //��ʱ��ϵͳ�ȶ�   
	   Init_clock();    //��ʼ��ʱ��
//======================�˿ڳ�ʼ��==============================//	   
	   GPIOA_INIT(GPIO_Pin_All,GPIO_Mode_OUT,DISABLE,RESET);
	   GPIOB_INIT(GPIO_Pin_All,GPIO_Mode_OUT,RESET);
	   GPIOC_INIT(GPIO_Pin_All,GPIO_Mode_OUT,SET);	   
	   GPIOD_INIT(GPIO_Pin_All,GPIO_Mode_OUT,SET); 
	   
	   GPIOB_INIT(GPIO_Pin_3|GPIO_Pin_6,GPIO_Mode_OUT,SET);
     GPIOA_INIT(GPIO_Pin_1,GPIO_Mode_OUT,DISABLE,SET);
//======================����ܳ�ʼ��==============================//
//======================END====================================//
	   while(1)
		 {
	  	GCC_CLRWDT();   //ι��  	
//========================END==================================//
		 }
	}