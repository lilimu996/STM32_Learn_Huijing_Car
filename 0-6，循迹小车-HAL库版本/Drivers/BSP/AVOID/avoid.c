#include "./BSP/AVOID/avoid.h"



void avoid_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    AVOID_GPIO_CLK_ENABLE();                                 /* 红外避障时钟使能 */
   

    gpio_init_struct.Pin = AVOIDR_GPIO_PIN;                  /* 右红外模块引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                /* 输入模式 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    HAL_GPIO_Init(AVOIDR_GPIO_PORT, &gpio_init_struct);       /* 初始化右红外避障引脚 */

    gpio_init_struct.Pin = AVOIDL_GPIO_PIN;                  /* 左红外模块引脚 */
    HAL_GPIO_Init(AVOIDL_GPIO_PORT, &gpio_init_struct);       /* 初始化左红外避障引脚 */
    

}

void read_x_infrared(void)
{
    READ_R_INFRARED;
    READ_L_INFRARED;

}




