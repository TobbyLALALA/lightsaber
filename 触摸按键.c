#include<STC15F104E.h>
#include<iostream>

sbit l1=P3^0;
sbit l2=P3^1;
sbit key=P3^2;
sbit l3=P3^3;

bit b,d,l,n;                     //���忪ʼ��˫����������������־λ

void interrupt_init();           //�����жϳ�ʼ������
void T0_init();                  //����T0��ʼ������

void main()
{
    interrupt_init();            //�����жϳ�ʼ��
    T0_init();                   //����T0��ʼ��
    
    while(1)
    {
        if(d==1)
        {
            l1=1;
			l2=0;
			l3=0;
        }
        
        if(d==0)
        {
            l2=1;
			l1=0;
			l3=0;
        }
        
        if(l==1)
        {
            l3=1;
			l2=0;
			l1=0;
            l=0;
        }
    }
}

void interrupt_init()
{
    EA=1;                       //���жϿ�
    ET0=1;                      //T0����жϿ�
    EX0=1;                      //INT0�жϿ�
}

void T0_init()	             	//5����@11.0592MHz
{
	AUXR |= 0x80;		        //��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		        //���ö�ʱ��ģʽ
	TL0 = 0x00;		            //���ö�ʱ��ֵ
	TH0 = 0x28;		            //���ö�ʱ��ֵ
	TF0 = 0;		            //���TF0��־
	TR0 = 0;		            //��ʱ��0�ݲ���ʱ
}

void Int0_Routine(void)     interrupt 0
{
    TR0=!TR0;
    b=!b;
    
    if(d==1)
    {
        d=0;
    }
    
    if(b==1)
    {
        n=1;
        d=1;
    }
    else
    {
        n=0;
    }
}
    
void Timer0_Rountine(void) interrupt 1
{
    l=1;
    d=0;
    b=0;
}