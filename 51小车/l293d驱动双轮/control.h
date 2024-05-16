
sbit IN1=P1^4;
sbit IN2=P1^5;
sbit IN3=P1^3;
sbit IN4=P1^2;
sbit EN1=P1^7;
sbit EN2=P1^6;
//◊Ó”“ «trace1
sbit trace1  =P2^3;
sbit trace2  =P2^2;
sbit trace3  =P2^1;
sbit trace4  =P2^0;

void c_stop(void);
void c_goStraight(void);
void c_turnLeft(void);
void c_turnLeftStop(void);
void c_turnRight(void);
void c_turnRightStop(void);
void control(void);
void c_turnLeftFast(void);

void c_turnLeftSlow(void);
void c_turnRightSlow(void);

void c_backTest(void);



