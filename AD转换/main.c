#include <REGX52.H>
#include <INTRINS.H>
#include "LCD1602.h"	//包含LCD1602头文件
#include "Delay.h"		//包含Delay头文件
//#include "MatrixKey.h"
//#include "Timer0.h"
//#include "key.h"
//#include "DS1302.h"
//#include "Nixie.h"
//#include "AT24C02.h"
#include "key_selfPlus.h"
#include "XPT2046.h"

sbit motor = P1^0;
sbit beep = P2^5;
int i = 0;

typedef enum{false = 0,true =1} bool;
unsigned int keyNum = 0;
unsigned int count,compare;
unsigned char mode = 0;
unsigned int ad1,ad2,ad3;
void main()
{

//	Timer0Init();
	count = 0;
	LCD_Init();
	LCD_ShowString(1,1,"wdnmd");
	while(1){
		ad1=XPT2046_readAD(XPT2046_XP);
		LCD_ShowNum(2,1,ad1,4);
		Delay(10);
		ad2=XPT2046_readAD(XPT2046_YP);
		LCD_ShowNum(2,6,ad2,4);
		Delay(10);
		ad3=XPT2046_readAD(XPT2046_VBAT);
		LCD_ShowNum(2,11,ad3,4);
		Delay(10);
		
	}
	
	
}


//void Timer0_Rountine(void) interrupt 1
//{
//	static unsigned int T0count;
//	T0count++;
//	TL0 = 0x66;		//设置定时初值
//	TH0 = 0xFC;		//设置定时初值
//	if(T0count == 20){
//		//P2_5 = 0;
//		key_loop();
//		T0count = 0;
//	}
//	count++;
//	count%=100;
//	if(count<compare)
//		motor = 1;
//	if(count>=compare)
//		motor = 0;
//}
