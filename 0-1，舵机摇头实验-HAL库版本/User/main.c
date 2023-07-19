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
#include "./BSP/TIMER/btim.h"
#include "./BSP/TIMER/gtim.h"

extern TIM_HandleTypeDef g_timx_pwm_chy_handle;     /* ��ʱ��x��� */

int main(void)
{
    
    uint16_t ledrpwmval=0;
    uint8_t dir=1;
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    led_init();                         /* LED��ʼ�� */
    gtim_timx_pwm_chy_init(50-1, 72-1);  /*ͨ�ö�ʱ����ʼ��*/
    
    while(1)
    { 
        delay_ms(10);
        if(dir) ledrpwmval++;
        else ledrpwmval--;
        if(ledrpwmval>300) dir=0;
        if(ledrpwmval==0) dir=1;
        __HAL_TIM_SET_COMPARE(&g_timx_pwm_chy_handle,TIM_CHANNEL_3,ledrpwmval);
        
    }
}

