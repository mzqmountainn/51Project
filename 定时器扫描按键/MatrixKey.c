#include <REGX52.H>
#include "LCD1602.h"	//包含LCD1602头文件
#include "Delay.h"		//包含Delay头文件

unsigned int MatrixKey()
{
	unsigned int num = 0;
	P1 = 0xFF;
	P1_3 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);num = 1;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);num = 5;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);num = 9;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);num = 13;}
	
	P1 = 0xFF;
	P1_2 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);num = 2;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);num = 6;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);num = 10;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);num = 14;}
	
	P1 = 0xFF;
	P1_1 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);num = 3;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);num = 7;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);num = 11;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);num = 15;}
	
	P1 = 0xFF;
	P1_0 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);num = 4;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);num = 8;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);num = 12;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);num = 16;}
	
	return num;
}