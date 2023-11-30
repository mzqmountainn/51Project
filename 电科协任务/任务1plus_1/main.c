#include <REGX52.H>
#include "Delay.h"
#include "key_plus.h"
#include "Timer0.h"
#include "Timer1.h"
#include "Timer2.h"

typedef enum{false = 0,true = 1} bool;

unsigned int keyNum = 0;
unsigned int timeGap = 500;
bool direction = 1;  // 1 is left 0 is right
int LEDnum = 0;
bool flag = 0; // K1标志  
char mask = 0x01;
char temp_byte,swap ;

void main(void){

	while(1){
		Timer1Init();
		LEDnum=  0;
		direction = 1;
		flag = 0;
		P2 = 0XFF;
//		Timer0Init();
		while(1){
			keyNum = key_return();

			if(timeGap>1500)
					timeGap = 500;
			if(keyNum==1)
			{	flag  =1;
				P2 = 0XFF;
			}
			
//			if(keyNum == 1){
//				flag = 1;

//				Delay(500);
//				direction = 1;

//			}
			if(keyNum == 2)
				direction =!direction;
			if(keyNum == 4)
				break;
			if(keyNum == 3){
				//P2_5 = ~P2_5;
				timeGap+=250;

			}
		}
		
	}
}
void Timer1_Rountine(void) interrupt 3
{
	static unsigned int t1,t2,key;
	char temp;
	TL1 = 0x66;		//设置定时初值
	TH1 = 0xFC;		//设置定时初值
	t1++;t2++;key++;
	if(t1 == 1000){
		P2_0 =~P2_0;
		t1 = 0;
	}
	if(t2 == timeGap){
		if(LEDnum == 7) LEDnum = 0;
		//P2_1=~P2_1;
		t2 = 0;if(flag){//
		if(direction){
			temp_byte = P2&mask; //获取最后一位
			temp =temp_byte|0xfe;
			P2 = ((~(0x80>>LEDnum))&temp);
		}else{
			temp_byte = P2&mask; //获取最后一位
			temp =temp_byte|0xfe;
			P2 = ((~(0x01<<(LEDnum+1)))&temp);
		}
		LEDnum++;}//
		
		
	}
	if(key>20)	//每隔20毫秒调用按键扫描函数
	{
		key_loop();
		key = 0;
	}


}
//void Timer0_Rountine(void) interrupt 1
//{
//	static unsigned int t0;
//	TL0 = 0x66;		//设置定时初值
//	TH0 = 0xFC;		//设置定时初值
//	t0++;
//	if(t0 == timeGap){
//		P2_7 =~P2_7;
//		t0 = 0;
//	}
//}

