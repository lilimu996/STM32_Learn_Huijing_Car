#include "./BSP/MOTOR/motor.h"
#include "./BSP/LED/led.h"

void motor_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    MOTOR_GPIO_CLK_ENABLE();                                          /* ���ʱ��ʹ�� */
      
    gpio_init_struct.Pin = FRONT_RIGHT_F_GPIO_PIN;                     /* IN1���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;                      /* ������� */
    gpio_init_struct.Pull =  GPIO_NOPULL;                             /* �������� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                    /* ���� */   
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
    
    //EN1��EN2����ߵ�ƽ
    ENABLE_LEFT_SET;
    ENABLE_RIGHT_SET;
    
}


/*��ʱ���жϳ�ʼ������*/

TIM_HandleTypeDef g_timx_handle;                 /*������*/

void btim_timx_int_init(uint16_t arr,uint16_t psc)
{
    
    g_timx_handle.Instance=BASIC_TIM;
    g_timx_handle.Init.Prescaler=psc;
    g_timx_handle.Init.Period=arr;
    HAL_TIM_Base_Init(&g_timx_handle);
    HAL_TIM_Base_Start_IT(&g_timx_handle);
   
}


/*��ʱ������MSP��ʼ������*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();                     /*ʹ��TIM6ʱ��*/
        HAL_NVIC_SetPriority(TIM6_IRQn, 2,3);
        HAL_NVIC_EnableIRQ(TIM6_IRQn);
        
    }
}     
/*��ʱ��6�жϷ�����*/
void TIM6_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_handle);

}
/*��ʱ������ж��жϻص�����*/

uint16_t duty_cycle_l_go=INIT_VELOCITY;
uint16_t duty_cycle_l_back=INIT_VELOCITY;
uint16_t duty_cycle_r_go=INIT_VELOCITY;
uint16_t duty_cycle_r_back=INIT_VELOCITY;
uint16_t motion_flag=1;
uint16_t count=0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    count++;//���жϴ���
    //��ǰ��pwm
    if(duty_cycle_l_go<=count)
    {
        LEFT_GO;
        motion_flag=MOTION_FLAG_LG;
    }
    else
    {   
        //û��ǰ����û�к�������ͣ
       if(motion_flag!=MOTION_FLAG_LB)
       {
            LEFT_STOP;
       }
    }
    //�����pwm
    if(duty_cycle_l_back<=count)
    {
        LEFT_BACK;
        motion_flag=MOTION_FLAG_LB;
    }
    else
    {
       if(motion_flag!=MOTION_FLAG_LG)
       {
            LEFT_STOP;
       }
    }
    //��ǰ��pwm
    if(duty_cycle_r_go<=count)
    {
        RIGHT_GO;
        motion_flag=MOTION_FLAG_RG;
        
    }
    else
    {
       //û��ǰ����û�к�������ͣ
       if(motion_flag!=MOTION_FLAG_RB)
       {
            RIGHT_STOP;
       }
    }
    //�Һ���pwm
    if(duty_cycle_r_back<=count)
    {
        RIGHT_BACK;
        motion_flag=MOTION_FLAG_RB;
    }
    else
    {
       //û��ǰ����û�к�������ͣ
       if(motion_flag!=MOTION_FLAG_RG)
       {
            RIGHT_STOP;
       }
    }
    
    if(count>=10)
    {
        count=0;
    }

}
/*С��ǰ����speedΪ0��8֮�䣬speedԽС���ٶ�Խ��*/
void car_go(uint16_t speed)
{
    left_go(speed);
    right_go(speed);

}
/*С�����ˣ�speedΪ0��8֮�䣬speedԽС���ٶ�Խ��*/
void car_back(uint16_t speed)
{
    left_back(speed);
    right_back(speed);

}
/*С��ֹͣ*/
void car_stop(void)
{
    left_stop();
    right_stop();

}
/*С����ת,speedΪ2��7֮��*/
void car_left(void)
{  
        left_go(8);
        right_go(4);   
}
/*С����ת,speedΪ2��7֮��*/
void car_right(void)
{  
        right_go(8);
        left_go(4);   
}

/*��ǰ��,speedΪ0��8֮�䣬speedԽС���ٶ�Խ��*/
void left_go(uint16_t speed)
{
    if(speed<=8)
    {
        duty_cycle_l_go=speed;
        duty_cycle_l_back=INIT_VELOCITY;
    }
}
/*�����,speedΪ0��8֮�䣬speedԽС���ٶ�Խ��*/
void left_back(uint16_t speed)
{
    if(speed<=8)
    {
        duty_cycle_l_back=speed;
        duty_cycle_l_go=INIT_VELOCITY;
    }
}
/*��ֹͣ*/
void left_stop(void)
{  
        duty_cycle_l_back=INIT_VELOCITY;
        duty_cycle_l_go=INIT_VELOCITY;   
}
/*��ǰ��,speedΪ0��8֮�䣬speedԽС���ٶ�Խ��*/
void right_go(uint16_t speed)
{
    if(speed<=8)
    {
        duty_cycle_r_go=speed;
        duty_cycle_r_back=INIT_VELOCITY;
    }

}
/*�Һ���,speedΪ0��8֮�䣬speedԽС���ٶ�Խ��*/
void right_back(uint16_t speed)
{
    if(speed<=8)
    {
        duty_cycle_r_back=speed;
        duty_cycle_r_go=INIT_VELOCITY;
    }
}
/*��ֹͣ*/
void right_stop(void)
{
        duty_cycle_r_back=INIT_VELOCITY;
        duty_cycle_r_go=INIT_VELOCITY;
}



