//连接方式 ：请参考interface.h文件
//部份源码来源网络--请试用24小时后删除

#include "stm32f10x.h"
#include "interface.h" //连接IO口定义头文件
#include "LCD1602.h"
#include "IRCtrol.h"
#include "motor.h"

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
unsigned char continue_time=0;


int main(void)
{
	delay_init();
	GPIOCLKInit();
	UserLEDInit();
	LCD1602Init();
	IRCtrolInit();
	TIM2_Init();
	MotorInit();
//	ServoInit();

 while(1)
 {	 
	 		if(tick_5ms >= 5)//5ms 
		{
			tick_5ms = 0;
			tick_200ms++;
			if(tick_200ms >= 40)
			{
				tick_200ms = 0;
				//LEDToggle(LED_PIN);
			}
			
			//do something
			if(ir_rec_flag == 1)//接收到红外信号
			{
				ir_rec_flag = 0;
				switch(ctrl_comm)
				{
					case COMM_UP:    LED_RESET;break; 
					case COMM_DOWN:  LED_SET;break;

					default : break;
				}
				LCD1602WriteCommand(ctrl_comm);
			}
		}
		
 }
}

