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

#define R_FIX 0 //������������һֱ����ƫ��

//c_ С�������˶����ƺ���
extern int pwmL,pwmR;
void c_stop(void){
	IN2=0;IN3=0;
	IN1=0;IN4=0;
	pwmL=0;pwmR=0;
}
void c_goStraight(void){
	IN2=1;IN3=1;
	IN1=0;IN4=0;
	pwmL=40;pwmR=40+R_FIX;//30
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
void c_turnLeftStop(void){ //左轮停止
	IN2=0;IN3=1;
	IN1=1;IN4=0;
	pwmL=25;pwmR=25+R_FIX;
}


void control(){
	if(trace4 == 0 &&trace3 == 0 &&trace2== 0 &&trace1 == 0 )//什么也没有
	{
		c_stop();
	}
	if(trace4 == 1 &&trace3 == 1 &&trace2== 1 &&trace1 == 1 )//四个传感器都感应到黑线
	{
		c_goStraight();
	}
	if(trace4 == 0 &&trace3 == 1 &&trace2== 1 &&trace1 == 0)//小车直行
	{
		 //c_turnLeftStop();//
		c_goStraight();
	}
	if(trace4 == 0 &&trace3 == 0 &&trace2== 1 &&trace1 == 0)//偏左，向右
	{
		c_turnRight();
		Delay(4);
		if(trace4 == 0 &&trace3 == 0 &&trace2== 0 &&trace1 == 0)
		{
			c_turnLeft();
			Delay(50);
		}
	}
	if(trace4 == 0 &&trace3 == 1 &&trace2== 0 &&trace1 == 0)//偏有，向左
	{
		c_turnLeft();
		Delay(4);
		if(trace4 == 0 &&trace3 == 0 &&trace2== 0 &&trace1 == 0)
		{
			c_turnRight();
			Delay(50);
		}
	}
	

	if((trace4 == 1 &&trace3 == 1 &&trace2== 1 &&trace1 == 0 )||(trace4 == 1 &&trace3 == 1 &&trace2== 0 &&trace1 == 0))//ֱ直角左转
	{
		c_goStraight();
		Delay(50);//
		if(trace4 == 0 &&trace3 == 0 &&trace2== 0 &&trace1 == 0 )//左转中
		{
			c_stop();
			Delay(200);
			c_turnLeftStop();
			while(!(trace4 == 0 &&trace3 == 1 &&trace2== 0 &&trace1 == 0||trace4 == 0 &&trace3 == 1 &&trace2== 1 &&trace1 == 0));
			//改动开始
			c_goStraight();
			Delay(300);//600
			IN2=1;IN3=0;
			IN1=0;IN4=0;
			pwmL=15;pwmR=0;
			Delay(400);//300
			//改动结束
		}
	}
	if(trace4 == 1 &&trace3 == 0 &&trace2== 0 &&trace1 == 0 )//大圆弧转弯向左
	{
		IN2=1;IN3=1;
		IN1=0;IN4=0;
		pwmL=10;pwmR=40+R_FIX;
	}
	if(trace4 == 0 &&trace3 == 0 &&trace2== 0 &&trace1 == 1 )//大圆弧转弯向右
	{
		IN2=1;IN3=1;
		IN1=0;IN4=0;
		pwmL=40;pwmR=10;
	}

}