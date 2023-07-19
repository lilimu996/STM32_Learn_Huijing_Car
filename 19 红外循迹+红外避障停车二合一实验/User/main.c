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
//char front_left_speed_duty=SPEED_DUTY;
char front_right_speed_duty=SPEED_DUTY;
char behind_left_speed_duty=SPEED_DUTY;
//char behind_right_speed_duty=SPEED_DUTY;

unsigned char tick_5ms = 0;//5ms计数器，作为主函数的基本周期
unsigned char tick_1ms = 0;//1ms计数器，作为电机的基本计数器
unsigned char tick_200ms = 0;//刷新显示

char ctrl_comm = COMM_STOP;//控制指令
char ctrl_comm_last = COMM_STOP;//上一次的指令
unsigned char continue_time=0;
unsigned char bt_rec_flag=0;//蓝牙控制标志位

//循迹，通过判断三个光电对管的状态来控制小车运动
void SearchRun(void)
{

	if(SEARCH_L_IO == 1 && SEARCH_M_IO == 1 && SEARCH_R_IO == 1)  //三路都检测到 //黑线
	{
		CarStop();  //小车停止，方便小车传感器灵敏度调试
	}
	
	if(SEARCH_L_IO == 0 && SEARCH_M_IO == 0 && SEARCH_R_IO == 1) //右边黑线，说明小车偏左，需要调用右转函数
	{
		CarRight();  //小车右转
	}
	if(SEARCH_L_IO == 1 && SEARCH_M_IO == 0 && SEARCH_R_IO == 0)//左边黑线，说明小车偏右，需要调用左转函数
	{
		CarLeft();  //小车左转
	}
	else if(SEARCH_L_IO == 0 && SEARCH_M_IO == 1 && SEARCH_R_IO == 0)//中间黑线，调用小车前进函数
	{
		CarGo();  //停小车前进
	}
	
	if((VOID_R_IO == 0) && (VOID_L_IO == 0)) //左边和右边两个红外避障传感器同时检测到障碍物
	{
  	CarStop();   //小车停止3秒后再重新循迹，方便操作取走障碍物
	  Delayms(3000);
		CarBack();   //小车后退100毫秒，防止其中两个循迹传感器同时感应到黑线时车子不走的问题
		Delayms(100);  //后退时间不宜太长，防止小车后退时冲出黑线跑道
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
			if(ctrl_comm_last != ctrl_comm)//指令发生变化
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
				Delayms(10);//防抖
				LCD1602WriteCommand(ctrl_comm);
			}
			
		}
		
 }
}

