#include <REGX52.H>
#include "Delay.h"
#include "key_selfPlus.h"
#include "Timer0.h"
#include "Nixie_plus.h"
#include "DS18B20.h"

void change(void);
void check();
void ringCheck();

typedef enum{false = 0,true =1} bool;
sbit led =P2^0;


unsigned char hour =23,min =59,sec =59;
char showMode =0;
unsigned char keyNum;
float T;
unsigned char ring[3]={0}; //h,m,s
bool setMode =0; //定义设置模式
int setSelect; //定义设置选择
/*unsigned*/ char setBuf[3];
bool setBufReady=0;
int startRing=0;


void main(){
	led=1;
	DS18B20_ConvertT();	
	Delay(1000);
	
	Timer0Init();
	
	while(1){
		//DS18B20_ConvertT();	//转换温度
		//T=DS18B20_ReadT();	//读取温度
		ringCheck();
		keyNum = key_return();
		if(keyNum == 1){
			if(!setMode){
				showMode++;
				showMode%=3;
			}
			if(setMode){
				setSelect++;
				setSelect%=3;
			}
		}
		if(keyNum ==4){
			if(setMode){
				setBufReady=0;
				if(showMode==0){
					hour = setBuf[0];
					min= setBuf[1];
					sec= setBuf[2];
				}
				if(showMode==1){
					ring[0] = setBuf[0];
					ring[1] = setBuf[1];
					ring[2] = setBuf[2];
				}
			}
			if(showMode !=2)
				setMode = !setMode;
			
		}

		
		
		
		if(showMode == 0&&!setMode){
			Nixie_set(0,hour/10);
			Nixie_set(1,hour%10);
			Nixie_set(2,11);
			Nixie_set(3,min/10);
			Nixie_set(4,min%10);
			Nixie_set(5,11);
			Nixie_set(6,sec/10);
			Nixie_set(7,sec%10);
		}
		if(showMode == 1&&!setMode){
			Nixie_set(0,ring[0]/10);
			Nixie_set(1,ring[0]%10);
			Nixie_set(2,11);
			Nixie_set(3,ring[1]/10);
			Nixie_set(4,ring[1]%10);
			Nixie_set(5,11);
			Nixie_set(6,ring[2]/10);
			Nixie_set(7,ring[2]%10);
		}
		if(showMode == 2){
			Nixie_set(0,10);
			Nixie_set(1,10);
			Nixie_set(2,10);
			Nixie_set(3,10);
			Nixie_set(4,10);
			Nixie_set(5,(int)T/10);
			Nixie_set(6,(int)T%10);
			Nixie_set(7,12);
		}
		
		if(setMode){
			if(showMode == 0){
				if(!setBufReady){
					setBuf[0]=hour;
					setBuf[1]=min;
					setBuf[2]=sec;
					setBufReady=1;
				}

				change();
				check();
			}
			if(showMode == 1 ){
				if(!setBufReady){
					setBuf[0]=ring[0];
					setBuf[1]=ring[1];
					setBuf[2]=ring[2];
					setBufReady=1;
				}
				change();
				check();
			}

			
		}
	}
}
void change(void){
	if(keyNum ==2){
		setBuf[setSelect]++;
	}
	if(keyNum ==3){
		setBuf[setSelect]--;
	}
}
void ringCheck(){
	if(hour==ring[0]&&min==ring[1]&&sec==ring[2])
		startRing=1;
}

