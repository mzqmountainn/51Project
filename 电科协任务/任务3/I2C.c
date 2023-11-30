#include <REGX52.H>
#include "Delay.h"

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;
void I2C_Start(void){
	I2C_SCL = 1;
	I2C_SDA = 1;
	I2C_SDA = 0;
	I2C_SCL = 0;
}
void I2C_Stop(void){
	I2C_SDA = 0;
	I2C_SCL = 1;
	I2C_SDA = 1;
	
}
void I2C_sendByte(unsigned char content){
	int i;
	I2C_SCL = 0;
	for (i = 0; i <8; i++){
		I2C_SDA = content&(0x80>>i);
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
}
unsigned char I2C_receiveByte(void){
	int  i ;
	unsigned char target;
	I2C_SDA= 1;
	for(i = 0;i<8;i++){
		I2C_SCL = 1;
		if(I2C_SDA){target|=(0x80>>i);}
		I2C_SCL = 0;
	}
	return  target;
	
}
void sendAck(unsigned char target){
	I2C_SDA = target;
	I2C_SCL = 1;
	I2C_SCL = 0;
}
unsigned char receiveAck(void){
	unsigned char target;
	I2C_SDA = 1;
	I2C_SCL = 1;
	target = I2C_SDA;
	I2C_SCL= 0;
	return target;
}











