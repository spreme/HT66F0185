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
	  	_tbc=0b10000111;       //ʱ����ʱ������ʹ�� fTBCʱ��Դ LXT��������
	  	_tb0f=0;               //ʱ��0�ж������־����
	  	_tb0e=1;               //ʱ��0�жϿ���λʹ��
	  	
	  	_emi=1;		  			//�����ж�
	  	
	  	GCC_CLRWDT();	       //������Ź�
		clr_ram_en(0);         //���ݴ洢��ѡ��BANK0
		clr_ram_en(1);         //���ݴ洢��ѡ��BANK1

	}

//===========================ʱ����ʱ���ж����=========================================//
	DEFINE_ISR(isr_TBS0, 0x1C)       //ʱ����ʱ���жϺ���  1s�ж�һ��
	{	
		_tb0f=0;
		t10s++;                   //32.768 KHz ��Ƶ����Ϊ1Sһ���ж�
		if (pekjsflag)
		{	
			peking_second++;           // ��ʱ����
		}
		if (warmjsflag)
		{	
		 	alarm_second--;           //��������
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
			if(!keyconflag)   //������������־��
			{
				t2s++;       //��ʱ�����
				if(t2s>=2)   //���ʱ�����2s
				{	
					t2s=0;
					keyconflag=1;	//������������־
				}
			}
		}
		else
		{
			t2s=0;
		}
			
	}

