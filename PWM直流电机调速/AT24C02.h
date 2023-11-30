#ifndef __AT24C02_H__
#define __AT24C02_H__

//用户调用函数：
void AT24C02_sendByte(unsigned char address,content);
unsigned char AT24C02_receiveByte(unsigned char address);
#endif
