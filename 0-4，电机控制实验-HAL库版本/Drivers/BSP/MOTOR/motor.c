#include "./BSP/MOTOR/motor.h"





void motor_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    MOTOR_GPIO_CLK_ENABLE();                                 /* ���ʱ��ʹ�� */
   

    gpio_init_struct.Pin = ENABLE_RIGHT_GPIO_PIN;            /* EN1���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
    gpio_init_struct.Pull =  GPIO_NOPULL;                    /* �������� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(ENABLE_RIGHT_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��EN1���� */
    
    gpio_init_struct.Pin = ENABLE_LEFT_GPIO_PIN;                   /* EN2���� */
    HAL_GPIO_Init(ENABLE_LEFT_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��EN2���� */
    ENABLE_RIGHT_RESET;                                              /* EN1��������͵�ƽ */ 
    ENABLE_LEFT_RESET;                                              /* EN2��������͵�ƽ */ 
    
    gpio_init_struct.Pin = FRONT_RIGHT_F_GPIO_PIN;                   /* IN1���� */
    HAL_GPIO_Init(FRONT_RIGHT_F_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��IN1���� */
    FRONT_RIGHT_F_RESET;                                             /*IN1����͵�ƽ*/
    
    gpio_init_struct.Pin = FRONT_RIGHT_B_GPIO_PIN;                   /* IN2���� */
    HAL_GPIO_Init(FRONT_RIGHT_B_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��IN2���� */
    FRONT_RIGHT_B_RESET;                                             /*IN2����͵�ƽ*/
    
    gpio_init_struct.Pin = BEHIND_LEFT_F_GPIO_PIN;                   /* IN3���� */
    HAL_GPIO_Init(BEHIND_LEFT_F_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��IN3���� */
    BEHIND_LEFT_F_RESET;                                             /*IN3����͵�ƽ*/
    
    gpio_init_struct.Pin = BEHIND_LEFT_B_GPIO_PIN;                   /* IN4���� */
    HAL_GPIO_Init(BEHIND_LEFT_B_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��IN4���� */
    BEHIND_LEFT_B_RESET;                                             /*IN4����͵�ƽ*/
    
}

/*�˶�ʹ��*/
void motion_enable(void)
{
    //EN1��EN2����ߵ�ƽ
    ENABLE_LEFT_SET;
    ENABLE_RIGHT_SET;
}
/*�˶�ʧ��*/
void motion_disable(void)
{
    //EN1��EN2����͵�ƽ
    ENABLE_LEFT_RESET;
    ENABLE_RIGHT_RESET;

}
/*��ǰ*/
void left_go(void)
{
    //IN1=0,IN2=1
    FRONT_RIGHT_F_RESET;
    FRONT_RIGHT_B_SET;

}
/*���*/
void left_back(void)
{
    //IN1=0,IN2=1
    FRONT_RIGHT_F_SET;
    FRONT_RIGHT_B_RESET;
}
/*��ֹͣ*/
void left_stop(void)
{
    //IN1=0,IN2=0
    FRONT_RIGHT_F_RESET;
    FRONT_RIGHT_B_RESET;
}
/*��ǰ*/
void right_go(void)
{
    //IN3=0,IN4=1
    BEHIND_LEFT_F_RESET;
    BEHIND_LEFT_B_SET;
}
/*�Һ�*/
void right_back(void)
{
    //IN3=1,IN4=0
    BEHIND_LEFT_F_SET;
    BEHIND_LEFT_B_RESET;
}
/*��ֹͣ*/
void right_stop(void)
{
    //IN3=0,IN4=0
    BEHIND_LEFT_F_RESET;
    BEHIND_LEFT_B_RESET;
}


