#include <REGX52.H>
#include "control.h"
#include "Delay.h"

//extern sbit IN1=P1^4;
//extern sbit IN2=P1^5;
//extern sbit IN3=P1^3;
//extern sbit IN4=P1^2;
//extern sbit EN1=P1^7;
//extern sbit EN2=P1^6;
//extern sbit trace1  =P2^3;
//extern sbit trace2  =P2^2;
//extern sbit trace3  =P2^1;
//extern sbit trace4  =P2^0;

#define R_FIX 0 //右修正量（车一直向右偏）

//c_ 小车车轮运动控制函数
extern int pwmL,pwmR;
void c_stop(void){
	IN2=0;IN3=0;
	IN1=0;IN4=0;
	pwmL=0;pwmR=0;
}
void c_goStraight(void){
	IN2=1;IN3=1;
	IN1=0;IN4=0;
	pwmL=20;pwmR=20+R_FIX;//30
}
void c_turnLeft(void){
	IN2=1;IN3=1;
	IN1=0;IN4=0;
	pwmL=15;pwmR=24+R_FIX;
}
void c_turnRight(void){
	IN2=1;IN3=1;
	IN1=0;IN4=0;
	pwmL=24;pwmR=15+R_FIX;
}
void c_turnLeftStop(void){ //宸﹁疆鍋滄
	IN2=0;IN3=1;
	IN1=0;IN4=0;
	pwmL=15;pwmR=10+R_FIX;
}


void control(){
	if(trace4 == 0 &&trace3 == 0 &&trace2== 0 &&trace1 == 0 )//浠�涔堜篃娌℃湁
	{
		c_stop();
	}
	if(trace4 == 1 &&trace3 == 1 &&trace2== 1 &&trace1 == 1 )//鍥涗釜浼犳劅鍣ㄩ兘鎰熷簲鍒伴粦绾�
	{
		c_goStraight();
	}
	if(trace4 == 0 &&trace3 == 1 &&trace2== 1 &&trace1 == 0)//灏忚溅鐩磋
	{
		 //c_turnLeftStop();//
		c_goStraight();
	}
	if(trace4 == 0 &&trace3 == 0 &&trace2== 1 &&trace1 == 0)//鍋忓乏锛屽悜鍙�
	{
		c_turnRight();
		Delay(4);
		if(trace4 == 0 &&trace3 == 0 &&trace2== 0 &&trace1 == 0)
		{
			c_turnLeft();
			Delay(50);
		}
	}
	if(trace4 == 0 &&trace3 == 1 &&trace2== 0 &&trace1 == 0)//鍋忔湁锛屽悜宸�
	{
		c_turnLeft();
		Delay(4);
		if(trace4 == 0 &&trace3 == 0 &&trace2== 0 &&trace1 == 0)
		{
			c_turnRight();
			Delay(50);
		}
	}
	

	if((trace4 == 1 &&trace3 == 1 &&trace2== 1 &&trace1 == 0 )||(trace4 == 1 &&trace3 == 1 &&trace2== 0 &&trace1 == 0))//直鐩磋宸﹁浆
	{
		c_goStraight();
		Delay(50);//
		if(trace4 == 0 &&trace3 == 0 &&trace2== 0 &&trace1 == 0 )//宸﹁浆涓�
		{
			c_stop();
			Delay(200);
			c_turnLeftStop();
			while(!(trace4 == 0 &&trace3 == 1 &&trace2== 0 &&trace1 == 0||trace4 == 0 &&trace3 == 1 &&trace2== 1 &&trace1 == 0));
			//鏀瑰姩寮�濮�
			c_goStraight();
			Delay(600);
			IN2=1;IN3=0;
			IN1=0;IN4=0;
			pwmL=15;pwmR=0;
			Delay(300);
			//鏀瑰姩缁撴潫
		}
	}
	if(trace4 == 1 &&trace3 == 0 &&trace2== 0 &&trace1 == 0 )//澶у渾寮ц浆寮悜宸�
	{
		IN2=1;IN3=1;
		IN1=0;IN4=0;
		pwmL=10;pwmR=28+R_FIX;
	}
	if(trace4 == 0 &&trace3 == 0 &&trace2== 0 &&trace1 == 1 )//澶у渾寮ц浆寮悜鍙�
	{
		IN2=1;IN3=1;
		IN1=0;IN4=0;
		pwmL=30;pwmR=10;wrg+  
	}

}