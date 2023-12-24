#include <REGX52.H>
void Timer0Init(void)		//1����@11.0592MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;
	TL0 = 0;		//���ö�ʱ��ֵ
	TH0 = 0;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 0;		//��ʱ��0����ʱ
}
void Timer0_setCounter(int value){
	TL0 = value%256;
	TH0 = value/256;
}
void Timer0_run(unsigned char flag){
	TR0 = flag;
}
unsigned int Timer0_getCounter(void){
	return (TH0<<8)|TL0;
}