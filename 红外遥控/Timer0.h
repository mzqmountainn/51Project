#ifndef __TIMER0_H__
#define __TIMER0_H__
void Timer0Init(void);
void Timer0_setCounter(int value);
void Timer0_run(unsigned char flag);
unsigned int Timer0_getCounter(void);

#endif