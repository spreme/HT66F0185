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
	  	_tbc=0b10000111;       //时基定时器配置使能 fTBC时钟源 LXT快速启振
	  	_tb0f=0;               //时基0中断请求标志清零
	  	_tb0e=1;               //时基0中断控制位使能
	  	
	  	_emi=1;		  			//开总中断
	  	
	  	GCC_CLRWDT();	       //清除看门狗
		clr_ram_en(0);         //数据存储区选择BANK0
		clr_ram_en(1);         //数据存储区选择BANK1

	}

//===========================时基定时器中断入口=========================================//
	DEFINE_ISR(isr_TBS0, 0x1C)       //时基定时器中断函数  1s中断一次
	{	
		_tb0f=0;
		t10s++;                   //32.768 KHz 的频率下为1S一次中断
		if (pekjsflag)
		{	
			peking_second++;           // 计时秒钟
		}
		if (warmjsflag)
		{	
		 	alarm_second--;           //报警秒钟
		}
		
		if(min5flag)
		{	
			bj_second++;
		}
		else
		{
			bj_second=0;
			bj_min=0;	
		}
		
		if((keydownflag)||(keyupflag))
		{
			if(!keyconflag)   //非连续按键标志下
			{
				t2s++;       //秒时间计数
				if(t2s>=2)   //如果时间等于2s
				{	
					t2s=0;
					keyconflag=1;	//置连续按键标志
				}
			}
		}
		else
		{
			t2s=0;
		}
			
	}

//===========================定时器0中断入口=========================================//
	DEFINE_ISR(isr_TM0, 0x0c)   //定时器0中断函数  191us
	{
	    _t0af=0;       //t0中断请求标志清零
	    _emi=1;        //开总中断
	    step++;
	    step2++;
	    step3++;
	    sum++;
	    sum1++;
	    if(countmsflag)
	    {
	    	tms++;
	    	if(tms>=5236)
	    	{
	    		tms=0;
	    		peking_second1++;   //1s
	    	}
	    }
	    if(buzopen)  //开启蜂鸣器标志
		{
			buz=~buz;
		}

		if (step>= 52)
		{
			step=0;
			t10msflag=1;
		}
		
		
		if (step2>= 105)     //105*192us=20055us=20.055ms
		{
			step2=0;
			t20msflag=1;  //置位标志
		}
		
		if(keyconflag)    //连续按键标志下
		{
			if (sum>=523)
			{	
				sum=0;
				t100msflag=1;
			}
		}
		else
		{
			t100msflag=0;	
		}
		
		if (sum1>=2618)
		{	
			t500msflag=1;
		}
		if (sum1>=5236)
		{	
			sum1=0;
			t500msflag=0;
		}
		
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
		                      }break ;
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
//===========================蜂鸣器工作=========================================//
	void buz_beep (void)
	{	
		if(t10msflag)   //10ms到了
		{
		  t10msflag=0;
		  if (buzopen)  //开启蜂鸣器标志状态下
		     {
			      bBbSound--;													
			      if(bBbSound<=1)
			      {
			      	buzopen=0;
			      	if(bbRam==1)
			      	{
			      		bBbSound=bbTime;	
			      	}
			      	else
			      	{
			      		bBbSound=bbCnt;
			      	}
			      }	
		     }	
			
		  if ((!buzopen)&&(bbRam==2))						
		     {
		     	 bBbSound--;	
		    	 if(bBbSound<=1)
		    	 {
		    	 	buzopen=1;
		    	 	bbRam--;
		    	 	bBbSound=bbTime;
		    	 }			
		     }
		     if ((!buzopen)&&(bbRam==1))						
		     {
		     	 bBbSound--;	
		    	 if(bBbSound<=1)
		    	 {
		    	 	buzopen=1;
		    	 	bbRam--;
		    	 	bBbSound=bbTime;
		    	 }			
		     }
		      
		 }     	
	}
