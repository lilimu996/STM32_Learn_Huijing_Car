//���ӷ�ʽ ����ο�interface.h�ļ�
//����Դ����Դ����--����24Сʱ��ɾ��
//�������غ�BOOT0�����ұߣ�����λ���������
#include "stm32f10x.h"
#include "interface.h"
#include "LCD1602.h"
#include "IRCtrol.h"
#include "motor.h"
#include "UltrasonicCtrol.h"

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

unsigned char duoji_count=0;
unsigned char zhuanjiao = 11;

//��ʱ��������0.1ms 
//���PWM������20ms��0 - 180��ֱ��Ӧ 0.5 - 2.5ms ������
//����zhuanjiao�ɵ���ΧΪ 5 - 25 ��Ӧ 0 - 180�㣬��zhuanjiao = 15 ʱ��Ӧ90��
//Ϊ���ö�����и���ȷ���������һ�����ת�ǲ�Ҫʹ��0���180�㣬�������м俿��һ��
//��תʱѡ��zhuanjiao=7 ��תʱ��zhuanjiao=23
void DuojiMid()
{
	zhuanjiao = 15;
	Delayms(300);
}

void DuojiRight()
{
	zhuanjiao = 7;
	Delayms(300);
}

void DuojiLeft()
{
	zhuanjiao = 23;
	Delayms(300);
}

///��ȡ��������ľ���,����ǰ�������Ϊ��ǰ
void GetAllDistance(unsigned int *dis_left,unsigned int *dis_right,unsigned int *dis_direct)
{
	CarStop();
	GetDistanceDelay();
	*dis_direct = distance_cm;
	
	DuojiRight();
	Delayms(100);
	GetDistanceDelay();//��ȡ�ұ߾���
	*dis_right = distance_cm;
	
	DuojiMid();
	DuojiLeft();
	Delayms(100);
	GetDistanceDelay();//��ȡ��߾���
	*dis_left = distance_cm;
	
	DuojiMid();//��λ
}

void BarrierProc()
{
		if(distance_cm < 10)//ǰ�����ϰ���
	{
		unsigned int dis_left;//��߾���
		unsigned int dis_right;//�ұ߾���
		unsigned int dis_direct;//ǰ������
		if(distance_cm < 8)
		{
			CarBack();
			Delayms(400);
		}
		
		while(1)
		{
			GetAllDistance(&dis_left,&dis_right,&dis_direct);
			if(dis_direct < 5)
			{
				CarBack();
				Delayms(400);
				continue;
			}
			else if((dis_left < 5) || (dis_right < 5))
			{
				CarBack();
				Delayms(400);
				continue;
			}
			else if(dis_direct >= dis_left && dis_direct >= dis_right)//ǰ��������Զ
			{
				CarGo();
				Delayms(600);
				return;
			}
			else if(dis_left <= dis_right)//��ת
			{
				CarRight();
				Delayms(500);
			}
			else if(dis_right < dis_left)
			{
				CarLeft();
				Delayms(500);
			}
		}
	}
	else
	{
		CarGo();
	}
}

int main(void)
{
	delay_init();
	GPIOCLKInit();
	UserLEDInit();
	//LCD1602Init();
	//IRCtrolInit();
	TIM2_Init();
	MotorInit();
	UltraSoundInit();
	//RedRayInit();
	ServoInit();
	DuojiMid();
	Delayms(500);

 while(1)
 {	

	zhuanjiao = 16;
	 
	//DuojiMid();//��λ		
 }
}

