/*#include <REGX52.H>
#include <Timer0.h>
#include <Delay.h>
#include <LCD1602.h>
#include <intrins.h>

sbit Trig=P2^2;   	 //���ƶ� 
sbit Echo=P2^1; 	 //���ն�

unsigned int receiveTime,realTime;
unsigned int length=0;
void main(void){
	Timer0Init();
	LCD_Init();
	Timer0_setCounter(0);
	while(1){
		Trig=0;
		Echo=0;
		Timer0_run(1);
		LCD_ShowString(1,1,"nmsl");
		
		Trig=1;
		Delay10us();
		_nop_();
		//while(!Echo);
		Timer0_setCounter(0);
		Trig=0;

		while(Echo);
		receiveTime = Timer0_getCounter();
		
		realTime = (unsigned int)(receiveTime*0.916);
		length = (unsigned int)(realTime*0.017);
		
		LCD_ShowNum(2,9,realTime,5);//
		LCD_ShowNum(2,1,length,5);
		LCD_ShowString(2,6,"cm");
		Timer0_run(0);
		//Delay(1000);
	}
}*/
#include <intrins.h>
#include <REGX52.H>
#include <Delay.h>
#include <LCD1602.h>
sbit Trig=P2^2;   	 //���ƶ� 
sbit Echo=P2^1; 	 //���ն�

 //΢�뼶��ʱ��������ʱt΢�룬ע��Ҫ����ͷ�ļ���intrins.h��
void delay_us(unsigned char t)
{
	while(t--)
	{
				_nop_();
	}
}

void HC_SR04_Init(void) //�õ���T0��ʱ��
{
		TMOD &= 0xf1; //��T0����Ϊ16λ�Ķ�ʱ����ģʽ
}
float getDistance(void) //��ȡһ�ξ���ֵ
{
		unsigned int n; 
		Trig = 1;
		TH0 = TL0 = 0;
		delay_us(10);
		Trig = 0; //10us���ϵĸߵ�ƽ����
		while(!Echo); //�ȴ����أ����EchoΪ�߾�Ҫ��ʼ��ʱ��
		TR0 = 1;  //������ʱ��
		while(Echo) ; //�ȴ�����ĸߵ�ƽ����
		TR0 = 0; //�ص���ʱ��
		n = (TH0)*256+TL0; //�����������ֵ
//		sendOneByte(TH0); //���ڴ��ڵ��ԣ��ɺ���s
//		sendOneByte(' ');
//		sendOneByte(TL0);
		return 22.1*n/10000; //��λcm
}
void main(void){
	HC_SR04_Init();
	LCD_Init();
	while(1){
		LCD_ShowNum(2,1,(unsigned int)getDistance(),5);
		Delay(100);
	}
}