//===========================按键扫描=========================================//
	void key_scal(void)
	{
		if (!t20msflag)        //20ms标志未到 
		 return ;              //退出函数
		else
		  {
		  	t20msflag=0;     //否则清除标志
		  	if((keyup)&&(keyset)&&(keydown))		//无按键按下高电平
		  	 {
		  	 	keystep=0;	        //按键步数20ms一步
		  	 	keyconflag=0;       //连续按键标志
		  	 	keynullflag=1;      //无按键按下标志位
		  	 	keysetflag=0;		    //按键设定标志	  	 	  
			  	keydownflag=0;      //向下按键标志
			  	keyupflag=0;        //向上按键标志
			   	keysstflag=0;       //设定按键下标志
		  	 }
		  	else	         //否则有按键按下									
		  	 {
		  	 	keystep++;
		  	 	if (keystep>5)    //20ms*5=100ms到了
		  	 	{
			  	 	if((keyup)&&(keyset)&&(!keydown))
			  	 	{
			  	 		keydownflag=1;		//down按下
			  	 	}
			  	 	if((!keyup)&&(keyset)&&(keydown))
			  	 	{
			  	 		keyupflag=1;		//up按下
			  	 	}
			  	 	if((keyup)&&(!keyset)&&(keydown))
			  	 	{
			  	 		keysetflag=1;	    //set按下
			  	 	}
		  	 	}
		  	 }

		  }	

		 if ((keysetflag)&&(keynullflag))        //设置按键按下
		  {	
		  	keynullflag=0;                   //有按键按下
		 	   keysstflag=1;                    //设定标志下
		  }	
	}
//===========================时间设置=========================================//
	void time_set(void)
	{
		if ((keydownflag)&&(keynullflag))                          //向下按键操作
		{	
			keydownflag=0;
			keynullflag=0;
			if (data==2)            //控制时钟分钟
			{
				peking_min--;
				peking_second=0;
			}
			if (data==1)           //控制时钟小时
			{
				peking_hour--;   
				peking_second=0;
			}
			
			if (data==4)          //控制报警分钟
			{
				alarm_min--;
				alarm_second=59;
			}
			if (data==3)         //控制报警小时
			{
				alarm_hour--;
				alarm_second=59;
			}
		}
		if ((keyupflag)&&(keynullflag))        //向上按键操作
		{	
			keyupflag=0;
			keynullflag=0;
			if (data==2)
			{
				peking_min++;
				peking_second=0;
			}
			if (data==1)
			{
				peking_hour++;
				peking_second=0;
			}
			
			if (data==4)
			{
				alarm_min++;
				alarm_second=59;
			}
			if (data==3)
			{
				alarm_hour++;
				alarm_second=59;
			}
		}
				  
		if ((keyconflag) && (t100msflag))        //连续设置按键操作  100ms加减一次
	    {
	       	  t100msflag=0;
	   	      if (data==2)        //北京分钟调整
	   	         {
	   	      		if (keydownflag)
	   	      		{
	   	      			peking_min--;
	   	      			peking_second=0;
	   	      		}  //长按+，-，快速设置时间
	   	      		if (keyupflag)
	   	      		{
	   	      			peking_min++;
	   	      			peking_second=0;
	   	      		}
	   	         }
	   	      if (data==4)      //报警闹钟分钟调整
	   	         { 
	   	         	if (keydownflag)
	   	         	{
	   	         		alarm_min--;
	   	         		alarm_second=59;
	   	         	}
	   	         	if (keyupflag)
	   	         	{
	   	         		alarm_min++;
	   	         		alarm_second=59;
	   	         	}
	   	         }
	   	       if (data==1)      //北京小时调整
	   	         {
	   	      		if (keydownflag)
	   	      		{
	   	      			peking_hour--;
	   	      			peking_second=0;
	   	      		}
	   	      		if (keyupflag)
	   	      		{
	   	      			peking_hour++;
	   	      			peking_second=0;
	   	      		}
	   	         }
	   	      if (data==3)         //报警小时调整
	   	         { 
	   	         	if (keydownflag)
	   	         	{
	   	         		alarm_hour--;
	   	         		alarm_second=59;
	   	         	}
	   	         	if (keyupflag)
	   	         	{
	   	         		alarm_hour++;
	   	         		alarm_second=59;
	   	         	}
	   	         }
		   	
	    }
    		if (alarm_second<0)
		      {
		     	alarm_second=59;
		     	if(data!=3)
		     	alarm_min--;
		      }	
	     	if (alarm_min<0)
	     	  {
	     	  	alarm_min=59;
	     	  	if(data!=4)
	     	  	alarm_hour--;
	     	  }	
     	  	 if (alarm_hour<0)
     	  	 alarm_hour=23;
		     	  
		      
		 	 if (alarm_second>59)
		      {
		     	alarm_second=0;

		      }
	     	 if (alarm_min>59)
	     	  {
	     	  	alarm_min=0;

	     	  }
     	  	 if (alarm_hour>23)
     	  	 {
     	  	 	alarm_hour=0;
     	  	 }
	
		     if (peking_second>59)
			   {
			   	  peking_second=0;
			   	  peking_min++;
			   }
			  if (peking_min>59)
			   {
			   	peking_min=0;
			   	if(data!=2)
			   	  {	
			   	  	peking_hour++;
			   	  }
			   }
			  if (peking_hour>=24)
			  {
			  	peking_hour=0;
			  }
		
		   	  if (peking_second<0)
			   {
			   	  	peking_second=59;
			   }
			  if (peking_min<0)
			   {
			   		peking_min=59;
			   }
			   if (peking_hour<0)
			   {
			   		peking_hour=23;
			   }
			   
			   if(bj_second>59)
			   {	
			   		bj_second=0;
			   		bj_min++;
			   		if(bj_min>=1)
			   		{	
			   			bj_second=0;
			   			bj_min=0;
			   			min5flag=0;	
			   			data=0;
			   		}
			   }
	  	
	}	
