#include "INFO/bsp_info.h"
#include "COMMON/bsp_common.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "main.h"
//�����ض���

/*****************************************************************
ʹ��UART6�������ݷ���

���ߣ������
���ܣ��ض���printf()��scanf()

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

//#define USER_MAIN_DEBUG

//#ifdef USER_MAIN_DEBUG
//#define user_main_printf(format, ...) 	printf( format "\r\n",##__VA_ARGS__)
//#define user_main_info(format, ...) 		printf("��main��info:" format "\r\n",##__VA_ARGS__)
//#define user_main_debug(format, ...) 		printf("��main��debug:" format "\r\n",##__VA_ARGS__)
//#define user_main_error(format, ...) 		printf("��main��error:" format "\r\n",##__VA_ARGS__)
//#else
//#define user_main_printf(format, ...)
//#define user_main_info(format, ...)
//#define user_main_debug(format, ...)
//#define user_main_error(format, ...)

//#endif
