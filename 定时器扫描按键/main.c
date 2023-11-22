#include <REGX52.H>
#include <INTRINS.H>
#include "LCD1602.h"	//包含LCD1602头文件
//#include "Delay.h"		//包含Delay头文件
//#include "MatrixKey.h"
#include "Timer0.h"
//#include "key.h"
//#include "DS1302.h"
#include "Nixie.h"
#include "AT24C02.h"
#include "key_selfPlus.h"


sbit beep = P2^5;
int i = 0;

typedef enum{false = 0,true =1} bool;
unsigned int keyNum = 0;
unsigned int num = 0;

void main()
{
	unsigned char temp ; 
	Timer0Init();
	while(1){
		keyNum = key_return();
		if(keyNum){
			temp = keyNum;
			Nixie(1,temp);
		}
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
}
