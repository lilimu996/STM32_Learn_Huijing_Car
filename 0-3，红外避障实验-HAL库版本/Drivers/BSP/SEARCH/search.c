#include "./BSP/SEARCH/search.h"



void search_init(void)
{

    GPIO_InitTypeDef gpio_init_struct;
    SEARCH_GPIO_CLK_ENABLE();                                   /* 循迹传感器时钟使能 */
   

    gpio_init_struct.Pin = SEARCHR_GPIO_PIN;                   /* 循迹模块引脚R */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                  /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                     /* 上拉 */
    
    HAL_GPIO_Init(SEARCHR_GPIO_PORT, &gpio_init_struct);    /* 初始化循迹模块引脚R */

    gpio_init_struct.Pin = SEARCHM_GPIO_PIN;                /* 循迹模块引脚M */
    HAL_GPIO_Init(SEARCHM_GPIO_PORT, &gpio_init_struct);    /* 初始化循迹模块引脚M*/
    
    gpio_init_struct.Pin = SEARCHL_GPIO_PIN;                /* 循迹模块引脚L */
    HAL_GPIO_Init(SEARCHL_GPIO_PORT, &gpio_init_struct);    /* 初始化循迹模块引脚L*/
    
    

}

/*读取循迹模块状态*/
void read_status(void)
{
    R_STATUS;
    M_STATUS;
    L_STATUS;

}


