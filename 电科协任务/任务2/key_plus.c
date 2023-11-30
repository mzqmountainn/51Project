#include <REGX52.H>
unsigned char key_keyNumber;
/**
  * @brief按键检测，之前要在按键按下后用Delay函数进行软件消抖，还要用while(P3_1==0)来判断是否松手，如果长期不松手，则CPU会	卡在该死循环里，不能执行其他代码
  * @param无
  * @retval返回被按下按键的值
  */
unsigned char Key_GetState()
{
	unsigned char keynum = 0;
	if(P3_1==0){keynum=1;}	//一有按键被按下，标志位keynum立即置位并返回，给key_loop函数处理
	if(P3_0==0){keynum=2;}
	if(P3_2==0){keynum=3;}
	if(P3_3==0){keynum=4;}
	return keynum;
}
/**
  * @brief用于返回按键标志位，main函数中调用
  * @param无
  * @retval按键标志位
  */
unsigned char key_return()
{
	unsigned char temp = 0;
	temp = key_keyNumber;
	key_keyNumber = 0;
	return temp;
}
/**
  * @brief每隔20毫秒执行一次该函数，对按键状态进行扫描
  * @param无
  * @retval无
  */
void key_loop()
{
	static unsigned char before_state,now_state;
	before_state = now_state;
	now_state = Key_GetState();		//获取按键标志位
    
    /*1.一开始没按键按下时before_state = 0,now_state = 0
      2.当按键1按下没松开时，now_state = 1,此时before_state = 0，不满足下面任何的判断
      3.20ms后该函数再次被调用，before_state = now_state = 1
      4.按键1松开，now_state = 0，此时before_state = 1，满足下面第一条if判断，key_keyNumber置1
    */
    
	//上一个状态有按键按下，现在状态没有按键按下，说明处于按下后松手阶段
    //若if(before_state == 0 && now_state == 1)，则是按键按下瞬间为真，标志位置1，不用等	
	if(before_state == 1 && now_state == 0)	
	{
		key_keyNumber = 1;	//全局变量key_keyNumber置1，使用key_return函数返回给main函数使用
	}
	if(before_state == 2 && now_state == 0)	
	{
		key_keyNumber = 2;
	}
	if(before_state == 3 && now_state == 0)	
	{
		key_keyNumber = 3;
	}
	if(before_state == 4 && now_state == 0)	
	{
		key_keyNumber = 4;
	}
}
