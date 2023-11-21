#include <REGX52.H>
#include <INTRINS.H>
#include "LCD1602.h"	//包含LCD1602头文件
#include "Delay.h"		//包含Delay头文件
//#include "MatrixKey.h"
//#include "Timer0.h"
#include "key.h"
//#include "DS1302.h"
//#include "Nixie.h"
#include "AT24C02.h"

sbit beep = P2^5;
int i = 0;

typedef enum{false = 0,true =1} bool;
unsigned int keyNum = 0;
unsigned int num = 0;

void main()
{
	LCD_Init();
	while(1){
		keyNum = key();
		if(keyNum == 1){
			num++;
			LCD_ShowNum(2,1,num,5);
		}
		if(keyNum == 2){
			num--;
			LCD_ShowNum(2,1,num,5);
		}
		if(keyNum == 4){
			num = AT24C02_receiveByte(0); //低位
			num |= AT24C02_receiveByte(1)<<8;
			LCD_ShowNum(2,1,num,5);
			LCD_ShowString(1,1,"Read OK");
			Delay(1000);
			LCD_ShowString(1,1,"         ");
		}
		if(keyNum == 3){
			LCD_ShowNum(2,1,num,5);
			AT24C02_sendByte(0,num%256);
			Delay(5);//注意写延时
			AT24C02_sendByte(1,num/256);
			Delay(5);
			LCD_ShowString(1,1,"Write OK");
			Delay(1000);
			LCD_ShowString(1,1,"         ");
		}
	}
	
	
	
	
	
	
//	unsigned char i;
//	LCD_Init();
//	AT24C02_sendByte(0,123);
//	Delay(5);
//	i = AT24C02_receiveByte(0);
//	LCD_ShowNum(1,1,i,5);
}

//void Timer0_Rountine(void) interrupt 1
//{
//	static unsigned int T0count;
//	T0count++;
//	TL0 = 0x66;		//设置定时初值
//	TH0 = 0xFC;		//设置定时初值
//	if(T0count == 1000){
//		if(blankJudge)
//			blankJudge = 0;
//		else
//			blankJudge = 1;

//		T0count = 0;
//	}
//}
