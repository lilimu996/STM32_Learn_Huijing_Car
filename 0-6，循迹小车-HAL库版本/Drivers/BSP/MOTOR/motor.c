#include "./BSP/MOTOR/motor.h"
#include "./BSP/LED/led.h"

void motor_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    MOTOR_GPIO_CLK_ENABLE();                                          /* 电机时钟使能 */
      
    gpio_init_struct.Pin = FRONT_RIGHT_F_GPIO_PIN;                     /* IN1引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;                      /* 推挽输出 */
    gpio_init_struct.Pull =  GPIO_NOPULL;                             /* 无上下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                    /* 高速 */   
    HAL_GPIO_Init(FRONT_RIGHT_F_GPIO_PORT, &gpio_init_struct);       /* 初始化IN1引脚 */
    FRONT_RIGHT_F_RESET;                                             /*IN1输出低电平*/
    
    gpio_init_struct.Pin = FRONT_RIGHT_B_GPIO_PIN;                   /* IN2引脚 */
    HAL_GPIO_Init(FRONT_RIGHT_B_GPIO_PORT, &gpio_init_struct);       /* 初始化IN2引脚 */
    FRONT_RIGHT_B_RESET;                                             /*IN2输出低电平*/
    
    gpio_init_struct.Pin = BEHIND_LEFT_F_GPIO_PIN;                   /* IN3引脚 */
    HAL_GPIO_Init(BEHIND_LEFT_F_GPIO_PORT, &gpio_init_struct);       /* 初始化IN3引脚 */
    BEHIND_LEFT_F_RESET;                                             /*IN3输出低电平*/
    
    gpio_init_struct.Pin = BEHIND_LEFT_B_GPIO_PIN;                   /* IN4引脚 */
    HAL_GPIO_Init(BEHIND_LEFT_B_GPIO_PORT, &gpio_init_struct);       /* 初始化IN4引脚 */
    BEHIND_LEFT_B_RESET;                                             /*IN4输出低电平*/
    
    //EN1和EN2输出高电平
    ENABLE_LEFT_SET;
    ENABLE_RIGHT_SET;
    
}


/*定时器中断初始化函数*/

TIM_HandleTypeDef g_timx_handle;                 /*定义句柄*/

void btim_timx_int_init(uint16_t arr,uint16_t psc)
{
    
    g_timx_handle.Instance=BASIC_TIM;
    g_timx_handle.Init.Prescaler=psc;
    g_timx_handle.Init.Period=arr;
    HAL_TIM_Base_Init(&g_timx_handle);
    HAL_TIM_Base_Start_IT(&g_timx_handle);
   
}


/*定时器基础MSP初始化函数*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();                     /*使能TIM6时钟*/
        HAL_NVIC_SetPriority(TIM6_IRQn, 2,3);
        HAL_NVIC_EnableIRQ(TIM6_IRQn);
        
    }
}     
/*定时器6中断服务函数*/
void TIM6_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_handle);

}
/*定时器溢出中断中断回调函数*/

uint16_t duty_cycle_l_go=INIT_VELOCITY;
uint16_t duty_cycle_l_back=INIT_VELOCITY;
uint16_t duty_cycle_r_go=INIT_VELOCITY;
uint16_t duty_cycle_r_back=INIT_VELOCITY;
uint16_t motion_flag=1;
uint16_t count=0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    count++;//计中断次数
    //左前进pwm
    if(duty_cycle_l_go<=count)
    {
        LEFT_GO;
        motion_flag=MOTION_FLAG_LG;
    }
    else
    {   
        //没有前进且没有后退则暂停
       if(motion_flag!=MOTION_FLAG_LB)
       {
            LEFT_STOP;
       }
    }
    //左后退pwm
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
    //右前进pwm
    if(duty_cycle_r_go<=count)
    {
        RIGHT_GO;
        motion_flag=MOTION_FLAG_RG;
        
    }
    else
    {
       //没有前进且没有后退则暂停
       if(motion_flag!=MOTION_FLAG_RB)
       {
            RIGHT_STOP;
       }
    }
    //右后退pwm
    if(duty_cycle_r_back<=count)
    {
        RIGHT_BACK;
        motion_flag=MOTION_FLAG_RB;
    }
    else
    {
       //没有前进且没有后退则暂停
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
/*小车前进，speed为0到8之间，speed越小，速度越快*/
void car_go(uint16_t speed)
{
    left_go(speed);
    right_go(speed);

}
/*小车后退，speed为0到8之间，speed越小，速度越快*/
void car_back(uint16_t speed)
{
    left_back(speed);
    right_back(speed);

}
/*小车停止*/
void car_stop(void)
{
    left_stop();
    right_stop();

}
/*小车左转,speed为2到7之间*/
void car_left(void)
{  
        left_go(8);
        right_go(4);   
}
/*小车右转,speed为2到7之间*/
void car_right(void)
{  
        right_go(8);
        left_go(4);   
}

/*左前进,speed为0到8之间，speed越小，速度越快*/
void left_go(uint16_t speed)
{
    if(speed<=8)
    {
        duty_cycle_l_go=speed;
        duty_cycle_l_back=INIT_VELOCITY;
    }
}
/*左后退,speed为0到8之间，speed越小，速度越快*/
void left_back(uint16_t speed)
{
    if(speed<=8)
    {
        duty_cycle_l_back=speed;
        duty_cycle_l_go=INIT_VELOCITY;
    }
}
/*左停止*/
void left_stop(void)
{  
        duty_cycle_l_back=INIT_VELOCITY;
        duty_cycle_l_go=INIT_VELOCITY;   
}
/*右前进,speed为0到8之间，speed越小，速度越快*/
void right_go(uint16_t speed)
{
    if(speed<=8)
    {
        duty_cycle_r_go=speed;
        duty_cycle_r_back=INIT_VELOCITY;
    }

}
/*右后退,speed为0到8之间，speed越小，速度越快*/
void right_back(uint16_t speed)
{
    if(speed<=8)
    {
        duty_cycle_r_back=speed;
        duty_cycle_r_go=INIT_VELOCITY;
    }
}
/*右停止*/
void right_stop(void)
{
        duty_cycle_r_back=INIT_VELOCITY;
        duty_cycle_r_go=INIT_VELOCITY;
}



