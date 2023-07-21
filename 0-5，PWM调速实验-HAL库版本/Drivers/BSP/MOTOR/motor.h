#ifndef _MOTOR_H
#define _MOTOR_H
#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* ���� ���� */

//IN1 PC11 IO�ڶ���
#define FRONT_RIGHT_F_GPIO_PORT                  GPIOC
#define FRONT_RIGHT_F_GPIO_PIN                   GPIO_PIN_11
#define FRONT_RIGHT_F_SET                        HAL_GPIO_WritePin(FRONT_RIGHT_F_GPIO_PORT,FRONT_RIGHT_F_GPIO_PIN,GPIO_PIN_SET)
#define FRONT_RIGHT_F_RESET                      HAL_GPIO_WritePin(FRONT_RIGHT_F_GPIO_PORT,FRONT_RIGHT_F_GPIO_PIN,GPIO_PIN_RESET)

//IN2 PD0 IO�ڶ���
#define FRONT_RIGHT_B_GPIO_PORT                  GPIOD
#define FRONT_RIGHT_B_GPIO_PIN                   GPIO_PIN_0
#define FRONT_RIGHT_B_SET                        HAL_GPIO_WritePin(FRONT_RIGHT_B_GPIO_PORT,FRONT_RIGHT_B_GPIO_PIN,GPIO_PIN_SET)
#define FRONT_RIGHT_B_RESET                      HAL_GPIO_WritePin(FRONT_RIGHT_B_GPIO_PORT,FRONT_RIGHT_B_GPIO_PIN,GPIO_PIN_RESET)

//IN3 PD6 IO�ڶ���
#define BEHIND_LEFT_F_GPIO_PORT                  GPIOD
#define BEHIND_LEFT_F_GPIO_PIN                   GPIO_PIN_6
#define BEHIND_LEFT_F_SET                        HAL_GPIO_WritePin(BEHIND_LEFT_F_GPIO_PORT,BEHIND_LEFT_F_GPIO_PIN,GPIO_PIN_SET)
#define BEHIND_LEFT_F_RESET                      HAL_GPIO_WritePin(BEHIND_LEFT_F_GPIO_PORT,BEHIND_LEFT_F_GPIO_PIN,GPIO_PIN_RESET)

//IN4 PG9 IO�ڶ���
#define BEHIND_LEFT_B_GPIO_PORT                  GPIOG
#define BEHIND_LEFT_B_GPIO_PIN                   GPIO_PIN_9
#define BEHIND_LEFT_B_SET                        HAL_GPIO_WritePin(BEHIND_LEFT_B_GPIO_PORT,BEHIND_LEFT_B_GPIO_PIN,GPIO_PIN_SET)
#define BEHIND_LEFT_B_RESET                      HAL_GPIO_WritePin(BEHIND_LEFT_B_GPIO_PORT,BEHIND_LEFT_B_GPIO_PIN,GPIO_PIN_RESET)

//EN1 PD4
#define ENABLE_RIGHT_GPIO_PORT                  GPIOD
#define ENABLE_RIGHT_GPIO_PIN                   GPIO_PIN_4
#define ENABLE_RIGHT_SET                        HAL_GPIO_WritePin(ENABLE_RIGHT_GPIO_PORT,ENABLE_RIGHT_GPIO_PIN,GPIO_PIN_SET)
#define ENABLE_RIGHT_RESET                      HAL_GPIO_WritePin(ENABLE_RIGHT_GPIO_PORT,ENABLE_RIGHT_GPIO_PIN,GPIO_PIN_RESET)

//EN2 PD2
#define ENABLE_LEFT_GPIO_PORT                  GPIOD
#define ENABLE_LEFT_GPIO_PIN                   GPIO_PIN_2
#define ENABLE_LEFT_SET                        HAL_GPIO_WritePin(ENABLE_LEFT_GPIO_PORT,ENABLE_LEFT_GPIO_PIN,GPIO_PIN_SET)
#define ENABLE_LEFT_RESET                      HAL_GPIO_WritePin(ENABLE_LEFT_GPIO_PORT,ENABLE_LEFT_GPIO_PIN,GPIO_PIN_RESET)



#define MOTOR_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE();__HAL_RCC_GPIOD_CLK_ENABLE();__HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)             /* PC��PD�ں�PG��ʱ��ʹ�� */
         
/******************************************************************************************/
#define BASIC_TIM TIM6
#define BASIC_TIM_CLK_ENABLE() __TIM6_CLK_ENABLE()
#define BASIC_TIM_IRQn            TIM6_DAC_IRQn
#define BASIC_TIM_IRQHandler      TIM6_DAC_IRQHandler

/******************************************************************************************/
/*�˶�����*/
/*��ǰ*/
#define LEFT_GO FRONT_RIGHT_F_RESET;  FRONT_RIGHT_B_SET
/*���*/
#define LEFT_BACK FRONT_RIGHT_F_SET; FRONT_RIGHT_B_RESET
/*��ֹͣ*/
#define LEFT_STOP FRONT_RIGHT_F_RESET; FRONT_RIGHT_B_RESET
/*��ǰ*/
#define RIGHT_GO BEHIND_LEFT_F_RESET;  BEHIND_LEFT_B_SET
/*�Һ�*/
#define RIGHT_BACK BEHIND_LEFT_F_SET; BEHIND_LEFT_B_RESET
/*��ֹͣ*/
#define RIGHT_STOP BEHIND_LEFT_F_RESET; BEHIND_LEFT_B_RESET

/******************************************************************************************/
#define  INIT_VELOCITY 99
#define  MOTION_FLAG_LG 100
#define  MOTION_FLAG_LB 101
#define  MOTION_FLAG_RG 102
#define  MOTION_FLAG_RB 103

void motor_init(void);
void btim_timx_int_init(uint16_t arr,uint16_t psc);

void left_go(uint16_t speed);
void left_back(uint16_t speed);
void left_stop(void);
void right_go(uint16_t speed);

#endif

