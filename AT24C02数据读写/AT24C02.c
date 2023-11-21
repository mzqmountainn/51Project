#include <REGX52.H>
#include "I2C.h"

#define AT24C02_address 0xA0


void AT24C02_sendByte(unsigned char address,content){
	I2C_Start();
	I2C_sendByte(AT24C02_address);
	receiveAck();
	I2C_sendByte(address);
	receiveAck();
	I2C_sendByte(content);
	receiveAck();
	I2C_Stop();
}

unsigned char AT24C02_receiveByte(unsigned char address){
	unsigned char target;
	I2C_Start();
	I2C_sendByte(AT24C02_address);
	receiveAck();
	I2C_sendByte(address);
	receiveAck();
	I2C_Start();
	I2C_sendByte(AT24C02_address|0x01);
	receiveAck();
	target = I2C_receiveByte();
	sendAck(1);
	I2C_Stop();
	return target;
	
	
}