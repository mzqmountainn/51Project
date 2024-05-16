#include <REGX52.H>
#include "trace.h"
extern int pwmL,pwmR;
void controlMotor(void){
	if(trace1==0&&trace2==0&&trace3==0&&trace4==0)//四个传感器都未检测到黑线
	{ 
		pwmL =0;pwmR = 0;
	}
	if(trace1==0&&trace2==1&&trace3==1&&trace4==0)//正中黑线
		{ 
			pwmL =100 ;pwmR = 100;
		}
	if(trace1==0&&trace2==0&&trace3==1&&trace4==0)//偏右，向左矫正
		{ 
			pwmL =40 ;pwmR = 100;
		}
	if(trace1==0&&trace2==1&&trace3==0&&trace4==0)//偏左，向右矫正
		{ 
			pwmL =100 ;pwmR = 40;
		}
		
		

}