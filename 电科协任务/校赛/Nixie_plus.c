#include <REGX52.H>
#include "Delay.h"	//包含Delay头文件

//数码管显示缓存区
unsigned char Nixie_buf[8]={10,10,10,10,10,10,10,10};

//数码管段码表    10 不显示 11 - 12 C
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0x40,0x39};

void Nixie_set(unsigned char location,Data){
	Nixie_buf[location] = Data;
}

//数码管显示子函数
void Nixie_scan(unsigned char Location,Number)
{
	P0=0x00;				//段码清0，消影-
	switch(Location)		//位码输出
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[Number];	//段码输出

}

void Nixie_loop(void){
	static int time ;
	Nixie_scan(time+1,Nixie_buf[time]);
	time++;
	if(time>=8)time = 0;
}
	











