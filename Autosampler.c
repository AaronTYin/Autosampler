#include <STC89C52RC.h>

//P20-P1.0转盘脉冲
//P21-P1.1转盘方向
//P22-P1.2针臂脉冲
//P23-P1.3针臂方向
//P25-P0.1下限位
//P26-P0.2上限位
//P27-P0.0霍尔传感器


void delay()
{
	TMOD=0x01;
	TH0=0xac;				//Speed
	TL0=0xf0;
	TF0=0;
	TR0=1;
	while(TF0==0);
	TR0=0;
}


void delayo()
{
	int i;
	for(i=0;i<2600;i++){}
}


void updown()
{
	int i=0;
	
	P23=1;
	
	for(i=0;i<430;i++)
	{	
		P22=1;
		delayo();
		P22=0;
		delayo();
	}
		
	P23=0;
	
	for(i=0;i<430;i++)
	{
		P22=1;
		delayo();
		P22=0;
		delayo();
	}
}


void runo()
{
	P20=1;
	delayo();
	P20=0;
	delayo();
}


void run()
{
	P20=1;
	delay();
	P20=0;
	delay();
}


main()
{
	int i;
	int fi;
	int T24=100;
	bit pf=0;
	TMOD=0x21;
	TH1=0xe8;
	TL1=0xe8;	//1200波特率12MHz
	TR1=1;
	SCON=0x50;
	TI=1;
	
	
	while(0)
	{
		//转盘针臂
		if(P27||T24!=0)
		{
			T24--;
			run();
		}
		if(P27) pf=1;
		else if(P27==0)
		{
			if(pf==1)
			{
				pf=0;
				T24=23;
			}
			if(pf==0&&T24==0)
			{
				updown();
				T24=8;//goto loop;
			}
		}
	}
	

		//串口通讯
		/*for(i=0;i<10;i++)
		{
			while(TI=0);
			TI=0;
			SBUF=i;			//发送i
		}*/
		/*if(RI)			//接收到字符
		{
			i=SBUF;			//接收i
			RI=0;			//接收标志位RI
			TI=0;			//发送结束标志位TI
			SBUF=i;			//发送i
			while(TI==0);			//等待发送完毕
		}*/
		
	
	
		
	//四位控制
	while(1){
		loop:if(RI)
		{
			fi=SBUF;
			RI=0;
			
			
			if(fi==0)		//Reset
			{
				P21=1;
				T24=100;
				while(1)
				{
					if(P27||T24!=0)
					{
						T24--;
						runo();
					}
					if(P27) pf=1;
					else if(P27==0)
					{
						if(pf==1)
						{
							pf=0;
							T24=23;
						}
						if(pf==0&&T24==0)
						{
							updown();
							T24=8;
							if(RI)
								goto loop;
						}
					}
				}
			}
			if(fi==1)		//转换转的方向
			{
				P21=~P21;
				while(1)
				{
					runo();
					if(RI)
						goto loop;
				}
			}
			if(fi==2)		//停止
			{
				P20=0;
				goto loop;
			}
			if(fi==3)		//继续
			{
				while(1)
				{
					runo();
					if(RI)
						goto loop;
				}
			}
			if(fi==4)		//抽取
			{
				P20=0;
				updown();
				goto loop;
			}
		}
	}
}