#include "stm32f10x.h"
#include "interface.h"

int main() //你好，星慈光零基础STM32编程视频教程
{
    GPIOCLKInit();
    UserLEDInit();
	while(1)
	{
		LED_RESET;
	}
}
