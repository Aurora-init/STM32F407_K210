#include "main.h"
#include "DHT11/bsp_dht11.h"
//温湿度传感器


/**
	******************************************************************************
	* @file			bsp_dht11.c
	* @author		Aurora_init
	* @date			
	* @version	v1.0
	* @note			DHT11 driver
	******************************************************************************
	*/

/**
	* @brief 微秒级延时
	*/
/*在这里找的是定时器5做延时，最高延时2的32次方us*/
void bsp_delay_us(uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim5, 0);
	
	HAL_TIM_Base_Start(&htim5);
	
	while (__HAL_TIM_GET_COUNTER(&htim5) != us);
	
	HAL_TIM_Base_Stop(&htim5);
}

/**
	* @brief DHT11 输出模式
	*/
static void DHT11_Mode_OUT_PP(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Pin = BSP_DHT11_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
  HAL_GPIO_Init(BSP_DHT11_PORT, &GPIO_InitStruct);
}
 
/**
	* @brief DHT11 输入模式
	*/
static void DHT11_Mode_IN_NP(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Pin = BSP_DHT11_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
 
  HAL_GPIO_Init(BSP_DHT11_PORT, &GPIO_InitStruct);
}
 
/**
	* @brief DHT11 读取字节
	*/
uint8_t DHT11_ReadByte(void)
{
	uint8_t i, temp = 0;
 
	for (i = 0; i < 8; i++)
	{
		while (DHT11_IN == 0);		
		
		bsp_delay_us(40);				
		
		if (DHT11_IN == 1)
		{
			while (DHT11_IN == 1);	
			
			temp |= (uint8_t)(0X01 << (7 - i));			
		}
		else
		{
			temp &= (uint8_t)~(0X01 << (7 - i));
		}
	}
	return temp;
}
 
/**
	* @brief DHT11 读取一次数据
	*/
uint8_t DHT11_ReadData(DHT11_Data_TypeDef *DHT11_Data)
{
	DHT11_Mode_OUT_PP();	
	DHT11_OUT_0;	
	HAL_Delay(18);		
	
	DHT11_OUT_1;			
	bsp_delay_us(30);	
 
	DHT11_Mode_IN_NP();	
	
	if (DHT11_IN == 0)		
	{
		while (DHT11_IN == 0);
		
		while (DHT11_IN == 1);	
		   
		DHT11_Data->humi_int  = DHT11_ReadByte();
		DHT11_Data->humi_deci = DHT11_ReadByte();
		DHT11_Data->temp_int  = DHT11_ReadByte();
		DHT11_Data->temp_deci = DHT11_ReadByte();
		DHT11_Data->check_sum = DHT11_ReadByte();
		
		DHT11_Mode_OUT_PP();	
		DHT11_OUT_1;	
		
		if (DHT11_Data->check_sum == DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int + DHT11_Data->temp_deci)	
		{
			return 1;
		}		
		else
		{
			return 0;
		}
	}
	else		
	{
		return 0;
	}
}

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
