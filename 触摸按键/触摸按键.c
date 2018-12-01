#include<STC15F104E.h>

sbit l1=P3^0;
sbit l2=P3^1;
sbit key=P3^2;
sbit l3=P3^3;

bit b,d,l,n;                     //定义开始，双击，长按，计数标志位

void interrupt_init();           //声明中断初始化函数
void T0_init();                  //声明T0初始化函数

void main()
{
    interrupt_init();            //声明中断初始化
    T0_init();                   //声明T0初始化
    
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
    EA=1;                       //总中断开
    ET0=1;                      //T0溢出中断开
    EX0=1;                      //INT0中断开
}

void T0_init()	             	//5毫秒@11.0592MHz
{
	AUXR |= 0x80;		        //定时器时钟1T模式
	TMOD &= 0xF0;		        //设置定时器模式
	TL0 = 0x00;		            //设置定时初值
	TH0 = 0x28;		            //设置定时初值
	TF0 = 0;		            //清除TF0标志
	TR0 = 0;		            //定时器0暂不计时
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