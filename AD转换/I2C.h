#ifndef __I2C_H__
#define __I2C_H__
void I2C_Start(void);
void I2C_Stop(void);
void I2C_sendByte(unsigned char content);
unsigned char I2C_receiveByte(void);
void sendAck(unsigned char target);
unsigned char receiveAck(void)	;
#endif