#ifndef __esp_H
#define __esp_H

#include "main.h"

#define REV_OK		0	//接收完成标志
#define REV_WAIT	1	//接收未完成标志
#define USART_DEBUG		USART1		//调试打印所使用的串口组

typedef _Bool			uint1;
typedef unsigned char   uint8;
typedef char			int8;
typedef unsigned short  uint16;
typedef short			int16;
typedef unsigned int    uint32;
typedef int				int32;
typedef unsigned int	size_t;

void Usart_SendString(UART_HandleTypeDef *USARTx, unsigned char *str, unsigned short len);

void UsartPrintf(UART_HandleTypeDef *USARTx, char *fmt,...);

void ESP8266_Init(void);

void ESP8266_Clear(void);

void ESP8266_SendData(unsigned char *data, unsigned short len);

unsigned char *ESP8266_GetIPD(unsigned short timeOut);

#endif

