#include <REGX52.H>

unsigned char key_keynum = 0;


unsigned char key_getStatus(void){
	unsigned char key = 0;
	if(P3_1 == 0){key = 1;}
	if(P3_0 == 0){key = 2;}
	if(P3_2 == 0){key = 3;}
	if(P3_3 == 0){key = 4;}
	return key;
}

unsigned char key_return(void){
	unsigned char temp;
	temp = key_keynum ; 
	key_keynum = 0;
	return temp;
}

void key_loop(void){
	static unsigned char nowStatus,beforeStatus;
	//static int continueCount;
	beforeStatus = nowStatus ; 
	nowStatus = key_getStatus();
	if(beforeStatus == 1 &&nowStatus == 0){
		key_keynum =1;
	}
	if(beforeStatus == 2 &&nowStatus == 0){
		key_keynum =2;
	}
	if(beforeStatus == 3 &&nowStatus == 0){
		key_keynum =3;
	}
	if(beforeStatus == 4 &&nowStatus == 0){
		key_keynum =4;
	}

}