#include "main.h"
#include "gpio.h"
#include "SR501/bsp_sr501.h"

 
void SR501_Init(void)
{
	//����һ�µ�Ƶ�൱�ڳ�ʼ���ˣ�ʵ�ʵ��������õȶ���cubemx��������
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET);
}
