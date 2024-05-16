#include <REGX52.H>
#include "Timer0.h"
#include "trace.h"

typedef enum{false = 0,true =1} bool;
int pwmL,pwmR;

sbit OUT1 = P1^0;
sbit OUT2 = P1^1;
sbit OUT3 = P1^2;
sbit OUT4 = P2^3;
//out为高电平时，电机转动



int main(void){
	Timer0Init();
	P1=0x00;
	while(1){
		controlMotor();
	}
	
}

void Timer0_Rountine(void) interrupt 1
{
	static unsigned int countT;
	countT++;
	countT%=100;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	if(pwmL<=countT){
		OUT1 = 0;
	}
	if(pwmL>countT){
		OUT1 = 1;
	}
	
	if(pwmR<=countT){
		OUT2 = 0;
	}
	if(pwmR>countT){
		OUT2 = 1;
	}

}