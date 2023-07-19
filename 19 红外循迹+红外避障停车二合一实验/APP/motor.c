#include "motor.h"
#include "interface.h"
#include "stm32f10x.h"

//GPIO配置函数
void MotorGPIO_Configuration(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_F_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_Init(FRONT_LEFT_F_GPIO, &GPIO_InitStructure);    
	
	GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_B_PIN;	
	GPIO_Init(FRONT_LEFT_B_GPIO, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_F_PIN;	
	GPIO_Init(FRONT_RIGHT_F_GPIO, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_B_PIN;	
	GPIO_Init(FRONT_RIGHT_B_GPIO, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_LEFT_F_PIN;	
	GPIO_Init(BEHIND_LEFT_F_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_LEFT_B_PIN;	
	GPIO_Init(BEHIND_LEFT_B_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_RIGHT_F_PIN;	
	GPIO_Init(BEHIND_RIGHT_F_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = BEHIND_RIGHT_B_PIN;	
	GPIO_Init(BEHIND_RIGHT_B_GPIO, &GPIO_InitStructure);  
	
}

//根据占空比驱动电机转动
void CarMove(void)
{   
	
	 BEHIND_RIGHT_EN;
	
		//右轮
	if(front_right_speed_duty > 0)//向前
	{
		if(speed_count < front_right_speed_duty)
		{
			FRONT_RIGHT_GO;
		}else                //停止
		{
			FRONT_RIGHT_STOP;
		}
	}
	else if(front_right_speed_duty < 0)//向后
	{
		if(speed_count < (-1)*front_right_speed_duty)
		{
			FRONT_RIGHT_BACK;
		}else                //停止
		{
			FRONT_RIGHT_STOP;
		}
	}
	else                //停止
	{
		FRONT_RIGHT_STOP;
	}
	
	//左轮
	if(behind_left_speed_duty > 0)//向前
	{
		if(speed_count < behind_left_speed_duty)
		{
			BEHIND_LEFT_GO;
		}	else                //停止
		{
			BEHIND_LEFT_STOP;
		}
	}
	else if(behind_left_speed_duty < 0)//向后
	{
		if(speed_count < (-1)*behind_left_speed_duty)
		{
			BEHIND_LEFT_BACK;
		}	else                //停止
		{
			BEHIND_LEFT_STOP;
		}
	}
	else                //停止
	{
		BEHIND_LEFT_STOP;
	}
	
}

//向前
void CarGo(void)
{
	front_right_speed_duty=20;  //右前进
	behind_left_speed_duty=20; //左前进
}

//后退
void CarBack(void)
{
	front_right_speed_duty=-20; //右后退
	behind_left_speed_duty=-20; //左后退
}

//向左
void CarLeft(void)
{
	front_right_speed_duty=30;    //右边车轮前进，增加右边车轮速度右转
	behind_left_speed_duty=-20;   //左后退
}

//向右
void CarRight(void)
{
	front_right_speed_duty=-20;  //右后退
	behind_left_speed_duty=30;  //左边车轮前进，增加左边车轮速度左转
}

//停止
void CarStop(void)
{
	front_right_speed_duty=0;
	behind_left_speed_duty=0;
}

void MotorInit(void)
{
	MotorGPIO_Configuration();
	CarStop();
}

