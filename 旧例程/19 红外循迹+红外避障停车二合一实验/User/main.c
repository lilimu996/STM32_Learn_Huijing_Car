//���ӷ�ʽ ����ο�interface.h�ļ�
//����Դ����Դ����--������24Сʱ��ɾ��
#include "stm32f10x.h"
#include "interface.h"
#include "LCD1602.h"
#include "IRCtrol.h"
#include "motor.h"
#include "uart.h"
#include "redvoid.h"

//ȫ�ֱ�������
unsigned int speed_count=0;//ռ�ձȼ����� 50��һ����
//char front_left_speed_duty=SPEED_DUTY;
char front_right_speed_duty=SPEED_DUTY;
char behind_left_speed_duty=SPEED_DUTY;
//char behind_right_speed_duty=SPEED_DUTY;

unsigned char tick_5ms = 0;//5ms����������Ϊ�������Ļ�������
unsigned char tick_1ms = 0;//1ms����������Ϊ����Ļ���������
unsigned char tick_200ms = 0;//ˢ����ʾ

char ctrl_comm = COMM_STOP;//����ָ��
char ctrl_comm_last = COMM_STOP;//��һ�ε�ָ��
unsigned char continue_time=0;
unsigned char bt_rec_flag=0;//�������Ʊ�־λ

//ѭ����ͨ���ж��������Թܵ�״̬������С���˶�
void SearchRun(void)
{

	if(SEARCH_L_IO == 1 && SEARCH_M_IO == 1 && SEARCH_R_IO == 1)  //��·����⵽ //����
	{
		CarStop();  //С��ֹͣ������С�������������ȵ���
	}
	
	if(SEARCH_L_IO == 0 && SEARCH_M_IO == 0 && SEARCH_R_IO == 1) //�ұߺ��ߣ�˵��С��ƫ����Ҫ������ת����
	{
		CarRight();  //С����ת
	}
	if(SEARCH_L_IO == 1 && SEARCH_M_IO == 0 && SEARCH_R_IO == 0)//��ߺ��ߣ�˵��С��ƫ�ң���Ҫ������ת����
	{
		CarLeft();  //С����ת
	}
	else if(SEARCH_L_IO == 0 && SEARCH_M_IO == 1 && SEARCH_R_IO == 0)//�м���ߣ�����С��ǰ������
	{
		CarGo();  //ͣС��ǰ��
	}
	
	if((VOID_R_IO == 0) && (VOID_L_IO == 0)) //��ߺ��ұ�����������ϴ�����ͬʱ��⵽�ϰ���
	{
  	CarStop();   //С��ֹͣ3���������ѭ�����������ȡ���ϰ���
	  Delayms(3000);
		CarBack();   //С������100���룬��ֹ��������ѭ��������ͬʱ��Ӧ������ʱ���Ӳ��ߵ�����
		Delayms(100);  //����ʱ�䲻��̫������ֹС������ʱ��������ܵ�
	}
	
}


int main(void)
{
	delay_init();
	GPIOCLKInit();
	UserLEDInit();
	LCD1602Init();
	//IRCtrolInit();
	TIM2_Init();
	MotorInit();
	ServoInit();
	
	RedRayInit();
	//USART3Conf(9600);

 while(1)
 {	 
	 		if(tick_5ms >= 5)
		{
			tick_5ms = 0;
			tick_200ms++;
			if(tick_200ms >= 40)
			{
				tick_200ms = 0;
				LEDToggle(LED_PIN);
			}
			//VoidRun();
			SearchRun();
			if(ctrl_comm_last != ctrl_comm)//ָ����仯
			{
				ctrl_comm_last = ctrl_comm;
				switch(ctrl_comm)
				{
					case COMM_UP:    CarGo();break;
					case COMM_DOWN:  CarBack();break;
					case COMM_LEFT:  CarLeft();break;
					case COMM_RIGHT: CarRight();break;
					case COMM_STOP:  CarStop();break;
					default : break;
				}
				Delayms(10);//����
				LCD1602WriteCommand(ctrl_comm);
			}
			
		}
		
 }
}

