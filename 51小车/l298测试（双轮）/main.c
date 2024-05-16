#include <REGX52.H>



sbit ENA = P1^0;
sbit IN1 = P1^1;
sbit IN2 = P1^2;
sbit IN3 = P1^4;
sbit IN4 = P1^5;
sbit ENB = P1^6;



int main(void){
	P1 = 0x00;
	IN1=1;IN3=1;
	ENA=1;ENB=1;
	return 0 ;
}