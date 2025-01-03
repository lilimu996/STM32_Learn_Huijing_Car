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
#include "./BSP/LED/led.h"
#include "./BSP/MOTOR/motor.h"

extern TIM_HandleTypeDef servos_pwm_chy_handle;     /* 定时器5句柄 */

int main(void)
{
    
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
    led_init();                         /*LED灯初始化*/
    motor_init();                       /*电机初始化*/
    
    
    while(1)
    { 
       
        LED0(0);
        motion_enable();
        delay_ms(1);
        left_go();
        delay_ms(2000);
        left_stop();
        delay_ms(500);
        left_back();
        delay_ms(2000);
        left_stop();
        delay_ms(1);
        motion_disable();
        
        
    }
}

