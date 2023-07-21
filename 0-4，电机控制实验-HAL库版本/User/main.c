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

extern TIM_HandleTypeDef servos_pwm_chy_handle;     /* ��ʱ��5��� */

int main(void)
{
    
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    led_init();                         /*LED�Ƴ�ʼ��*/
    motor_init();                       /*�����ʼ��*/
    
    
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

