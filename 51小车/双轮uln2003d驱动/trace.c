#include <REGX52.H>
#include "trace.h"
extern int pwmL,pwmR;
void controlMotor(void){
	if(trace1==0&&trace2==0&&trace3==0&&trace4==0)//�ĸ���������δ��⵽����
	{ 
		pwmL =0;pwmR = 0;
	}
	if(trace1==0&&trace2==1&&trace3==1&&trace4==0)//���к���
		{ 
			pwmL =100 ;pwmR = 100;
		}
	if(trace1==0&&trace2==0&&trace3==1&&trace4==0)//ƫ�ң��������
		{ 
			pwmL =40 ;pwmR = 100;
		}
	if(trace1==0&&trace2==1&&trace3==0&&trace4==0)//ƫ�����ҽ���
		{ 
			pwmL =100 ;pwmR = 40;
		}
		
		

}