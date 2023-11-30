#include <REGX52.H>
#include "Delay.h"

unsigned int key(void){
	int keyNum = 0;
	if(P3_1 == 0){Delay(20);while(P3_1 == 0);Delay(20);keyNum = 1;}
	if(P3_0 == 0){Delay(20);while(P3_0 == 0);Delay(20);keyNum = 2;}
	if(P3_2 == 0){Delay(20);while(P3_2 == 0);Delay(20);keyNum = 3;}
	if(P3_3 == 0){Delay(20);while(P3_3 == 0);Delay(20);keyNum = 4;}
	return keyNum;
}