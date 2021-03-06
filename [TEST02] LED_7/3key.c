#include "init.h"
#include "HT66F0185.h"
	
//===========================PA端口初始化函数=========================================//
	void GPIOA_INIT(u8 GPIO_Pin,u8 GPIO_Mode,u8 wakeup,u8 GPIO_BitVal)  //u8 为无符号字符型
	{
		if ((u8)GPIO_Mode == (u8)0x01)   //pa为输入型时
		 {
		 	_pac|=GPIO_Pin;             //当pa引脚GPIO_Pin为输入，则置位pac ，同时设置上拉电阻
		 	_papu|=GPIO_Pin;
		 }
		else
		 {
			_pac&=(u8)(~GPIO_Pin);      //将pa设置为输出型 
			_papu&=(u8)(~GPIO_Pin);	
		 }
		 
		if (GPIO_BitVal != RESET)       //重置
		 {
		  	 _pa|=GPIO_Pin;
		 }
		else
		 {
		 	 _pa&=(u8)(~GPIO_Pin);   

		 }	 	
	}
//===========================PB端口初始化函数=========================================//
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
//===========================PC端口初始化函数=========================================//
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

//===========================PD端口初始化函数=========================================//
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
	
//===========================数据存储区使能配置=========================================//
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
//===========================时钟初始化函数=========================================//
	void Init_clock(void)
	{
  	_smod=0x01;       //选择gao速时钟为系统时钟 内部8Mhz
  	while(!_hto);     //等待高速震荡器就位
  	_wdtc=0x57;       //使能看门狗
  	_acerl=0x00;		  //取消A/D输入
  	_tmpc=0x00;       //取消相关引脚用作TM 输入/ 输出，相关引脚保持原来功能
  	_cpc=0x08;        //比较器输出仅内部使用
  	_integ=0x00;			//所有外部中断边沿控制除能
  	_int0e=0;				  //INTO中断除能
  	_emi = 0;   			//关闭总中断

//=========LCD控制寄存器引脚设定为其他功能=====================//		
		_slcdc0 = 0;	//设定为其他引脚功能
		_slcdc1 = 0;
		_slcdc2 = 0;
		_slcdc3 = 0;
		_slcdc4 = 0;
/***********TM0************/
  	_tm0c0=0x10;			//选择系统时钟fsys作为t1时钟fint=8MHZ	
  	_tm0c1=0xc1;			//定时模式，a匹配
  	_tm0al=0xf8;			//定时初值  0x5f8=1528
  	_tm0ah=0x05;            //1528/8MHZ=191us
  	_t0af=0;				//清t中断标志位
  	_t0on=1;				//启动定时
  	_mf0e=1;				//开多功能中断
  	_t0ae=1;	    		//开t0中断
/***********时基0************/	  
  	_tbc=0b10000111;       //时基定时器配置使能 fTBC时钟源 LXT快速启振
  	_tb0f=0;               //时基0中断请求标志清零
  	_tb0e=1;               //时基0中断控制位使能  	
  	_emi=1;		  			//开总中断
	  	
	  GCC_CLRWDT();	         //清除看门狗
		clr_ram_en(0);         //数据存储区选择BANK0
		clr_ram_en(1);         //数据存储区选择BANK1

	}

//===========================时基定时器中断入口=========================================//
	DEFINE_ISR(isr_TBS0, 0x1C)       //时基定时器中断函数  
	{	
		_tb0f=0;
		
			
	}

//===========================定时器0中断入口=========================================//
	DEFINE_ISR(isr_TM0, 0x0c)   //定时器0中断函数  191us
	{
    _t0af=0;       //t0中断请求标志清零
    _emi=1;        //开总中断
    tms++;
    if(tms>=5236)
    {
    	tms=0;
    	tms1++;
    	if(tms1==1)
    	{
    	 LED1=0;	
    	}
    	else
    	{
    	 LED1=1;
    	}
    	if(tms1==2)
    	{
    	 LED2=0;	
    	}
    	else
    	{
    	 LED2=1;
    	}
    	if(tms1==3)
    	{
    	 LED3=0;	
    	}
    	else
    	{
    	 LED3=1;
    	}
    	if(tms1==4)
    	{
    	 LED4=0;	
    	}
    	else
    	{
    	 LED4=1;
    	}
    	if(tms1==5)
    	{
    	 LED5=0;	
    	}
    	else
    	{
    	 LED5=1;
    	}
    	if(tms1==6)
    	{
    	 LED6=0;	
    	}
    	else
    	{
    	 LED6=1;
    	}
     	if(tms1==7)
    	{
    	 LED7=0;	
    	}
    	else
    	{
    	 LED7=1;
    	} 
    	if(tms1==8)
    	{
    	 tms1=0;
    	 LED8=0;	
    	}
    	else
    	{
    	 LED8=1;
    	}    
    }
	  
	}
//===========================蜂鸣器工作=========================================//
	void buz_beep (void)
	{	
    	
	}
//===========================主函数=========================================//		
	void main()
	{
	   GCC_DELAY(100);  //延时待系统稳定   
	   Init_clock();    //初始化时钟
//======================端口初始化==============================//	   
	   GPIOA_INIT(GPIO_Pin_All,GPIO_Mode_OUT,DISABLE,RESET);
	   GPIOB_INIT(GPIO_Pin_All,GPIO_Mode_OUT,RESET);
	   GPIOC_INIT(GPIO_Pin_All,GPIO_Mode_OUT,SET);	   
	   GPIOD_INIT(GPIO_Pin_All,GPIO_Mode_OUT,SET); 
	   
	   GPIOB_INIT(GPIO_Pin_3|GPIO_Pin_6,GPIO_Mode_OUT,SET);
     GPIOA_INIT(GPIO_Pin_1,GPIO_Mode_OUT,DISABLE,SET);
//======================数码管初始化==============================//
     
//======================END====================================//
	   while(1)
		 {
	  	GCC_CLRWDT();   //喂狗  	
//========================END==================================//
		 }
	}