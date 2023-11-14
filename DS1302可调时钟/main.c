#include <REGX52.H>
#include <INTRINS.H>
#include "LCD1602.h"	//包含LCD1602头文件
#include "Delay.h"		//包含Delay头文件
//#include "MatrixKey.h"
#include "Timer0.h"
#include "key.h"
#include "DS1302.h"

typedef enum{false = 0,true =1} bool;
unsigned int keyNum = 0;
int select = 0;
bool mode = 0;
bool blankJudge = 0; // 判断闪烁

void timeSet(void);
void timeShow(void);
void judge(int select,char * target);

void main()
{
	Timer0Init();
	LCD_Init();
	DS1302_Init();
	LCD_ShowString(1,1,"  -  -  ");//静态字符初始化显示
	LCD_ShowString(2,1,"  :  :  ");
	
	DS1302_SetTime();//设置时间
	while(1)
	{
		keyNum =key();
		if(keyNum == 1){
			if(mode){
				select = 0;
				DS1302_SetTime();
			}
			mode = !mode;
			
		}
		if(mode == 0)
			timeShow();
		else
			timeSet();

	}
}
void timeShow(void){
	DS1302_ReadTime();//读取时间
	LCD_ShowNum(1,1,DS1302_Time[0],2);//显示年
	LCD_ShowNum(1,4,DS1302_Time[1],2);//显示月
	LCD_ShowNum(1,7,DS1302_Time[2],2);//显示日
	LCD_ShowNum(2,1,DS1302_Time[3],2);//显示时
	LCD_ShowNum(2,4,DS1302_Time[4],2);//显示分
	LCD_ShowNum(2,7,DS1302_Time[5],2);//显示秒
}
void timeSet(void){
	if(keyNum == 2){
		select++;
		select%=6;
	}
	if(keyNum == 3){
		DS1302_Time[select]++;
	}
	if(keyNum == 4){
		DS1302_Time[select]--;
	}
	judge(select,DS1302_Time);
	
	if(blankJudge)
		LCD_ShowNum(1,1,DS1302_Time[0],2);
	if(!blankJudge&&select==0)
		LCD_ShowString(1,1+3*(select%3),"  ");
	
	if(blankJudge)
		LCD_ShowNum(1,4,DS1302_Time[1],2);
	if(!blankJudge&&select==1)
		LCD_ShowString(1,4,"  ");
	
	if(blankJudge)
		LCD_ShowNum(1,7,DS1302_Time[2],2);
	if(!blankJudge&&select==2)
		LCD_ShowString(1,7,"  ");
	
	if(blankJudge)
		LCD_ShowNum(2,1,DS1302_Time[3],2);
	if(!blankJudge&&select==3)
		LCD_ShowString(2,1,"  ");
	
	if(blankJudge)
		LCD_ShowNum(2,4,DS1302_Time[4],2);
	if(!blankJudge&&select==4)
		LCD_ShowString(2,4,"  ");
	
	if(blankJudge)
		LCD_ShowNum(2,7,DS1302_Time[5],2);
	if(!blankJudge&&select==5)
		LCD_ShowString(2,7,"  ");


}
void judge(int select,char target[]){
	if(select ==5 ||select ==4){				//分秒判断
		if(target[select]>59)
			target[select]=0;
		if(target[select]<0)
			target[select]=59;
	}
	if(select ==3){
		if(target[select]>23)
			target[select] = 0;
		if(target[select]<0)
			target[select]=23;
	}
	if(select == 1){ //月
		if(target[select]>12)
			target[select]=1;
		if(target[select]<1)
			target[select]=12;
	}
	if(select ==0){
		if(target[select]>99)
			target[select]=  0;
		if(target[select]<0)
			target[select] = 99;
	}
	if(target[1]==1||target[1]==3||target[1]==5||target[1]==7||target[1]==8||target[1]==10||target[1]==12)
	{
		if(target[2]>31)
			target[2]=1;
		if(target[2]<1)
			target[2]=31;
	}
	if(target[1]==4||target[1]==6||target[1]==9||target[1]==11)
	{
		if(target[2]>30)
			target[2]=1;
		if(target[2]<1)
			target[2]=30;
	}
	if(target[1]==2&&target[0]%4!=0){
		if(target[2]>28)
			target[2]=1;
		if(target[2]<1)
			target[2] = 28;
	}
	if(target[1]==2&&target[0]%4==0){
		if(target[2]>29)
			target[2]=1;
		if(target[2]<1)
			target[2] = 29;
	}
}

void Timer0_Rountine(void) interrupt 1
{
	static unsigned int T0count;
	T0count++;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	if(T0count == 1000){
		if(blankJudge)
			blankJudge = 0;
		else
			blankJudge = 1;

		T0count = 0;
	}
}
//void Timer0_Rountine(void) interrupt 1 //出现问题的 1114 1751  定时器出现问题 无法定时
//{
//	static unsigned int T0count;
//	T0count++;
//	TL0 = 0x66;		//设置定时初值
//	TH0 = 0xFC;		//设置定时初值
//	if(T0count == 1000){
//		P2_7 = !P2_7;
//		if(mode){
//			blankJudge = !blankJudge;
//			if(select<=2){
//				if(blankJudge)
//					LCD_ShowString(1,1+3*(select%3),"  ");		
//			else{
//				if(blankJudge)
//					LCD_ShowString(2,1+3*(select%3),"  ");
//			}
//		}


//		T0count = 0;
//	}
//}
//}