//===========================过程处理=========================================//	
	void process_set(void)
	{
		if (keysstflag)     //设定键按下标志
		 {
			keysstflag=0;
			data++;        //闪烁选择自加1
			if((data==5)&&(!alarm_hour)&&(!alarm_min))   //如果等于5并且闹铃小时和闹铃分钟都为0状态下
			{
				data=0;	     //等于0
			}
		 }
	 	if ((!alarm_hour)&&(!alarm_min))       //闹铃报警小时和分钟都为0的情况下             
		  {
		  		if (data>=5) 
				{	
		          	min5flag=1;   
		          	warmjsflag=0;
		          	alarm_second=0;   //闹铃秒清零
		          	if(min5flag==1)
		          	{	
		          		if((!bbRam)&&(!buzopen))  //bbRam等于0并且蜂鸣器非开启状态下
		          		{
					 	      	BBB(2,20,1);    //进入蜂鸣器BBB工作状态下
		          		}
		          	}
				 	if((keyupflag)||(keydownflag)||(data==6))   //如果向上或者向下按键或者data等于6
				  	 {	
					  	min5flag=0;    //清除蜂鸣器报警
					 		data=0; 
					 		buzopen=0;
							bbRam=0;
				  	 }  
      		if (t500msflag)         //500ms到了  刷新一次数码管值
      	 	 {
							num1=alarm_hour/10;
							num2=alarm_hour%10;
							num3=alarm_min/10;
							num4=alarm_min%10;
    	  	 }	
    		 else                //数码管熄灭
      	 {
						num1=16;   
						num2=16;
						num3=16;
						num4=16;				
      	 }	
				}
		  }	
		else           //否则闹铃报警时间不为0模式下  为0说明没有设定倒计时报警
		  {
		  		if(data>5)
		  		{
		  			data=1;
		  		}
				if (data==5)          //启动倒计时报警功能
				{
				 warmjsflag=1;
				 pekjsflag=1;
				 num1=alarm_hour/10;
      	      	 num2=alarm_hour%10;
      	      	 num3=alarm_min/10;
      	      	 num4=alarm_min%10;								
				}
				else     //data不等于5
				{  
					pekjsflag=0;
					warmjsflag=0;
					alarm_second=59;
					peking_second=0;
				}
		  }	
		  if(keynullflag)		//无健按下10退出
		   {
		     if(t10s>10)		//大于60s时间									
		      {	
		      	t10s=0;
		      	if ((data!=0)&&(data!=5))    //
		      	  {
		      	  	if((!alarm_hour)&&(!alarm_min))
		      	  		{
		      	  			data=0;
		      	  		}
		      	  		else
		      	  		{
		      	  			data=5;	
		      	  		}
		      	  }
		      }
		   }
		   else
		   {
		   	t10s=0;
		   }
	    switch(data)
	          {
	        
	          	case 0 :                          //data为0 北京时间走时显示     
	          	      {
	          	      	pekjsflag=1;
	          	      	num1=peking_hour/10;
	          	      	num2=peking_hour%10;
	          	      	num3=peking_min/10;
	          	      	num4=peking_min%10;         	      	
	          	      }break;
	          	
	           case 1 :                                           //data为1 设置北京“时”
	          	      {	
	          	      	pekjsflag=0;
	          	      	peking_second=0;
	          	      	if ((t500msflag)&&(!keyconflag))
	          	      	  {
		          	      	num1=16;
		          	      	num2=16;
	          	      	  }
	          	      
	          	      	else
	          	      	  {
		          	      	num1=peking_hour/10;
		          	      	num2=peking_hour%10;
	          	      	  }

	          	      	num3=peking_min/10;
	          	      	num4=peking_min%10;
	          	      }break;		          	
	          	case 2 :												//data为2 设置北京“分”
	          	      {
	          	      	num1=peking_hour/10;
	          	      	num2=peking_hour%10;
	          	      	if ((t500msflag)&&(!keyconflag))
	          	      	  {
		          	      	num3=16;
		          	      	num4=16;	          	      	
	          	      	  }
	          	      	 else
	          	      	  {
	          	      	  	num3=peking_min/10;
		          	      	num4=peking_min%10;
	          	      	  	
	          	      	  }
	          	      }break;
	          	case 3 :							                	//data为3 设置闹铃“时”			
	          	      {	
	          	      	
	          	      	if ((t500msflag)&&(!keyconflag))
	          	      	  {
		          	      	num1=16;
		          	      	num2=16;
	          	      	  }
	          	      	else 
	          	      	  {
		          	      	num1=alarm_hour/10;
		          	      	num2=alarm_hour%10;
	          	      	  }
	          	      	 num3=alarm_min/10;
	          	      	 num4=alarm_min%10;	
	          	      }break;	          	
	          	case 4 :                                             //data为4 设置闹铃“分”
	          	      {	
	          	      	num1=alarm_hour/10;
	          	      	num2=alarm_hour%10;
	          	      	if ((t500msflag)&&(!keyconflag))
	          	      	  {
		          	      	num3=16;
		          	      	num4=16;        	      	
	          	      	  }
	          	      	 else
	          	      	  {
	          	      	  	num3=alarm_min/10;
		          	      	num4=alarm_min%10;
	          	      	  	
	          	      	  }  
	          	      }break;

	          	default : break;
	          }
		
	     
    }
