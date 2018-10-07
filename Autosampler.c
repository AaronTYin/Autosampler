#include <STC89C52RC.h>

//P20-P1.0ת������
//P21-P1.1ת�̷���
//P22-P1.2�������
//P23-P1.3��۷���
//P25-P0.1����λ
//P26-P0.2����λ
//P27-P0.0����������


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
	TL1=0xe8;	//1200������12MHz
	TR1=1;
	SCON=0x50;
	TI=1;
	
	
	while(0)
	{
		//ת�����
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
	

		//����ͨѶ
		/*for(i=0;i<10;i++)
		{
			while(TI=0);
			TI=0;
			SBUF=i;			//����i
		}*/
		/*if(RI)			//���յ��ַ�
		{
			i=SBUF;			//����i
			RI=0;			//���ձ�־λRI
			TI=0;			//���ͽ�����־λTI
			SBUF=i;			//����i
			while(TI==0);			//�ȴ��������
		}*/
		
	
	
		
	//��λ����
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
			if(fi==1)		//ת��ת�ķ���
			{
				P21=~P21;
				while(1)
				{
					runo();
					if(RI)
						goto loop;
				}
			}
			if(fi==2)		//ֹͣ
			{
				P20=0;
				goto loop;
			}
			if(fi==3)		//����
			{
				while(1)
				{
					runo();
					if(RI)
						goto loop;
				}
			}
			if(fi==4)		//��ȡ
			{
				P20=0;
				updown();
				goto loop;
			}
		}
	}
}