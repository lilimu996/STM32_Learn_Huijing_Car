#include "./BSP/AVOID/avoid.h"



void avoid_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    AVOID_GPIO_CLK_ENABLE();                                 /* �������ʱ��ʹ�� */
   

    gpio_init_struct.Pin = AVOIDR_GPIO_PIN;                  /* �Һ���ģ������ */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                /* ����ģʽ */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    HAL_GPIO_Init(AVOIDR_GPIO_PORT, &gpio_init_struct);       /* ��ʼ���Һ���������� */

    gpio_init_struct.Pin = AVOIDL_GPIO_PIN;                  /* �����ģ������ */
    HAL_GPIO_Init(AVOIDL_GPIO_PORT, &gpio_init_struct);       /* ��ʼ�������������� */
    

}

void read_x_infrared(void)
{
    READ_R_INFRARED;
    READ_L_INFRARED;

}




