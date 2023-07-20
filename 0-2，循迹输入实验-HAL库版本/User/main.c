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
#include "./BSP/SEARCH/search.h"

extern TIM_HandleTypeDef servos_pwm_chy_handle;     /* ��ʱ��5��� */

int main(void)
{
    uint16_t wight=0;
    uint16_t black=1;
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    led_init();                          /*LED�Ƴ�ʼ��*/
    search_init();                       /*ѭ��ģ���ʼ��*/
    
    while(1)
    { 
        
        read_status();
      
        if(R_STATUS==wight&&M_STATUS==wight&&L_STATUS==wight)
        {
            LED0(1);
        }
        if(R_STATUS==black&&M_STATUS==black&&L_STATUS==black)
        {
            LED0(0);
        
        }
        delay_ms(200);
       
        
        
    }
}

