#include <REGX52.H>
#include "Timer0.h"
#include "control.h"
#include "Delay.h"

typedef enum{false = 0,true =1} bool;
typedef enum{right = 0,back =1} direction;
direction L = right;direction R = right;
int pwmL,pwmR;
int modeL,modeR;
//in1ï¼Œ2ä¸ºå·¦ in2å‘å‰
//in3ï¼Œ4ä¸ºå³ï¼Œin3å‘å‰
//sbit IN1=P1^4;
//sbit IN2=P1^5;
//sbit IN3=P1^3;
//sbit IN4=P1^2;
//sbit EN1=P1^7;
//sbit EN2=P1^6;
////×îÓÒÊÇtrace1
//sbit trace1  =P2^3;
//sbit trace2  =P2^2;
//sbit trace3  =P2^1;
//sbit trace4  =P2^0;



int main(void){
	Timer0Init();
	pwmL =60;pwmR=55;
	P1=0x00;
	//IN2=1;IN3=1;
	EN1=1;EN2=1;
	while(1){
		control();
	}
	return 0 ;
}


void Timer0_Rountine(void) interrupt 1
{
	static unsigned int countT,countS;
	countT++;
	countT%=100;
	countT++;
	countT%=100;
	TL0 = 0x66;		//ÉèÖÃ¶¨Ê±³õÖµ
	TH0 = 0xFC;		//ÉèÖÃ¶¨Ê±³õÖµ
//	if(countT>=50){
//		P2_0=~P2_0;
//	}
	if(pwmL<=countT){
		EN1 = 0;
	}
	if(pwmL>countT){
		EN1 =1;
	}
	
	if(pwmR<=countT){
		EN2 = 0;
	}
	if(pwmR>countT){
		EN2 =1;
	}
	
	
}