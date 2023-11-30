#include <REGX52.H>
#include <INTRINS.H>
#include "LCD1602.h"	//包含LCD1602头文件
#include "Delay.h"		//包含Delay头文件
//#include "MatrixKey.h"
#include "Timer0.h"
//#include "key.h"
//#include "DS1302.h"
#include "Nixie.h"
#include "AT24C02.h"
#include "key_selfPlus.h"

sbit motor = P1^0;
sbit beep = P2^5;
int i = 0;

typedef enum{false = 0,true =1} bool;
unsigned int keyNum = 0;
unsigned int count,compare;
unsigned char mode = 0;
void main()
{

	Timer0Init();
	count = 0;
	while(1){
		keyNum = key_return();
		if(keyNum == 1){
			mode++;
			mode%=4;
		}
		switch(mode){
			case 0:compare= 0;break;
			case 1:compare = 50;break;
			case 2:compare = 75;break;
			case 3:compare = 100;break;
		}
		Nixie(1,mode);
	}
	
	
}


void Timer0_Rountine(void) interrupt 1
{
	static unsigned int T0count;
	T0count++;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	if(T0count == 20){
		//P2_5 = 0;
		key_loop();
		T0count = 0;
	}
	count++;
	count%=100;
	if(count<compare)
		motor = 1;
	if(count>=compare)
		motor = 0;
}
