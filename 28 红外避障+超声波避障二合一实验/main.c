//���ӷ�ʽ ����ο�interface.h�ļ�
//����Դ����Դ����--������24Сʱ��ɾ��
#include "stm32f10x.h"
#include "interface.h"
#include "LCD1602.h"
#include "IRCtrol.h"
#include "motor.h"
#include "UltrasonicCtrol.h"
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
}


///��ȡ����,�������ֶ������״̬
void GetAllDistance(unsigned int *dis_direct)
{
	
	
	GetDistanceDelay();
	*dis_direct = distance_cm;
	
	
}

void BarrierProc()
{
		if(distance_cm < 100)//ǰ�����ϰ���
	{
		
		unsigned int dis_direct;//ǰ������
		
		
		while(1)
		{
			GetAllDistance(&dis_direct);
	    GetVoidStatus();
			
			/*if(GetVoidStatus()==1)
				{
					CarStop();
					Delayms(5000);
				}*/
			
			if(GetVoidStatus()==1&&distance_cm < 30&&distance_cm >3) //������ϰ�����ǰ�����ϰ�������Ȼ����ת
				{
				CarBack();
				Delayms(500);
				CarLeft();
				Delayms(500);	
				}
				
				else
					if(GetVoidStatus()==3&&distance_cm < 30) //�������ϰ������ǰ�����ϰ������Ȼ����ת
				{
				CarBack();
				Delayms(1500);
				CarLeft();
				Delayms(500);	
				}
				else
			if(distance_cm < 10&&distance_cm >3)  //ǰ�����ϰ��������ת
			{
				
				CarBack();
				Delayms(500);
				CarRight();
				Delayms(300);
				return;
			}
		
			else 
			{
				VoidRun();
			}
			
		
		}
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
	RedRayInit();
	ServoInit();
	
	DuojiMid();
	Delayms(500);

 while(1)
 {	 
	 		if(tick_5ms >= 5)
		{
			tick_5ms = 0;
			Distance();//�������
			BarrierProc();

		}
		
 }
}

