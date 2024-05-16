
#include <REG52.H>

/*     自定义变量类型    */
typedef unsigned char uchar;   //0~255
typedef unsigned int uint;     //0~65535

uchar Turn_angle;
sbit PWM = P2^3;  //信号线
uchar kk = 0;

//延迟1ms
void delay_ms(uint c)   //误差 0us
{
    uint a,b;
    for(;c>0;c--)
        for(b=102;b>0;b--)
            for(a=3;a>0;a--);
}

void Time0_Init()          //定时器初始化
{
        TMOD = 0x01;           //定时器0工作在方式1
        EA = 1;
        ET0 = 1;
        TH0  = 0xfe;
        TL0  = 0x33;                   //11.0592MZ晶振，0.5ms
        TR0=1;                 //定时器开始
}

void main()
{
    Time0_Init();
   //PWM = 0;

    while (1)
    {
        kk = 0;
        Turn_angle = 1; //归零   1--0 2--45 3--90 4--135 5--180
        delay_ms(100);
		
				 kk = 0;
		Turn_angle = 2; //归零   1--0 2--45 3--90 4--135 5--180
        delay_ms(100);
		
				 kk = 0;
		Turn_angle = 3; //归零   1--0 2--45 3--90 4--135 5--180
        delay_ms(100);
		
						 kk = 0;
		Turn_angle = 4; //归零   1--0 2--45 3--90 4--135 5--180
        delay_ms(100);

        kk = 0;
        Turn_angle = 5; //旋转
        delay_ms(100);
    }
}

void timer0() interrupt 1
{
    //TR0 = 0;  //关闭计时
    TH0  = 0xfe;
    TL0  = 0x33;                   //11.0592MZ晶振，0.5ms

    if(kk<=Turn_angle)   //1---0度  2---45度 3---90 4--- 135度  5---180度
    {
        PWM = 1;
    }
    else
    {
        PWM = 0;
    }
    if(kk==40)   //一个周期20ms
    {
        kk = 0;
    }
    kk ++;
    //TR0 = 1;  //开启计时
}

