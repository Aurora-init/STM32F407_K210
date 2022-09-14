#ifndef __esp_H
#define __esp_H

#include "main.h"

#define REV_OK		0	//������ɱ�־
#define REV_WAIT	1	//����δ��ɱ�־
#define USART_DEBUG		USART1		//���Դ�ӡ��ʹ�õĴ�����

typedef _Bool			uint1;
typedef unsigned char   uint8;
typedef char			int8;
typedef unsigned short  uint16;
typedef short			int16;
typedef unsigned int    uint32;
typedef int				int32;
typedef unsigned int	size_t;
typedef struct
{
	uint8_t *IPD_buff; //������·�������
	uint16_t len; 		 //�������ݳ���
}IPD_RX;

void Usart_SendString(UART_HandleTypeDef *USARTx, unsigned char *str, unsigned short len);

void UsartPrintf(UART_HandleTypeDef *USARTx, char *fmt,...);

void ESP8266_Init(void);

void ESP8266_Clear(void);

void ESP8266_SendData(unsigned char *data, unsigned short len);

unsigned char *ESP8266_GetIPD(unsigned short timeOut);
//IPD_RX ESP8266_GetIPD(void);
#endif

