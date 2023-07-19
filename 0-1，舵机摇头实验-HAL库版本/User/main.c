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
#include "./BSP/SERVOS/servos.h"
#include "./BSP/LED/led.h"

extern TIM_HandleTypeDef servos_pwm_chy_handle;     /* ��ʱ��5��� */

int main(void)
{
    
   
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    led_init();                          /*LED�Ƴ�ʼ��*/
    /*PWM�������ó�20ms,0-180�ȷֱ��Ӧ0.5-2.5ms������*/
    servos_pwm_chy_init(20000-1,72-1);  /*ͨ�ö�ʱ����ʼ��*/
    
    int speed=1500;                      /*���ƶ��*/
    
    while(1)
    { 
        delay_ms(10);
        __HAL_TIM_SetCompare(&servos_pwm_chy_handle,TIM_CHANNEL_1,speed);
        LED0_TOGGLE();
        
        HAL_Delay(100);
        
        
    }
}

