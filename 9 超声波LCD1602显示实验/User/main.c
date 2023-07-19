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

void BarrierProc(void)
{
	if((distance_cm < 15 && distance_cm > 10) || distance_cm > 25) 
	{
		ctrl_comm = COMM_STOP;//防震荡
		return;
	}
	
	if(distance_cm <= 10) ctrl_comm = COMM_DOWN;
	
	if(distance_cm >= 15) ctrl_comm = COMM_UP;
}

int main(void)
{
	delay_init();
	GPIOCLKInit();
	UserLEDInit();
	LCD1602Init();
	IRCtrolInit();
	TIM2_Init();
	MotorInit();
	UltraSoundInit();
	ServoInit();

 while(1)
 {	 
				  LCD1602WriteDistance(distance_cm);//更新距离
					Distance();//计算距离
	 				LCD1602WriteCommand(ctrl_comm);
 }
}

