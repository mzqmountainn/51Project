#include <REGX52.H>

void Timer1Init(void)		//0.5毫秒@11.0592MHz
{
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x33;		//设置定时初值
	TH1 = 0xFE;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	EA =1;
	ET1 =1;
}


