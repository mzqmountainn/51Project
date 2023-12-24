#include <REGX52.H>
#include <Delay.h>
#include <LCD1602.h>
#include <Init0.h>
#include <Timer0.h>
#include <IR.h>

unsigned int count =0;
unsigned char address;
unsigned char command;

void main(){
	IR_init();
	LCD_Init();

	while(1){
		if(IR_getDataFlag()||IR_getRepeatFlag()){
			address=IR_getAddress();
			command=IR_getCommand();
			LCD_ShowHexNum(2,1,address,2);
			LCD_ShowHexNum(2,4,command,2);
			LCD_ShowNum(2,7,count,3);
			if(command == IR_VOL_MINUS)
				count--;
			if(command == IR_VOL_ADD)
				count++;
		}
		//LCD_ShowNum(2,1,time,5);
		
	}
}