//===========================测试模式=========================================//			
	void test_mode(void)
	{
		 	tms=0;
		 	peking_second1=0;
		 	  while(1)
		  		{
		  			GCC_CLRWDT();
		  			key_scal();
		  			buz_beep();
					if (peking_second1>59)    
					{
						peking_second1=0;
						peking_min1++;
					
						if (peking_min1>59)
						{
							peking_min1=0;
						}
					}
		  			if (keysstflag)      
		  			 {
		  			 	keysstflag=0;
		  			 	data++;                 
		  			 	if (data>4)
		  			 	{
		  			 		data=1;        //按set3次一循环
		  			 	}
		  			 	if (data==3)
		  			 	{	
		  			 		value=peking_second1;
		  			 	}
		  			 	
		  			 }
		  			switch(data)
		  			      {
		  			      	case 1 :
		  			      	       {
		  			      	       	countmsflag=1;
		  			      	       	num1=peking_second1/10;
		  			      	       	num2=peking_second1%10;
		  			      	       	num3=tms/524;
		  			      	       	num4=(tms-(tms/524)*524)/52;
		  			      	       }break;
		  			      	       
		  			        case 2 :
		  			        	   {
									  	num1=peking_second1%10;
									  	num2=num1;
									  	num3=num1;
									  	num4=num1;
		  			        	   }break;
		  			      	case 3 :
		  			      	       {	
		  			      	       		num1=value%10;
									  	num2=num1;
									  	num3=num1;
									  	num4=num1;
										if (keyupflag)                 //keyupflag
										{	
											if((!bbRam)&&(!buzopen))
											{
												BBB(2,20,1);
											}
										}
									    else
									    {
									    	buzopen=0;
	  										bbRam=0;	
									    }
									    
									    if(keydownflag)
									    {

									    }
									    else
									    {

									    }
		  			      	       	  
		  			      	       }break;
		  			      	case 4 :								//进入时间测试模式
		  			      	       {
		  			      	       	
		  			      	       	num3=peking_second1/10;
		  			      	       	num4=peking_second1%10;
		  			      	       	num1=peking_min1/10;
		  			      	       	num2=peking_min1%10;
		  			      	       }break;		      	
		  			      }
							Digbuff1 =num[num1];
							Digbuff2 =num[num2];
							Digbuff3 =num[num3];
							Digbuff4 =num[num4];
		  			  
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
	   GPIOD_INIT(GPIO_Pin_All,GPIO_Mode_OUT,RESET);
	   
	   GPIOA_INIT(GPIO_Pin_1,GPIO_Mode_OUT,DISABLE,SET);
	   	   
	   GPIOB_INIT(GPIO_Pin_4,GPIO_Mode_INT,RESET);
	   GPIOB_INIT(GPIO_Pin_3,GPIO_Mode_INT,RESET);
	   GPIOB_INIT(GPIO_Pin_2,GPIO_Mode_INT,RESET);
//======================END====================================//
     buz=0;        //关蜂鸣器
     buzopen=0;    //清蜂鸣器开启标志
	   bbRam=0;	    
	   data=1;    //默认控制小时 闪烁位置选择  
	   
	   while(1)
		 {
		 	GCC_CLRWDT();   //喂狗
      test_mode();  //测试模式 上电前同时按下三个按键
//========================END==================================//
		 }
	}