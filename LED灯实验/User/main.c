#include "stm32f10x.h"
#include "interface.h"

int main() //你好，星慈光零基础STM32编程视频教程
{
    GPIOCLKInit();              /*初始化GPIO时钟*/
    UserLEDInit();              /*初始化LED灯*/
    delay_init();               /*初始化延时函数*/
	while(1)
	{
		LED8_RESET;              /*点亮LED8灯*/
        Delayms(200);           /*延时200ms*/
        LED8_SET;               /*熄灭LED8灯*/
        LED_RESET;              /*点亮LED灯*/
        Delayms(200);           /*延时200ms*/
        LED_SET;               /*熄灭LED灯*/
        Delayms(200);           /*延时200ms*/
        
	}
}
