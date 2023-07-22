#ifndef _AVOID_H
#define _AVOID_H
#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* 引脚 定义 */

#define AVOIDR_GPIO_PORT                  GPIOC
#define AVOIDR_GPIO_PIN                   GPIO_PIN_7

#define AVOIDL_GPIO_PORT                  GPIOG
#define AVOIDL_GPIO_PIN                   GPIO_PIN_2


#define AVOID_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOG_CLK_ENABLE();__HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)             /* PC口和PG口时钟使能 */
         
/******************************************************************************************/


#define BARRIEY 0         //有障碍物
#define BARRIEN 1         //无障碍物


#define READ_R_INFRARED      HAL_GPIO_ReadPin(AVOIDR_GPIO_PORT,AVOIDR_GPIO_PIN)
#define READ_L_INFRARED      HAL_GPIO_ReadPin(AVOIDL_GPIO_PORT,AVOIDL_GPIO_PIN)

void avoid_init(void);
void read_x_infrared(void);

#endif


