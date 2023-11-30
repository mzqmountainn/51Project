#include <REGX52.H>
void Timer2Init(void)		//1毫秒@11.0592MHz
{
	T2MOD = 0;		//初始化模式寄存器
	T2CON = 0;		//初始化控制寄存器
	TL2 = 0x66;		//设置定时初值
	TH2 = 0xFC;		//设置定时初值
	RCAP2L = 0x66;		//设置定时重载值
	RCAP2H = 0xFC;		//设置定时重载值
	TR2 = 1;		//定时器2开始计时
	ET2 = 1;
}
