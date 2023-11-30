#include <REGX52.H>
extern unsigned char rawChar[10];
/**
  * @brief  串口初始化，4800bps@12.000MHz
  * @param  无
  * @retval 无
  */





void UART_Init(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA=1;
	ES=1;
}



/**
  * @brief  串口发送一个字节数据
  * @param  Byte 要发送的一个字节数据
  * @retval 无
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}
void PutString(unsigned char *TXStr)  
 {                
     ES=0;     
      while(*TXStr!=0) 
     {                      
         SBUF=*TXStr;
         while(TI==0);
         TI=0;    
         TXStr++;
     }
     ES=1; 
 }   
bit ReceiveString()    
  {
      char * RecStr=rawChar;
      char num=0;
      unsigned char count=0;
      loop:    
      *RecStr=SBUF;
      count=0;
      RI=0;    
      if(num<10)  //数据包长度为15个字符,尝试连续接收15个字符
      {
          num++;
          RecStr++;    
          while(!RI)
          {
              count++;
              if(count>140)return 0;    //接收数据等待延迟，等待时间太久会导致CPU运算闲置，太短会出现"数据包被分割",默认count=130
          }
          goto loop;
      }
      return 1;
  }

/*串口中断函数模板
void UART_Routine() interrupt 4
{
	if(RI==1)
	{
		
		RI=0;
	}
}
*/
