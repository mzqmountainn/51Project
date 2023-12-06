#include <REGX52.H>
#include "Delay.h"
#include "UART.h"
#include "LCD1602.h"
#include "key_selfPlus.h"
#include "Timer0.h"
#include <stdlib.h>
#include "MatrixKey.h"
#include "AT24C02.h"

typedef enum{false = 0,true =1} bool;

unsigned char key;
unsigned char Mkey;
char pwm ; 
bool startStatus = 0;
bool setMode = 0;
bool setModeFlag = 0;
//此处变量为uart读取数据用变量（此处开始）
//bool getChar =0;
unsigned char rawChar[10];
int frontData,endData;
//此处结束
//电机驱动定义 开始
sbit IN1 = P1^0;
sbit IN2 = P1^1;
sbit ENA = P1^2;
unsigned char count,compare;
bool motorEnable = 0;
//结束
void parse();
void changeJudge();

void main()
{
	pwm = (char)AT24C02_receiveByte(0);
	UART_Init();		//串口初始化
	LCD_Init();
	Timer0Init();
	//pwm = AT24C02_receiveByte(0);
	while(1)
	{
		//LCD_ShowString(2,1,rawChar);
		key=key_return();
		Mkey = MatrixKey();
		
		compare=abs(pwm);
		
		if(key == 1){
			startStatus = !startStatus;
			if(startStatus)
				motorEnable =1;
			else
				motorEnable =0;
		}
		
		if(key == 2)
			setMode = !setMode;
		if(key == 3&&pwm!=100&&setMode)
			pwm+=10;
		if(key == 4&&pwm!=-100&&setMode)
			pwm-=10;
		if(Mkey == 1){
			P2_1 = !P2_1;
			AT24C02_sendByte(0,(unsigned char)pwm);
			Delay(5);
		}
		if(Mkey == 2){
			motorEnable=!motorEnable;
		}
		
		if(motorEnable)
			ENA =1;
		if(!motorEnable)
			ENA =0;
		
		if(!startStatus)
			{
			LCD_ShowString(1,1,"                 ");
			LCD_ShowString(2,1,"                 ");
		}
		if(startStatus){									//负数显示与三位数显示未装载
			if(!setMode){
				LCD_ShowString(1,1,"-P-");
				if(pwm>0){
					if(pwm!=100){
						LCD_ShowNum(1,4,pwm,2);LCD_ShowString(1,6,"     ");}
					else
						LCD_ShowNum(1,4,pwm,3);
					if(pwm==0){LCD_ShowNum(1,4,0,1);LCD_ShowString(1,5,"     ");}
				}else if(pwm<0){
					LCD_ShowString(1,4,"-");
					if(pwm!=-100){
						LCD_ShowNum(1,5,0-pwm,2);LCD_ShowString(1,7,"     ");}
					else
						LCD_ShowNum(1,5,0-pwm,3);
				}
				if(pwm==0){LCD_ShowNum(1,4,0,1);LCD_ShowString(1,5,"        ");}
				
				//LCD_ShowString(1,1,"-P-");
				//LCD_ShowNum(1,4,pwm,2);
			}
			if(setMode){
				LCD_ShowString(1,1,"-S-");
				if(pwm>0){
					if(pwm!=100){
						if(setModeFlag)
							LCD_ShowNum(1,4,pwm,2);
						else
							LCD_ShowString(1,4,"     ");
					}else{
						if(setModeFlag)
							LCD_ShowNum(1,4,pwm,3);
						else
							LCD_ShowString(1,4,"     ");
					}
					
				}else if(pwm<0){
					LCD_ShowString(1,4,"-");
					if(pwm!=-100){
						if(setModeFlag)
							LCD_ShowNum(1,5,0-pwm,2);
						else
							LCD_ShowString(1,4,"      ");
					}else{
						if(setModeFlag)
							LCD_ShowNum(1,5,0-pwm,3);
						else
							LCD_ShowString(1,4,"       ");
					}
				}
				if(pwm==0){
					if(setModeFlag)
						LCD_ShowNum(1,4,0,1);
					else
						LCD_ShowString(1,4,"       ");}
//				LCD_ShowString(1,1,"-S-");
//				if(setModeFlag)
//					LCD_ShowNum(1,4,pwm,2);
//				else
//					LCD_ShowString(1,4,"   ");
			}

		}
	}
}

//void UART_Routine() interrupt 4
//{
//	
//	if(RI==1)					//如果接收标志位为1，接收到了数据
//	{
//		//P2=~SBUF;				//读取数据，取反后输出到LED
//		charFromU = SBUF;
//		UART_SendByte(SBUF);	//将受到的数据发回串口
//		getChar =1;
//		RI=0;					//接收标志位清0
//		


//	}
//}

void USART() interrupt 4   //标志位TI和RI需要手动复位，TI和RI置位共用一个中断入口
{
    ReceiveString();
	PutString(rawChar);
	parse();
	changeJudge();
    RI=0;  //接收并处理一次数据后把接收中断标志清除一下，拒绝响应在中断接收忙的时候发来的请求
}
 
void Timer0_Rountine(void) interrupt 1
{
	static unsigned int T0count,setModeCount,countT;
	T0count++;
	setModeCount++;
	countT++;
	countT%=100;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	if(T0count == 20){
		//P2_5 = 0;
		key_loop();
		T0count = 0;
	}
	if(setModeCount >=500){
		setModeFlag = !setModeFlag;
		setModeCount=0;
	}
	if(startStatus&&motorEnable){
		if(pwm>=0){
			IN2=0;
			if(countT<compare)
				IN1=1;
			else
				IN1=0;
		}else{
			IN1=0;
			if(countT<compare)
				IN2=1;
			else
				IN2=0;
		}
	}

}
void parse(){
	int location = 0;
	int r_location;
	for(location =0;location<10;location++){
		if(rawChar[location]=='-'&&location!=0){
			rawChar[location] = '\0';
			break;
		}}
	frontData = atoi(rawChar);
	endData = atoi(&(rawChar[location+1]));
//	LCD_ShowNum(1,7,frontData,3);	//测试用
//	LCD_ShowNum(2,7,endData,3);
}
void changeJudge(){
	if(frontData == pwm&&setMode){
		if(endData<=100 && endData>=-100)
			pwm = endData;
	}
}

