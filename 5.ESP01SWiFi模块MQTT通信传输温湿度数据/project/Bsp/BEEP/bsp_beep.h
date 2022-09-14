#include "main.h"
#include "gpio.h"

#ifndef __BSP_BEEP_H
#define __BSP_BEEP_H

#define BEEP_GPIO_Port    GPIOD						//�����������Ӷ˿ں�
#define BEEP_Pin					GPIO_PIN_7			//��������PIN���ź�

//�����ҵķ������ǵ͵�ƽ����
#define Beep_On     HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_RESET)
#define Beep_Off    HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_SET)
#define Beep_Toggle HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin)


#endif



/*���ӣ�

		Beep_On;//�򿪷�����
		for(int i=0;i<10;i++)
		{
			HAL_Delay(1000);//��ʱ
		}
		Beep_Off;//�رշ�����
		for(int i=0;i<10;i++)
		{
			HAL_Delay(1000);//��ʱ
		}
		
*/
