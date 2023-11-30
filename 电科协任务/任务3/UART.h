#ifndef __UART_H__
#define __UART_H__

void UART_Init();
void UART_SendByte(unsigned char Byte);
bit ReceiveString();
void PutString(unsigned char *TXStr) ;
#endif
