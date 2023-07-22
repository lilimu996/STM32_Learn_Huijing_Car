#include "./BSP/SEARCH/search.h"



void search_init(void)
{

    GPIO_InitTypeDef gpio_init_struct;
    SEARCH_GPIO_CLK_ENABLE();                                   /* ѭ��������ʱ��ʹ�� */
   

    gpio_init_struct.Pin = SEARCHR_GPIO_PIN;                   /* ѭ��ģ������R */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                  /* ���� */
    gpio_init_struct.Pull = GPIO_PULLUP;                     /* ���� */
    
    HAL_GPIO_Init(SEARCHR_GPIO_PORT, &gpio_init_struct);    /* ��ʼ��ѭ��ģ������R */

    gpio_init_struct.Pin = SEARCHM_GPIO_PIN;                /* ѭ��ģ������M */
    HAL_GPIO_Init(SEARCHM_GPIO_PORT, &gpio_init_struct);    /* ��ʼ��ѭ��ģ������M*/
    
    gpio_init_struct.Pin = SEARCHL_GPIO_PIN;                /* ѭ��ģ������L */
    HAL_GPIO_Init(SEARCHL_GPIO_PORT, &gpio_init_struct);    /* ��ʼ��ѭ��ģ������L*/
    
    

}

/*��ȡѭ��ģ��״̬*/
void read_status(void)
{
    R_STATUS;
    M_STATUS;
    L_STATUS;

}


