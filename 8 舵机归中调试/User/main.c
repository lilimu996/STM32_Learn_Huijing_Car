//连接方式 ：请参考interface.h文件
//部分源码来源网络--测试24小时后删除
//串口下载后，BOOT0跳到右边，按复位后程序运行
#include "stm32f10x.h"
#include "interface.h"
#include "LCD1602.h"
#include "IRCtrol.h"
#include "motor.h"
#include "UltrasonicCtrol.h"

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

///获取三个方向的距离,进来前舵机方向为向前
void GetAllDistance(unsigned int *dis_left,unsigned int *dis_right,unsigned int *dis_direct)
{
	CarStop();
	GetDistanceDelay();
	*dis_direct = distance_cm;
	
	DuojiRight();
	Delayms(100);
	GetDistanceDelay();//获取右边距离
	*dis_right = distance_cm;
	
	DuojiMid();
	DuojiLeft();
	Delayms(100);
	GetDistanceDelay();//获取左边距离
	*dis_left = distance_cm;
	
	DuojiMid();//归位
}

void BarrierProc()
{
		if(distance_cm < 10)//前方有障碍物
	{
		unsigned int dis_left;//左边距离
		unsigned int dis_right;//右边距离
		unsigned int dis_direct;//前方距离
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
			else if(dis_direct >= dis_left && dis_direct >= dis_right)//前方距离最远
			{
				CarGo();
				Delayms(600);
				return;
			}
			else if(dis_left <= dis_right)//右转
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
	 
	//DuojiMid();//归位		
 }
}

