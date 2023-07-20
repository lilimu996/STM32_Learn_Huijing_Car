#ifndef _SEARCH_H
#define _SEARCH_H
#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* 引脚 定义 */

#define SEARCHR_GPIO_PORT                  GPIOG
#define SEARCHR_GPIO_PIN                   GPIO_PIN_4

#define SEARCHM_GPIO_PORT                  GPIOG
#define SEARCHM_GPIO_PIN                   GPIO_PIN_8

#define SEARCHL_GPIO_PORT                  GPIOG
#define SEARCHL_GPIO_PIN                   GPIO_PIN_6


#define SEARCH_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)             /* PB口时钟使能 */
         
/******************************************************************************************/

/*读取循迹模块输入状态*/
#define R_STATUS                    HAL_GPIO_ReadPin(SEARCHR_GPIO_PORT,SEARCHR_GPIO_PIN)
#define M_STATUS                    HAL_GPIO_ReadPin(SEARCHM_GPIO_PORT,SEARCHM_GPIO_PIN)
#define L_STATUS                    HAL_GPIO_ReadPin(SEARCHL_GPIO_PORT,SEARCHL_GPIO_PIN)


void search_init(void);
void read_status(void);



#endif






