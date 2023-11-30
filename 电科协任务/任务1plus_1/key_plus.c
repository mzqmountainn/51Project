#include <REGX52.H>
unsigned char key_keyNumber;
/**
  * @brief������⣬֮ǰҪ�ڰ������º���Delay�������������������Ҫ��while(P3_1==0)���ж��Ƿ����֣�������ڲ����֣���CPU��	���ڸ���ѭ�������ִ����������
  * @param��
  * @retval���ر����°�����ֵ
  */
unsigned char Key_GetState()
{
	unsigned char keynum = 0;
	if(P3_1==0){keynum=1;}	//һ�а��������£���־λkeynum������λ�����أ���key_loop��������
	if(P3_0==0){keynum=2;}
	if(P3_2==0){keynum=3;}
	if(P3_3==0){keynum=4;}
	return keynum;
}
/**
  * @brief���ڷ��ذ�����־λ��main�����е���
  * @param��
  * @retval������־λ
  */
unsigned char key_return()
{
	unsigned char temp = 0;
	temp = key_keyNumber;
	key_keyNumber = 0;
	return temp;
}
/**
  * @briefÿ��20����ִ��һ�θú������԰���״̬����ɨ��
  * @param��
  * @retval��
  */
void key_loop()
{
	static unsigned char before_state,now_state;
	before_state = now_state;
	now_state = Key_GetState();		//��ȡ������־λ
    
    /*1.һ��ʼû��������ʱbefore_state = 0,now_state = 0
      2.������1����û�ɿ�ʱ��now_state = 1,��ʱbefore_state = 0�������������κε��ж�
      3.20ms��ú����ٴα����ã�before_state = now_state = 1
      4.����1�ɿ���now_state = 0����ʱbefore_state = 1�����������һ��if�жϣ�key_keyNumber��1
    */
    
	//��һ��״̬�а������£�����״̬û�а������£�˵�����ڰ��º����ֽ׶�
    //��if(before_state == 0 && now_state == 1)�����ǰ�������˲��Ϊ�棬��־λ��1�����õ�	
	if(before_state == 1 && now_state == 0)	
	{
		key_keyNumber = 1;	//ȫ�ֱ���key_keyNumber��1��ʹ��key_return�������ظ�main����ʹ��
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
