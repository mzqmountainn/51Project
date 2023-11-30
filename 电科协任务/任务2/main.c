#include <REGX52.H>
#include <Delay.h>
#include <key_plus.h>
#include <LCD1602.h>
#include <Timer0.h>
#include "Timer1.h"
#include "intrins.h"

typedef enum{false = 0,true =1} bool;

int keyNum ;
int interface = 1;
int minute[3] = {0};
int second[3] = {0};
bool timer_enable = 0;
int flag = 0;
sbit speak=P2^5;

void interfaceChoose(int n);
void beep(void);

void main()
{
	LCD_Init();
	Timer1Init();
	while(1){

		/*for(i =0;i<500;i++){
			speak = !speak;
		}蜂鸣器*/
		if(flag){
			flag = 0;
			beep();
		}
		keyNum = key_return();
		if(keyNum == 1&& timer_enable == 0){
			interface++;
			if(interface >= 4)
				interface = 1;
		}
		if(keyNum == 2&& timer_enable == 0){
			minute[interface-1]++;
			if(minute[interface-1]==10)
				minute[interface-1]=0;
		}
		if(keyNum == 3&& timer_enable == 0){
			second[interface-1]++;
			if(second[interface-1]==60)
				second[interface-1]=0;
		}
		if(keyNum == 4){
			timer_enable = !timer_enable;
		}
		//数组实现数据结构（？）
		//LCD_ShowNum(1,1,interface,1);
		interfaceChoose(interface);
	}
}
void interfaceChoose(int n){
	if(n==1)
		LCD_ShowString(1,1,"Num1_");//LCD_ShowNum(1,6,minute[0],2);LCD_ShowString(1,8,":");LCD_ShowNum(1,9,second[0],2);
	if(n==2)
		LCD_ShowString(1,1,"Num2_");//LCD_ShowNum(1,6,minute[1],2);LCD_ShowString(1,8,":");LCD_ShowNum(1,9,second[1],2);
	if(n==3)
		LCD_ShowString(1,1,"Num3_");//LCD_ShowNum(1,6,minute[2],2);LCD_ShowString(1,8,":");LCD_ShowNum(1,9,second[2],2);
	LCD_ShowNum(1,6,minute[interface-1],2);LCD_ShowString(1,8,":");LCD_ShowNum(1,9,second[interface-1],2);
	Delay(20);
}
void beep(void){

	int i =3000;
	while(i--){
		speak=!speak;
		Delay(1);
	}
	i = 0;
	speak = 0;
}



void Timer1_Rountine(void) interrupt 3
{
	static unsigned int key,t1;
	TL1 = 0x66;		//设置定时初值
	TH1 = 0xFC;		//设置定时初值
	key++;t1++;
	if(t1==1000 ){
		/*if(timer_enable){
			second[interface-1]--;
			if(second[interface-1]<0){
				minute[interface-1]--;
				if(minute[interface-1]<0){ //计时结束 
					second[interface-1]=0;
					minute[interface-1]=0;
					timer_enable = 0;
					P2_1 = 0;//test
					flag = 1;
				}
				if(minute[interface-1]>=0){
					second[interface-1]=59;
				}
				
			}
		}*/
		if(timer_enable){
			if(second[interface-1]==0){
				if(minute[interface-1]==0){
					second[interface-1]=0;
					minute[interface-1]=0;
					timer_enable = 0;
					P2_1 = 0;//test
					flag = 1;
				}else{
					minute[interface-1]--;
					second[interface-1]=59;
				}
				
			}else
			{
				second[interface-1]--;
			}
		}
		t1 = 0;
	}
	if(key>20)	//每隔20毫秒调用按键扫描函数
	{
		key_loop();
		key = 0;
	}


}