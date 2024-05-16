#include <REGX52.H>
void Timer0Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;
	TL0 = 0;		//设置定时初值
	TH0 = 0;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0不计时
}
void Timer0_setCounter(int value){
	TL0 = value%256;
	TH0 = value/256;
}
void Timer0_run(unsigned char flag){
	TR0 = flag;
}
unsigned int Timer0_getCounter(void){
	return (TH0<<8)|TL0;
}