/**
 ******************************************************************************
 * @file     main.c
 * @author   ����ԭ���Ŷ�(ALIENTEK)
 * @version  V1.0
 * @date     2020-08-20
 * @brief    �½�����ʵ��-HAL��汾 ʵ��
 * @license  Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ******************************************************************************
 * @attention
 * 
 * ʵ��ƽ̨:����ԭ�� STM32F103 ������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 ******************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/MOTOR/motor.h"
#include "./BSP/SEARCH/search.h"
#include "./BSP/AVOID/avoid.h"

extern TIM_HandleTypeDef servos_pwm_chy_handle;     /* ��ʱ��5��� */
extern uint16_t duty_cycle;

int main(void)
{
    
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    led_init();                         /*LED�Ƴ�ʼ��*/
    motor_init();                       /*�����ʼ��*/
    btim_timx_int_init(10-1,7200-1);    /*1ms����һ���ж�*/
    search_init();                       /*ѭ��ģ���ʼ��*/
    avoid_init();               /*����ģ���ʼ��*/
    
    while(1)
    { 
        /*�����ƶ�û�м�⵽��ɫ*/
        if(R_STATUS==WHITE&&M_STATUS==WHITE&&L_STATUS==WHITE)
        {
            LED0(1);
            car_go(8);
        }
        /*��ߵĵƼ�⵽��ɫ*/
        if(R_STATUS==WHITE&&M_STATUS==WHITE&&L_STATUS==BLACK)
        {
            LED0(1);
            car_right();
            if(M_STATUS==BLACK)
            {
                car_go(8);
            }
        }
         /*�ұߵĵƼ�⵽��ɫ*/
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

