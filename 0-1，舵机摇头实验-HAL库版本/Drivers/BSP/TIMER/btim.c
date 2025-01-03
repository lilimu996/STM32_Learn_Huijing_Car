#include "./BSP/TIMER/btim.h"
#include "./BSP/LED/led.h"

/*定时器中断初始化函数*/

TIM_HandleTypeDef g_timx_handle;                 /*定义句柄*/

void btim_timx_int_init(uint16_t arr,uint16_t psc)
{
    
    g_timx_handle.Instance=TIM6;
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


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM6)
    {
        LED0_TOGGLE();
    }



}


