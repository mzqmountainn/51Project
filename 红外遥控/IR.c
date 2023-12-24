#include <REGX52.H>
#include <Init0.h>
#include <Timer0.h>
//#include <LCD1602.h>

void IR_init(void){
	Timer0Init();
	Int0_Init();
}
typedef enum{true =1,false =0} bool;

bool IR_repeatFlag =0;
bool IR_dataFlag =0;
char IR_state =0;
unsigned int IR_time;
unsigned char IR_data[4];
unsigned char IR_Pdata=0;
unsigned char IR_address;
unsigned char IR_command;


unsigned char IR_getDataFlag(void){
	if( IR_dataFlag){
		 IR_dataFlag =0;
		return 1;
	}
	return 0;
}
unsigned char IR_getRepeatFlag(void){
	if( IR_repeatFlag){
		 IR_repeatFlag =0;
		return 1;
	}
	return 0;
}
unsigned char IR_getAddress(void){
	return IR_address;
}
unsigned char IR_getCommand(void){
	return IR_command;
}




void Int0_Routine(void) interrupt 0
{
	//P2_1 = ~P2_1;
	if(IR_state == 0){  //¼ì²âµ½ÏÂ½µÑØ
		Timer0_setCounter(0);
		Timer0_run(1);
		IR_state = 1;
	} 
	else if(IR_state == 1){
		IR_time =Timer0_getCounter();
		Timer0_setCounter(0);
		//LCD_ShowNum(2,1,IR_time,5);
		if(IR_time>=12442-500 && IR_time<= 12442+500){
						//P2=0;//////////
			IR_state = 2;
		}else if(IR_time>=10368-500 && IR_time<= 10368+500){
			IR_repeatFlag =1;
			Timer0_run(0);
			IR_state =0;
		}else{
			IR_state =1;
		}
	}
	else if(IR_state == 2){
		IR_time =Timer0_getCounter();
		Timer0_setCounter(0);
		if(IR_time>=1032-600 && IR_time<= 1032+600){
			IR_data[IR_Pdata/8] &= ~(0x01<<(IR_Pdata%8));
			IR_Pdata++;
		}
		else if(IR_time>=2074-600 && IR_time<= 2074+600){
			IR_data[IR_Pdata/8] |= (0x01<<(IR_Pdata%8));
			IR_Pdata++;
		}else{
			IR_Pdata =0;
			IR_state =1;
		}

		if(IR_Pdata>=32){
			IR_Pdata =0;
			if(IR_data[0] == ~(IR_data[1]) &&IR_data[2] == ~(IR_data[3])){
				IR_dataFlag =1;
				IR_address = IR_data[0];
				IR_command = IR_data[2];
			}
			Timer0_run(0);
			IR_state =0;
		}
	}
}













