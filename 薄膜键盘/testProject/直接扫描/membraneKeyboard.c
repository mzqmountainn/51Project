#include <REGX52.H>
#include "Delay.h"

#define membraneKeyboardIO P1

sbit membraneKeyboardRow1= membraneKeyboardIO^0;
sbit membraneKeyboardRow2= membraneKeyboardIO^1;
sbit membraneKeyboardRow3= membraneKeyboardIO^2;
sbit membraneKeyboardRow4= membraneKeyboardIO^3;
sbit membraneKeyboardCol1= membraneKeyboardIO^4;
sbit membraneKeyboardCol2= membraneKeyboardIO^5;
sbit membraneKeyboardCol3= membraneKeyboardIO^6;
sbit membraneKeyboardCol4= membraneKeyboardIO^7;

char membraneKeyboardLibrary[] = {'\0','1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};


char membraneKeyboardScan(){
	unsigned int num = 0;
	membraneKeyboardIO = 0xFF;
	membraneKeyboardRow1 = 0;
	if(membraneKeyboardCol1 == 0){Delay(20);while(membraneKeyboardCol1 == 0);Delay(20);num = 1;}
	if(membraneKeyboardCol2 == 0){Delay(20);while(membraneKeyboardCol2 == 0);Delay(20);num = 2;}
	if(membraneKeyboardCol3 == 0){Delay(20);while(membraneKeyboardCol3 == 0);Delay(20);num = 3;}
	if(membraneKeyboardCol4 == 0){Delay(20);while(membraneKeyboardCol4 == 0);Delay(20);num = 4;}
	
	membraneKeyboardIO = 0xFF;
	membraneKeyboardRow2 = 0;
	if(membraneKeyboardCol1 == 0){Delay(20);while(membraneKeyboardCol1 == 0);Delay(20);num = 5;}
	if(membraneKeyboardCol2 == 0){Delay(20);while(membraneKeyboardCol2 == 0);Delay(20);num = 6;}
	if(membraneKeyboardCol3 == 0){Delay(20);while(membraneKeyboardCol3 == 0);Delay(20);num = 7;}
	if(membraneKeyboardCol4 == 0){Delay(20);while(membraneKeyboardCol4 == 0);Delay(20);num = 8;}
	
	membraneKeyboardIO = 0xFF;
	membraneKeyboardRow3 = 0;
	if(membraneKeyboardCol1 == 0){Delay(20);while(membraneKeyboardCol1 == 0);Delay(20);num = 9;}
	if(membraneKeyboardCol2 == 0){Delay(20);while(membraneKeyboardCol2 == 0);Delay(20);num = 10;}
	if(membraneKeyboardCol3 == 0){Delay(20);while(membraneKeyboardCol3 == 0);Delay(20);num = 11;}
	if(membraneKeyboardCol4 == 0){Delay(20);while(membraneKeyboardCol4 == 0);Delay(20);num = 12;}
	
	membraneKeyboardIO = 0xFF;
	membraneKeyboardRow4 = 0;
	if(membraneKeyboardCol1 == 0){Delay(20);while(membraneKeyboardCol1 == 0);Delay(20);num = 13;}
	if(membraneKeyboardCol2 == 0){Delay(20);while(membraneKeyboardCol2 == 0);Delay(20);num = 14;}
	if(membraneKeyboardCol3 == 0){Delay(20);while(membraneKeyboardCol3 == 0);Delay(20);num = 15;}
	if(membraneKeyboardCol4 == 0){Delay(20);while(membraneKeyboardCol4 == 0);Delay(20);num = 16;}
	return membraneKeyboardLibrary[num];
}





















