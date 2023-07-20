//连接方式 ：请参考interface.h文件
//部份源码来源网络--请试用24小时后删除
#include "stm32f10x.h"
#include "interface.h"
#include "LCD1602.h"
#include "IRCtrol.h"
#include "motor.h"
#include "uart.h"
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
unsigned char bt_rec_flag=0;//蓝牙控制标志位
//   检测左边传感器函数，有物体电机前进，无物体电机后退
//IN1=1 左后
//IN2=1 左前
//IN3=1 右后
//IN4=1 右前
void VoidRun2(void)  //有物时后退，没有物体时前进
{
	//L左边检测到物体
	if(VOID_L_IO == BARRIER_Y)//前方有物体0
	{
	  LED_RESET;//开灯 低电平	
		//IN1  高电平左后退
		//IN2  低电平
		//IN1=1 IN2=0 左后退函数	
    FRONT_RIGHT_F_RESET;  //IN1 高电平
		FRONT_RIGHT_B_SET;    //IN2 低电平

	}
	
	if(VOID_L_IO == BARRIER_N)//前方无物体1
	{
		LED_SET; //关灯 高电平
		
   //IN1  低电平
   //IN2  高电平前进
	//IN1=0 IN2=1 左前进函数
		
	 FRONT_RIGHT_F_SET;  //IN1 低电平
	 FRONT_RIGHT_B_RESET; //IN2 高电平
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
	 //LED_RESET;//开灯 低电平
	 //LED_SET; //关灯 高电平
	 	 BEHIND_RIGHT_EN; 
	 //BEHIND_LEFT_GO; //左前进函数
	 //BEHIND_LEFT_BACK; //前后退函数
	 //FRONT_RIGHT_GO;  //右前进函数（错误注释）//右后退函数
	 //FRONT_RIGHT_BACK; //右后退函数（错误注释）//右前进函数
 }
		
}


