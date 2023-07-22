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
#include "./BSP/SEARCH/search.h"
#include "./BSP/AVOID/avoid.h"

extern TIM_HandleTypeDef servos_pwm_chy_handle;     /* 定时器5句柄 */
extern uint16_t duty_cycle;

int main(void)
{
    
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
    led_init();                         /*LED灯初始化*/
    motor_init();                       /*电机初始化*/
    btim_timx_int_init(10-1,7200-1);    /*1ms进入一次中断*/
    search_init();                       /*循迹模块初始化*/
    avoid_init();               /*避障模块初始化*/
    
    while(1)
    { 
        /*三个灯都没有检测到黑色*/
        if(R_STATUS==WHITE&&M_STATUS==WHITE&&L_STATUS==WHITE)
        {
            LED0(1);
            car_go(8);
        }
        /*左边的灯检测到黑色*/
        if(R_STATUS==WHITE&&M_STATUS==WHITE&&L_STATUS==BLACK)
        {
            LED0(1);
            car_right();
            if(M_STATUS==BLACK)
            {
                car_go(8);
            }
        }
         /*右边的灯检测到黑色*/
        if(R_STATUS==BLACK&&M_STATUS==WHITE&&L_STATUS==WHITE)
        {
            LED0(1);
            car_right();
             if(M_STATUS==BLACK)
            {
                car_go(8);
            }
        }
        if(READ_R_INFRARED== BARRIEY&&READ_L_INFRARED== BARRIEY)
        {
            car_stop();
        }
        if(READ_R_INFRARED== BARRIEN&&READ_L_INFRARED== BARRIEN)
        {
            car_go(8);
        }
        if(READ_R_INFRARED== BARRIEN&&READ_L_INFRARED== BARRIEY)
        {
            car_right();
            delay_ms(300);
        }
        if(READ_R_INFRARED== BARRIEY&&READ_L_INFRARED== BARRIEN)
        {
            car_left();
            delay_ms(300);
        }
        
        delay_ms(100);
        
        
    }
}

