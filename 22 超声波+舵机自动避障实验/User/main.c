//连接方式 ：请参考interface.h文件
//部份源码来源网络--请试用24小时后删除
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
	Delayms(500);
}

void DuojiRight()
{
	zhuanjiao = 25;
	Delayms(500);
}

void DuojiLeft()
{
	zhuanjiao = 6;
	Delayms(500);
}

///获取三个方向的距离,进来前舵机方向为向前
void GetAllDistance(unsigned int *dis_left,unsigned int *dis_right,unsigned int *dis_direct)
{
	CarStop();
	GetDistanceDelay();
	*dis_direct = distance_cm;
	
	
	DuojiMid();
	DuojiLeft();
	Delayms(200); //适当延长舵机归位时间，有助于超声波测距稳定性
	GetDistanceDelay();//获取左边距离
	*dis_left = distance_cm;
	
	DuojiMid();//归位
	
	DuojiRight();
	Delayms(200);
	GetDistanceDelay();//获取右边距离
	*dis_right = distance_cm;

	DuojiMid();//归位
	
}

void BarrierProc()
{
		if(distance_cm < 20)//前方有障碍物
	{
		unsigned int dis_left;//左边距离
		unsigned int dis_right;//右边距离
		unsigned int dis_direct;//前方距离
	if(distance_cm < 8) //前方障碍物距离小于5cm，小车执行后退一次
		{
			CarBack();
			Delayms(500);
		}
		
		if(distance_cm < 15) //正前方障碍物距离小于15厘米，执行右转一次
		{
			CarStop();
			Delayms(200);
			CarRight();
			Delayms(500);
		}
		
		while(1)
		{
			GetAllDistance(&dis_left,&dis_right,&dis_direct);
			if(dis_direct < 8)
			{
				CarBack();
				Delayms(500);
				CarRight();
			  Delayms(500);
				continue;
			}
			else if((dis_left < 8) || (dis_right < 8))
			{
				CarBack();
				Delayms(500);
				continue;
			}
			else if(dis_direct > 15 && dis_left > 15 && dis_right > 15)//前方距离最远
			{
				CarGo();
				Delayms(100);
				return;
			}
			
			else if(dis_left < dis_right)//右转
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
	 		if(tick_5ms >= 5)
		{
			tick_5ms = 0;

			Distance();//计算距离
			BarrierProc();

		}
		
 }
}