//===========================��ʱ��0�ж����=========================================//
	DEFINE_ISR(isr_TM0, 0x0c)   //��ʱ��0�жϺ���  191us
	{
	    _t0af=0;       //t0�ж������־����
	    _emi=1;        //�����ж�
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
	    if(buzopen)  //������������־
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
			t20msflag=1;  //��λ��־
		}
		
		if(keyconflag)    //����������־��
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
		    switch (wei)						//wei Ϊuchar����
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
//===========================����������=========================================//
	void buz_beep (void)
	{	
		if(t10msflag)   //10ms����
		{
		  t10msflag=0;
		  if (buzopen)  //������������־״̬��
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
//===========================����ɨ��=========================================//
	void key_scal(void)
	{
		if (!t20msflag)        //20ms��־δ�� 
		 return ;              //�˳�����
		else
		  {
		  	t20msflag=0;     //���������־
		  	if((keyup)&&(keyset)&&(keydown))		//�ް������¸ߵ�ƽ
		  	 {
		  	 	keystep=0;	        //��������20msһ��
		  	 	keyconflag=0;       //����������־
		  	 	keynullflag=1;      //�ް������±�־λ
		  	 	keysetflag=0;		    //�����趨��־	  	 	  
			  	keydownflag=0;      //���°�����־
			  	keyupflag=0;        //���ϰ�����־
			   	keysstflag=0;       //�趨�����±�־
		  	 }
		  	else	         //�����а�������									
		  	 {
		  	 	keystep++;
		  	 	if (keystep>5)    //20ms*5=100ms����
		  	 	{
			  	 	if((keyup)&&(keyset)&&(!keydown))
			  	 	{
			  	 		keydownflag=1;		//down����
			  	 	}
			  	 	if((!keyup)&&(keyset)&&(keydown))
			  	 	{
			  	 		keyupflag=1;		//up����
			  	 	}
			  	 	if((keyup)&&(!keyset)&&(keydown))
			  	 	{
			  	 		keysetflag=1;	    //set����
			  	 	}
		  	 	}
		  	 }

		  }	

		 if ((keysetflag)&&(keynullflag))        //���ð�������
		  {	
		  	keynullflag=0;                   //�а�������
		 	   keysstflag=1;                    //�趨��־��
		  }	
	}
//===========================ʱ������=========================================//
	void time_set(void)
	{
		if ((keydownflag)&&(keynullflag))                          //���°�������
		{	
			keydownflag=0;
			keynullflag=0;
			if (data==2)            //����ʱ�ӷ���
			{
				peking_min--;
				peking_second=0;
			}
			if (data==1)           //����ʱ��Сʱ
			{
				peking_hour--;   
				peking_second=0;
			}
			
			if (data==4)          //���Ʊ�������
			{
				alarm_min--;
				alarm_second=59;
			}
			if (data==3)         //���Ʊ���Сʱ
			{
				alarm_hour--;
				alarm_second=59;
			}
		}
		if ((keyupflag)&&(keynullflag))        //���ϰ�������
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
				  
		if ((keyconflag) && (t100msflag))        //�������ð�������  100ms�Ӽ�һ��
	    {
	       	  t100msflag=0;
	   	      if (data==2)        //�������ӵ���
	   	         {
	   	      		if (keydownflag)
	   	      		{
	   	      			peking_min--;
	   	      			peking_second=0;
	   	      		}  //����+��-����������ʱ��
	   	      		if (keyupflag)
	   	      		{
	   	      			peking_min++;
	   	      			peking_second=0;
	   	      		}
	   	         }
	   	      if (data==4)      //�������ӷ��ӵ���
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
	   	       if (data==1)      //����Сʱ����
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
	   	      if (data==3)         //����Сʱ����
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
//===========================���̴���=========================================//	
	void process_set(void)
	{
		if (keysstflag)     //�趨�����±�־
		 {
			keysstflag=0;
			data++;        //��˸ѡ���Լ�1
			if((data==5)&&(!alarm_hour)&&(!alarm_min))   //�������5��������Сʱ��������Ӷ�Ϊ0״̬��
			{
				data=0;	     //����0
			}
		 }
	 	if ((!alarm_hour)&&(!alarm_min))       //���屨��Сʱ�ͷ��Ӷ�Ϊ0�������             
		  {
		  		if (data>=5) 
				{	
		          	min5flag=1;   
		          	warmjsflag=0;
		          	alarm_second=0;   //����������
		          	if(min5flag==1)
		          	{	
		          		if((!bbRam)&&(!buzopen))  //bbRam����0���ҷ������ǿ���״̬��
		          		{
					 	      	BBB(2,20,1);    //���������BBB����״̬��
		          		}
		          	}
				 	if((keyupflag)||(keydownflag)||(data==6))   //������ϻ������°�������data����6
				  	 {	
					  	min5flag=0;    //�������������
					 		data=0; 
					 		buzopen=0;
							bbRam=0;
				  	 }  
      		if (t500msflag)         //500ms����  ˢ��һ�������ֵ
      	 	 {
							num1=alarm_hour/10;
							num2=alarm_hour%10;
							num3=alarm_min/10;
							num4=alarm_min%10;
    	  	 }	
    		 else                //�����Ϩ��
      	 {
						num1=16;   
						num2=16;
						num3=16;
						num4=16;				
      	 }	
				}
		  }	
		else           //�������屨��ʱ�䲻Ϊ0ģʽ��  Ϊ0˵��û���趨����ʱ����
		  {
		  		if(data>5)
		  		{
		  			data=1;
		  		}
				if (data==5)          //��������ʱ��������
				{
				 warmjsflag=1;
				 pekjsflag=1;
				 num1=alarm_hour/10;
      	      	 num2=alarm_hour%10;
      	      	 num3=alarm_min/10;
      	      	 num4=alarm_min%10;								
				}
				else     //data������5
				{  
					pekjsflag=0;
					warmjsflag=0;
					alarm_second=59;
					peking_second=0;
				}
		  }	
		  if(keynullflag)		//�޽�����10�˳�
		   {
		     if(t10s>10)		//����60sʱ��									
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
	        
	          	case 0 :                          //dataΪ0 ����ʱ����ʱ��ʾ     
	          	      {
	          	      	pekjsflag=1;
	          	      	num1=peking_hour/10;
	          	      	num2=peking_hour%10;
	          	      	num3=peking_min/10;
	          	      	num4=peking_min%10;         	      	
	          	      }break;
	          	
	           case 1 :                                           //dataΪ1 ���ñ�����ʱ��
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
	          	case 2 :												//dataΪ2 ���ñ������֡�
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
	          	case 3 :							                	//dataΪ3 �������塰ʱ��			
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
	          	case 4 :                                             //dataΪ4 �������塰�֡�
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
//===========================����ģʽ=========================================//			
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
		  			 		data=1;        //��set3��һѭ��
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
		  			      	case 4 :								//����ʱ�����ģʽ
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
//===========================������=========================================//		
	void main()
	{
	   GCC_DELAY(100);  //��ʱ��ϵͳ�ȶ�
	   
	   Init_clock();   //��ʼ��ʱ��
//======================�˿ڳ�ʼ��==============================//	   
	   GPIOA_INIT(GPIO_Pin_All,GPIO_Mode_OUT,DISABLE,RESET);
	   GPIOB_INIT(GPIO_Pin_All,GPIO_Mode_OUT,RESET);
	   GPIOC_INIT(GPIO_Pin_All,GPIO_Mode_OUT,SET);	   
	   GPIOD_INIT(GPIO_Pin_All,GPIO_Mode_OUT,RESET);
	   
	   GPIOA_INIT(GPIO_Pin_1,GPIO_Mode_OUT,DISABLE,SET);
	   	   
	   GPIOB_INIT(GPIO_Pin_4,GPIO_Mode_INT,RESET);
	   GPIOB_INIT(GPIO_Pin_3,GPIO_Mode_INT,RESET);
	   GPIOB_INIT(GPIO_Pin_2,GPIO_Mode_INT,RESET);
//======================END====================================//
     buz=0;        //�ط�����
     buzopen=0;    //�������������־
	   bbRam=0;	    
	   data=1;    //Ĭ�Ͽ���Сʱ ��˸λ��ѡ��  
	   
	   while(1)
		 {
		 	GCC_CLRWDT();   //ι��
      test_mode();  //����ģʽ �ϵ�ǰͬʱ������������
//========================END==================================//
		 }
	}