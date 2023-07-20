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
#include "./BSP/AVOID/avoid.h"

extern TIM_HandleTypeDef servos_pwm_chy_handle;     /* ��ʱ��5��� */

int main(void)
{
    
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    led_init();                          /*LED�Ƴ�ʼ��*/
    avoid_init();                       /*������ϳ�ʼ��*/
    
    
    while(1)
    { 
        read_x_infrared();
        if(READ_R_INFRARED==BARRIEY)
        {
            LED0(0);
        }
        if(READ_L_INFRARED==BARRIEY)
        {
            LED1(0);
        }
        
        delay_ms(500);
        LED0(1);
        LED1(1);
       
        
        
    }
}

