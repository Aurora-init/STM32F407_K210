#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "INFO/bsp_info.h"

#ifndef __BSP_DHT11_H
#define __BSP_DHT11_H
 
#define BSP_DHT11_PORT		GPIOD
#define BSP_DHT11_PIN			GPIO_PIN_6
 
#define DHT11_OUT_1				HAL_GPIO_WritePin(BSP_DHT11_PORT, BSP_DHT11_PIN, GPIO_PIN_SET)
#define DHT11_OUT_0				HAL_GPIO_WritePin(BSP_DHT11_PORT, BSP_DHT11_PIN, GPIO_PIN_RESET)
 
#define DHT11_IN					HAL_GPIO_ReadPin(BSP_DHT11_PORT, BSP_DHT11_PIN)
 
typedef struct
{
	uint8_t humi_int;				// 湿度的整数部分
	uint8_t humi_deci;	 		// 湿度的小数部分
	uint8_t temp_int;	 			// 温度的整数部分
	uint8_t temp_deci;	 		// 温度的小数部分
	uint8_t check_sum;	 		// 校验和
		                 
}DHT11_Data_TypeDef;
 
uint8_t DHT11_ReadData(DHT11_Data_TypeDef* DHT11_Data);
 
#endif	/* __BSP_DHT11_H */


/**
	* @brief DHT11例子
	*/
/**
DHT11_Data_TypeDef DHT11_Data;//dht11变量

char uart_std[21];

if(DHT11_ReadData(&DHT11_Data))
		{	
			user_main_info("\r\nDHT11 Read Success!\r\n");
			
			sprintf(uart_std,"\r\n湿度为%d.%d ％RH\r\n", DHT11_Data.humi_int,DHT11_Data.humi_deci);
			HAL_UART_Transmit(&huart6,(uint8_t*)uart_std,21,0XFFFF);
			
			sprintf(uart_std,"\r\n温度为%d.%d  ℃  \r\n", DHT11_Data.temp_int,DHT11_Data.temp_deci);
			HAL_UART_Transmit(&huart6,(uint8_t*)uart_std,21,0XFFFF);
		}
		else
		{
			user_main_error("Read DHT11 ERROR!\r\n");
		}
		HAL_Delay(3000);
		
*/

