#include "./BSP/MOTOR/motor.h"





void motor_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    MOTOR_GPIO_CLK_ENABLE();                                 /* 电机时钟使能 */
   

    gpio_init_struct.Pin = ENABLE_RIGHT_GPIO_PIN;            /* EN1引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull =  GPIO_NOPULL;                    /* 无上下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(ENABLE_RIGHT_GPIO_PORT, &gpio_init_struct);       /* 初始化EN1引脚 */
    
    gpio_init_struct.Pin = ENABLE_LEFT_GPIO_PIN;                   /* EN2引脚 */
    HAL_GPIO_Init(ENABLE_LEFT_GPIO_PORT, &gpio_init_struct);       /* 初始化EN2引脚 */
    ENABLE_RIGHT_RESET;                                              /* EN1引脚输出低电平 */ 
    ENABLE_LEFT_RESET;                                              /* EN2引脚输出低电平 */ 
    
    gpio_init_struct.Pin = FRONT_RIGHT_F_GPIO_PIN;                   /* IN1引脚 */
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
    
}

/*运动使能*/
void motion_enable(void)
{
    //EN1和EN2输出高电平
    ENABLE_LEFT_SET;
    ENABLE_RIGHT_SET;
}
/*运动失能*/
void motion_disable(void)
{
    //EN1和EN2输出低电平
    ENABLE_LEFT_RESET;
    ENABLE_RIGHT_RESET;

}
/*左前*/
void left_go(void)
{
    //IN1=0,IN2=1
    FRONT_RIGHT_F_RESET;
    FRONT_RIGHT_B_SET;

}
/*左后*/
void left_back(void)
{
    //IN1=0,IN2=1
    FRONT_RIGHT_F_SET;
    FRONT_RIGHT_B_RESET;
}
/*左停止*/
void left_stop(void)
{
    //IN1=0,IN2=0
    FRONT_RIGHT_F_RESET;
    FRONT_RIGHT_B_RESET;
}
/*右前*/
void right_go(void)
{
    //IN3=0,IN4=1
    BEHIND_LEFT_F_RESET;
    BEHIND_LEFT_B_SET;
}
/*右后*/
void right_back(void)
{
    //IN3=1,IN4=0
    BEHIND_LEFT_F_SET;
    BEHIND_LEFT_B_RESET;
}
/*右停止*/
void right_stop(void)
{
    //IN3=0,IN4=0
    BEHIND_LEFT_F_RESET;
    BEHIND_LEFT_B_RESET;
}


