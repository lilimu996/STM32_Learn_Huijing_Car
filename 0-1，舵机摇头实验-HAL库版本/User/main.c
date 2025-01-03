/**
 ******************************************************************************
 * @file     main.c
 * @author   正点原子团队(ALIENTEK)
 * @version  V1.0
 * @date     2020-08-20
 * @brief    新建工程实验-HAL库版本 实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 STM32F103 开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 ******************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/SERVOS/servos.h"
#include "./BSP/LED/led.h"

extern TIM_HandleTypeDef servos_pwm_chy_handle;     /* 定时器5句柄 */

int main(void)
{
    
   
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
    led_init();                          /*LED灯初始化*/
    /*PWM周期设置成20ms,0-180度分别对应0.5-2.5ms的脉宽*/
    servos_pwm_chy_init(20000-1,72-1);  /*通用定时器初始化*/
    
    int speed=1500;                      /*控制舵机*/
    
    while(1)
    { 
        delay_ms(10);
        __HAL_TIM_SetCompare(&servos_pwm_chy_handle,TIM_CHANNEL_1,speed);
        LED0_TOGGLE();
        
        HAL_Delay(100);
        
        
    }
}

