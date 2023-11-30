bit ReceiveString()    
  {
      char * RecStr=RecvString_buf;
      char num=0;
      unsigned char count=0;
      loop:    
      *RecStr=SBUF;
      count=0;
      RI=0;    
      if(num<14)  //数据包长度为15个字符,尝试连续接收15个字符
      {
          num++;
          RecStr++;    
          while(!RI)
          {
              count++;
              if(count>130)return 0;    //接收数据等待延迟，等待时间太久会导致CPU运算闲置，太短会出现"数据包被分割",默认count=130
          }
          goto loop;
      }
      return 0;
  }
  void USART() interrupt 4   //标志位TI和RI需要手动复位，TI和RI置位共用一个中断入口
 {
     if(ReceiveString())    
     {
         //数据包长度正确则执行以下代码
         Deal_UART_RecData();   
     }
     else
     {
         //数据包长度错误则执行以下代码
         //LED1=~LED1;                
     }
     RI=0;  //接收并处理一次数据后把接收中断标志清除一下，拒绝响应在中断接收忙的时候发来的请求
 }