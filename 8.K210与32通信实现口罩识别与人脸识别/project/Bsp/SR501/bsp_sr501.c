#include "main.h"
#include "gpio.h"
#include "SR501/bsp_sr501.h"
//人体红外传感器
 
void SR501_Init(void)
{
	//重置一下电频相当于初始化了，实际的引脚配置等都由cubemx进行配置
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET);
}