void showBlankLoop(void){
	static bool blankStatus;
	if(setMode){
		if(setSelect ==0){
			if(blankStatus){
				Nixie_set(0,10);
				Nixie_set(1,10);
			}else{
				if(showMode == 0){
					Nixie_set(0,setBuf[0]/10);
					Nixie_set(1,setBuf[0]%10);
				}
				if(showMode == 1){
					Nixie_set(0,setBuf[0]/10);
					Nixie_set(1,setBuf[0]%10);
				}

			}
		}
		if(setSelect ==1){
			if(blankStatus){
				Nixie_set(3,10);
				Nixie_set(4,10);
			
			}else{
				if(showMode == 0){
					Nixie_set(3,setBuf[1]/10);
					Nixie_set(4,setBuf[1]%10);
				}
				if(showMode == 1){
					Nixie_set(3,setBuf[1]/10);
					Nixie_set(4,setBuf[1]%10);
				}
			}
		}
		if(setSelect ==2){
			if(blankStatus){
				Nixie_set(6,10);
				Nixie_set(7,10);
			}else{
				if(showMode == 0){
					Nixie_set(6,setBuf[2]/10);
					Nixie_set(7,setBuf[2]%10);
				}
				if(showMode == 1){
					Nixie_set(6,setBuf[2]/10);
					Nixie_set(7,setBuf[2]%10);
				}
			}
		}
			
			
	}
	blankStatus =!blankStatus;
}
void check(){
	if(setBuf[0]>=24)
		setBuf[0]=0;
	if(setBuf[0]<0)
		setBuf[0]=23;
	if(setBuf[1]>=59)
		setBuf[1]=0;
	if(setBuf[1]<0)
		setBuf[1]=59;
	if(setBuf[2]>=59)
		setBuf[2]=0;
	if(setBuf[2]<0)
		setBuf[2]=59;

}

void Sec_Loop(void)
{
	if(1)
	{
		sec++;
		if(sec>=60)
		{
			sec=0;
			min++;
			if(min>=60)
			{
				min=0;
				hour++;
				if(hour>=24)
				{
					hour=0;
				}
			}
		}
	}
}







void Timer0_Rountine(void) interrupt 1
{
	static unsigned int T0count,nixieCount,secLoop,blank,count,ringTimeCount;
	T0count++;
	nixieCount++;
	secLoop++;
	blank++;
	count++;
	TL0 = 0x66;		//?????????
	TH0 = 0xFC;		//?????????
	if(T0count == 20){
		key_loop();
		T0count = 0;
	}
	if(nixieCount>=2){
		nixieCount=0;
		Nixie_loop();
	}
	if(secLoop>=1000){
		DS18B20_ConvertT();	//转换温度
		T=DS18B20_ReadT();	//读取温度
		Sec_Loop();
		secLoop=0;
	}
	if(blank == 500){
		showBlankLoop();
		blank = 0;
	}
	if(count == 200){
		if(startRing){
			led=!led;
			ringTimeCount++;
		}
		if(ringTimeCount == 10){
			startRing =0;
			ringTimeCount=0;
		}
		count = 0;
	}
	

}

//void showBlankLoop(void){    //备份
//	static bool blankStatus;
//	if(setMode){
//		if(setSelect ==0){
//			if(blankStatus){
//				Nixie_set(0,10);
//				Nixie_set(1,10);
//			}else{
//				if(showMode == 0){
//					Nixie_set(0,hour/10);
//					Nixie_set(1,hour%10);
//				}
//				if(showMode == 1){
//					Nixie_set(0,ring[0]/10);
//					Nixie_set(1,ring[0]%10);
//				}

//			}
//		}
//		if(setSelect ==1){
//			if(blankStatus){
//				Nixie_set(3,10);
//				Nixie_set(4,10);
//			
//			}else{
//				if(showMode == 0){
//					Nixie_set(3,min/10);
//					Nixie_set(4,min%10);
//				}
//				if(showMode == 1){
//					Nixie_set(3,ring[1]/10);
//					Nixie_set(4,ring[1]%10);
//				}
//			}
//		}
//		if(setSelect ==2){
//			if(blankStatus){
//				Nixie_set(6,10);
//				Nixie_set(7,10);
//			}else{
//				if(showMode == 0){
//					Nixie_set(6,sec/10);
//					Nixie_set(7,sec%10);
//				}
//				if(showMode == 1){
//					Nixie_set(6,ring[2]/10);
//					Nixie_set(7,ring[2]%10);
//				}
//			}
//		}
//			
//			
//	}
//	blankStatus =!blankStatus;
//}