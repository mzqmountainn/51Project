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

#define R_FIX 6 //右修正量（车一直向右偏）

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
//void c_turnLeftStop(void){
//	IN2=0;IN3=1;
//	IN1=1;IN4=0;
//	pwmL=60;pwmR=40+R_FIX;
//}
//void c_turnRightStop(void){
//	IN2=1;IN3=0;
//	IN1=0;IN4=1;
//	pwmL=40;pwmR=75+R_FIX;
//}
void c_turnLeftFast(void){
	IN2=1;IN3=1;
	IN1=0;IN4=0;
	pwmL=9;pwmR=20+R_FIX;
}


void c_turnLeftSlow(void){
	IN2=1;IN3=1;
	IN1=0;IN4=0;
	pwmL=9;pwmR=12+R_FIX;
}
void c_turnRightSlow(void){
	IN2=1;IN3=1;
	IN1=0;IN4=0;
	pwmL=15;pwmR=0+R_FIX;
}

void c_backTest(void){
	IN2=0;IN3=0;
	IN1=1;IN4=1;
	pwmL=50;pwmR=50+R_FIX;
}

void c_test(void){
	IN2=0;IN3=0;
	IN1=1;IN4=1;
	pwmL=100;pwmR=100;
}


void control(){
	c_test();

}