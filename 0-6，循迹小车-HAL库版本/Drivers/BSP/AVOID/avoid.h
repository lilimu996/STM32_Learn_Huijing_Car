#ifndef _AVOID_H
#define _AVOID_H
#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* ���� ���� */

#define AVOIDR_GPIO_PORT                  GPIOC
#define AVOIDR_GPIO_PIN                   GPIO_PIN_7

#define AVOIDL_GPIO_PORT                  GPIOG
#define AVOIDL_GPIO_PIN                   GPIO_PIN_2


#define AVOID_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOG_CLK_ENABLE();__HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)             /* PC�ں�PG��ʱ��ʹ�� */
         
/******************************************************************************************/


#define BARRIEY 0         //���ϰ���
#define BARRIEN 1         //���ϰ���


#define READ_R_INFRARED      HAL_GPIO_ReadPin(AVOIDR_GPIO_PORT,AVOIDR_GPIO_PIN)
#define READ_L_INFRARED      HAL_GPIO_ReadPin(AVOIDL_GPIO_PORT,AVOIDL_GPIO_PIN)

void avoid_init(void);
void read_x_infrared(void);

#endif


