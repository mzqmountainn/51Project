/*#include <REGX52.H>
#include <Timer0.h>
#include <Delay.h>
#include <LCD1602.h>
#include <intrins.h>

sbit Trig=P2^2;   	 //控制端 
sbit Echo=P2^1; 	 //接收端

unsigned int receiveTime,realTime;
unsigned int length=0;
void main(void){
	Timer0Init();
	LCD_Init();
	Timer0_setCounter(0);
	while(1){
		Trig=0;
		Echo=0;
		Timer0_run(1);
		LCD_ShowString(1,1,"nmsl");
		
		Trig=1;
		Delay10us();
		_nop_();
		//while(!Echo);
		Timer0_setCounter(0);
		Trig=0;

		while(Echo);
		receiveTime = Timer0_getCounter();
		
		realTime = (unsigned int)(receiveTime*0.916);
		length = (unsigned int)(realTime*0.017);
		
		LCD_ShowNum(2,9,realTime,5);//
		LCD_ShowNum(2,1,length,5);
		LCD_ShowString(2,6,"cm");
		Timer0_run(0);
		//Delay(1000);
	}
}*/
#include <intrins.h>
#include <REGX52.H>
#include <Delay.h>
#include <LCD1602.h>
sbit Trig=P2^2;   	 //控制端 
sbit Echo=P2^1; 	 //接收端

 //微秒级延时函数，延时t微秒，注意要包含头文件“intrins.h”
void delay_us(unsigned char t)
{
	while(t--)
	{
				_nop_();
	}
}

void HC_SR04_Init(void) //用到了T0计时器
{
		TMOD &= 0xf1; //把T0配置为16位的定时计数模式
}
float getDistance(void) //获取一次距离值
{
		unsigned int n; 
		Trig = 1;
		TH0 = TL0 = 0;
		delay_us(10);
		Trig = 0; //10us以上的高电平脉冲
		while(!Echo); //等待返回，如果Echo为高就要开始计时了
		TR0 = 1;  //启动计时器
		while(Echo) ; //等待输出的高电平结束
		TR0 = 0; //关掉计时器
		n = (TH0)*256+TL0; //计算计数的数值
//		sendOneByte(TH0); //用于串口调试，可忽略s
//		sendOneByte(' ');
//		sendOneByte(TL0);
		return 22.1*n/10000; //单位cm
}
void main(void){
	HC_SR04_Init();
	LCD_Init();
	while(1){
		LCD_ShowNum(2,1,(unsigned int)getDistance(),5);
		Delay(100);
	}
}
