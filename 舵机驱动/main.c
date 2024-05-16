#include <REGX52.H>
#include "Timer1.h"
#include "Delay.h"

typedef enum{false = 0,true =1} bool;
int count =0;
sbit sgControl = P2^3;
int pwm = 1; 
void main()
{
	Timer1Init();
	sgControl =0;
	while(1){
		count =0;
	pwm = 1; 
	Delay(400);
		count =0;
	pwm = 2; 
	Delay(400);
		count =0;
	pwm = 3; 
	Delay(400);
		count =0;
	pwm = 4; 
	Delay(400);
		count =0;
	pwm = 5; 
	Delay(400);
	}
}

void Timer1_Rountine(void) interrupt 3
{
	//static unsigned int count;
	TL1 = 0x33;		//设置定时初值
	TH1 = 0xFE;		//设置定时初值
	count++;
	count%=40;
	if(count<pwm){
		sgControl = 1;
	}else
	{
		sgControl = 0;
	}

}




