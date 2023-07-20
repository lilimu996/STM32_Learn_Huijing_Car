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
char front_left_speed_duty=SPEED_DUTY;
char front_right_speed_duty=SPEED_DUTY;
char behind_left_speed_duty=SPEED_DUTY;
char behind_right_speed_duty=SPEED_DUTY;

unsigned char tick_5ms = 0;//5ms����������Ϊ�������Ļ�������
unsigned char tick_1ms = 0;//1ms����������Ϊ����Ļ���������
unsigned char tick_200ms = 0;//ˢ����ʾ

char ctrl_comm = COMM_STOP;//����ָ��
char ctrl_comm_last = COMM_STOP;//��һ�ε�ָ��
unsigned char continue_time=0;
unsigned char bt_rec_flag=0;//�������Ʊ�־λ
//   �����ߴ�������������������ǰ����������������
//IN1=1 ���
//IN2=1 ��ǰ
//IN3=1 �Һ�
//IN4=1 ��ǰ
void VoidRun2(void)  //����ʱ���ˣ�û������ʱǰ��
{
	//L��߼�⵽����
	if(VOID_L_IO == BARRIER_Y)//ǰ��������0
	{
	  LED_RESET;//���� �͵�ƽ	
		//IN1  �ߵ�ƽ�����
		//IN2  �͵�ƽ
		//IN1=1 IN2=0 ����˺���	
    FRONT_RIGHT_F_RESET;  //IN1 �ߵ�ƽ
		FRONT_RIGHT_B_SET;    //IN2 �͵�ƽ

	}
	
	if(VOID_L_IO == BARRIER_N)//ǰ��������1
	{
		LED_SET; //�ص� �ߵ�ƽ
		
   //IN1  �͵�ƽ
   //IN2  �ߵ�ƽǰ��
	//IN1=0 IN2=1 ��ǰ������
		
	 FRONT_RIGHT_F_SET;  //IN1 �͵�ƽ
	 FRONT_RIGHT_B_RESET; //IN2 �ߵ�ƽ
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
//		VoidRun2();
	 //LED_RESET;//���� �͵�ƽ
	 //LED_SET; //�ص� �ߵ�ƽ
	 	 BEHIND_RIGHT_EN; 
	 //BEHIND_LEFT_GO; //��ǰ������
	 //BEHIND_LEFT_BACK; //ǰ���˺���
	 //FRONT_RIGHT_GO;  //��ǰ������������ע�ͣ�//�Һ��˺���
	 //FRONT_RIGHT_BACK; //�Һ��˺���������ע�ͣ�//��ǰ������
 }
		
}


