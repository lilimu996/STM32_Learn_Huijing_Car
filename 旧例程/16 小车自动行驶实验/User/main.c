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
//IN1=1 ���
//IN2=1 ��ǰ
//IN3=1 �Һ�
//IN4=1 ��ǰ

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
//	 CarGo();
//	 Delayms(1000);
//	 CarBack();
//	 Delayms(1000);
//	 CarLeft();
//	 Delayms(1000);
//	 CarRight();
//	 Delayms(1000);
//	 CarStop();
	 Delayms(9999);
 }
		
}


