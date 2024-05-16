#include <REGX52.H>
#include "membraneKeyboard.h"
#include "LCD1602.h"
#include "Delay.h"

void main(){
	LCD_Init();
	while(1){
		char temp;
		if(temp=membraneKeyboardScan(),temp!='\0'){
			LCD_ShowChar(1,1,temp);
		}
		
		
	}
}
