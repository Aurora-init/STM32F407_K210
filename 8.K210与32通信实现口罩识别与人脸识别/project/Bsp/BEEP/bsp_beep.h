#include "main.h"
#include "gpio.h"

#ifndef __BSP_BEEP_H
#define __BSP_BEEP_H

#define BEEP_GPIO_Port    GPIOD						//蜂鸣器的连接端口号
#define BEEP_Pin					GPIO_PIN_7			//蜂鸣器的PIN引脚号

//这里我的蜂鸣器是低电平触发
#define Beep_On     HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_RESET)
#define Beep_Off    HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_SET)
#define Beep_Toggle HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin)


#endif



/*例子：

		Beep_On;//打开蜂鸣器
		for(int i=0;i<10;i++)
		{
			HAL_Delay(1000);//延时
		}
		Beep_Off;//关闭蜂鸣器
		for(int i=0;i<10;i++)
		{
			HAL_Delay(1000);//延时
		}
		
*/
