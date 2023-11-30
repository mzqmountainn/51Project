#include <REGX52.H>
typedef enum{false = 0,true =1} bool;
void Delay(unsigned int x)		//@12.000MHz
{
	unsigned char i, j;
	while(x){
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
		x--;
	}

}

int main(void){
	int gap;
	int LEDnum;
	bool direction = 1;//0=left 1=right
	while(1){
		P2=0xAA;
		gap = 1;
		LEDnum = 0;
		while(1){
			if(P3_1 == 0){
				Delay(20);
				while(P3_1==0)	;
				Delay(20);
				P2=0xFE;
			}
			if(P3_3 == 0){ //¸´Î»
				Delay(20);
				while(P3_3==0)	;
				Delay(20);
				break;
			}
			if(P3_2 ==0){
				Delay(20);
				while(P3_2==0)	;
				Delay(20);
				gap++;
				if(gap == 4){
					gap =1;
					LEDnum=0;
					direction = !direction;
					if(direction)
						P2=0xFE;
					else
						P2=0x7f;
				}
			}
			if(P3_0==0){
				Delay(20);
				while(P3_0==0)	;
				Delay(20);
				LEDnum +=gap;
					if(LEDnum >=8)
						LEDnum-=8;
				if(direction)
					P2 = ~(0x01<<LEDnum);
				else
					P2 = ~(0x80>>LEDnum);
				
			}
			
		}
	}
}