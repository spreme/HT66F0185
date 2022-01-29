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
	  	_smod=0x01;            //选择gao速时钟为系统时钟 内部8Mhz
	  	while(!_hto);          //等待高速震荡器就位
	  	_wdtc=0x57;            //使能看门狗
	  	_acerl=0x00;		   //取消A/D输入
	  	_tmpc=0x00;            //取消相关引脚用作TM 输入/ 输出，相关引脚保持原来功能
	  	_cpc=0x08;             //比较器输出仅内部使用
	  	_integ=0x00;			//所有外部中断边沿控制除能
	  	_int0e=0;				//INTO中断除能
	  	_emi = 0;   			//关闭总中断

//=========LCD控制寄存器引脚设定为其他功能=====================//		
		_slcdc0 = 0;	
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
	  	//_tbc=0b10000111;       //时基定时器配置使能 fTBC时钟源 LXT快速启振
	  	//_tb0f=0;               //时基0中断请求标志清零
	  	//_tb0e=1;               //时基0中断控制位使能
	  	
	  	_emi=1;		  			//开总中断
	  	
	  	GCC_CLRWDT();	       //清除看门狗
		clr_ram_en(0);         //数据存储区选择BANK0
		clr_ram_en(1);         //数据存储区选择BANK1

	}


//===========================定时器0中断入口=========================================//
	DEFINE_ISR(isr_TM0, 0x0c)   //定时器0中断函数  191us
	{
    _t0af=0;       //t0中断请求标志清零
    _emi=1;        //开总中断
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
		  switch (wei)						//wei 为uchar变量
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

//===========================主函数=========================================//		
	void main()
	{
	   GCC_DELAY(100);  //延时待系统稳定
	   
	   Init_clock();   //初始化时钟
//======================端口初始化==============================//	   
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
	   Digbuff1 =num[num1];   //数码管1显示
		 Digbuff2 =num[num2];   //数码管2显示
	 	 Digbuff3 =num[num3];   //数码管3显示
		 Digbuff4 =num[num4];   //数码管4显示
//======================END====================================//
	   while(1)
		 {
		 	GCC_CLRWDT();          //喂狗		 	
//=====================数码管更新显示=========================//		  	

//========================END==================================//
		 }
	}