#include "./BSP/SERVOS/servos.h"


TIM_HandleTypeDef servos_pwm_chy_handle;

/* 通用定时器PWM输出初始化函数 */
void servos_pwm_chy_init(uint16_t arr, uint16_t psc)
{
    TIM_OC_InitTypeDef servos_oc_pwm_chy;
    
    servos_pwm_chy_handle.Instance = TIM5;
    servos_pwm_chy_handle.Init.Prescaler = psc;
    servos_pwm_chy_handle.Init.Period = arr;
    servos_pwm_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_PWM_Init(&servos_pwm_chy_handle);
    
    servos_oc_pwm_chy.OCMode = TIM_OCMODE_PWM1;
    servos_oc_pwm_chy.Pulse = 550;
    servos_oc_pwm_chy.OCPolarity = TIM_OCPOLARITY_HIGH;
    HAL_TIM_PWM_ConfigChannel(&servos_pwm_chy_handle, &servos_oc_pwm_chy, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&servos_pwm_chy_handle, TIM_CHANNEL_1);
}

/* 定时器输出PWM MSP初始化函数 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM5)
    {
        GPIO_InitTypeDef gpio_init_struct;
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_TIM5_CLK_ENABLE();

        gpio_init_struct.Pin = GPIO_PIN_0;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* 推挽复用 */
        gpio_init_struct.Pull = GPIO_PULLUP;                /* 上拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* 高速 */
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);
        
       
    }
}

void servos_tune(uint16_t angles){
    
    __HAL_TIM_SET_COMPARE(&servos_pwm_chy_handle,TIM_CHANNEL_1,angles);
    
}


