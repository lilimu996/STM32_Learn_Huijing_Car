//连接方式 ：请参考interface.h文件
//部份源码来源网络--请试用24小时后删除
#include "stm32f10x.h"
#include "interface.h"
#include "LCD1602.h"
#include "IRCtrol.h"
#include "motor.h"
#include "UltrasonicCtrol.h"
#include "redvoid.h"

//全局变量定义
unsigned int speed_count=0;//占空比计数器 50次一周期
char front_left_speed_duty=SPEED_DUTY;
char front_right_speed_duty=SPEED_DUTY;
char behind_left_speed_duty=SPEED_DUTY;
char behind_right_speed_duty=SPEED_DUTY;

unsigned char tick_5ms = 0;//5ms计数器，作为主函数的基本周期
unsigned char tick_1ms = 0;//1ms计数器，作为电机的基本计数器
unsigned char tick_200ms = 0;//刷新显示

char ctrl_comm = COMM_STOP;//控制指令
char ctrl_comm_last = COMM_STOP;//上一次的指令
unsigned char continue_time=0;

unsigned char duoji_count=0;
unsigned char zhuanjiao = 11;

//定时器周期是0.1ms 
//舵机PWM周期是20ms，0 - 180°分别对应 0.5 - 2.5ms 的脉宽
//变量zhuanjiao可调范围为 5 - 25 对应 0 - 180°，当zhuanjiao = 15 时对应90°
//为了让舵机运行更精确，建议向右或向左转是不要使用0°或180°，建议向中间靠近一点
//右转时选用zhuanjiao=7 左转时用zhuanjiao=23
void DuojiMid()
{
	zhuanjiao = 15;
}


///获取距离,开机保持舵机归中状态
void GetAllDistance(unsigned int *dis_direct)
{
	
	
	GetDistanceDelay();
	*dis_direct = distance_cm;
	
	
}

void BarrierProc()
{
		if(distance_cm < 100)//前方有障碍物
	{
		
		unsigned int dis_direct;//前方距离
		
		
		while(1)
		{
			GetAllDistance(&dis_direct);
	    GetVoidStatus();
			
			/*if(GetVoidStatus()==1)
				{
					CarStop();
					Delayms(5000);
				}*/
			
			if(GetVoidStatus()==1&&distance_cm < 30&&distance_cm >3) //左边有障碍物且前方有障碍，后退然后右转
				{
				CarBack();
				Delayms(500);
				CarLeft();
				Delayms(500);	
				}
				
				else
					if(GetVoidStatus()==3&&distance_cm < 30) //两边有障碍物，并且前方有障碍物，后退然后右转
				{
				CarBack();
				Delayms(1500);
				CarLeft();
				Delayms(500);	
				}
				else
			if(distance_cm < 10&&distance_cm >3)  //前方有障碍物后退左转
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
			Distance();//计算距离
			BarrierProc();

		}
		
 }
}

