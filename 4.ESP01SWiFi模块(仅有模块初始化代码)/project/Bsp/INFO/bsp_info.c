#include "INFO/bsp_info.h"
#include "COMMON/bsp_common.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "main.h"


/*****************************************************************
使用UART6进行数据发送

作者：衾许°
功能：重定向printf()与scanf()

*****************************************************************/

//int fputc(int ch,FILE *f)
//{
//    uint8_t temp[1]={ch};
//    HAL_UART_Transmit(&huart6,temp,1,2);
//		return 0;
//}

//int fgetc(FILE *f)
//{
//	uint8_t ch[1];
//	HAL_UART_Receive(&huart6,ch,1,0xffff);
//	return ch[0];
//}

