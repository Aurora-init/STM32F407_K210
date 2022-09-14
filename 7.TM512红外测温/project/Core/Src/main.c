/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "COMMON/bsp_common.h"	//STD�������
#include "COMMON/bsp_device.h"	//����ģ�黯���
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

//dht11����
DHT11_Data_TypeDef DHT11_Data;

////TCP͸�����ݱ���
//IPD_RX ipd_rx;

//�ϴ����ݵ�buf����
char PUB_BUF[256];
const char *devSubTopic[] = {"subTOPIC"};
const char 	devPubTopic[] = 	"pubTOPIC";
uint8_t ESP8266_INIT_OK = 0;//esp8266��ʼ����ɱ�־

//����5�������ݱ���
uint8_t rx_buffer[39];	
int Body_int;						//������������
int Body_deci;					//����С������
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//���ͼ������
	unsigned short timeCount = 0;	
	//ƽ̨�������ݱ���
	unsigned char *dataPtr = NULL;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FSMC_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  MX_USART6_UART_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  MX_UART5_Init();
  /* USER CODE BEGIN 2 */
	
	//1.LCD��ʼ������//������ʾ
	LCD_Init();				LCD_DisplayOn();				LCD_Display_Dir(1);					user_main_info("LCD��ʼ���ɹ�\t[OK]\r\n");						
	
	//2.ESP01S����WIFI�ȳ�ʼ������
	ESP8266_Init();				user_main_info("ESP01S��ʼ���ɹ�\t[OK]\r\n");
	
	//3.����OneNET//����ONENET�ɹ���������������ʾһ��
	while(OneNet_DevLink()){HAL_Delay(500);}				Beep_On;				HAL_Delay(100);				Beep_Off;				user_main_info("����ONENET�ɹ�\t[OK]\r\n");				
	
	//MQTT���Ļ���
	OneNet_Subscribe(devSubTopic, 1);				user_main_info("���Ļ���ɹ�\t[OK]\r\n");								
	
	//���������ж�
	HAL_UART_Receive_IT(&huart5,(uint8_t *)rx_buffer,39);				user_main_info("����5�����жϿ���\t[OK]\r\n");
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {	
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		HAL_UART_Receive_IT(&huart5,(uint8_t *)rx_buffer,39);
		
		if(++timeCount >= 100)// 2500ms / 25 = 100 ���ͼ��2500ms
		{
			sprintf(PUB_BUF,"{\"Hum\":%d.%d,\"Temp\":%d.%d}",DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
			OneNet_Publish(devPubTopic, PUB_BUF);
			
			OneNet_SendData();
			timeCount = 0;
			ESP8266_Clear();
		}
		//���ƽ̨�Ƿ�����Ӧ
		dataPtr = ESP8266_GetIPD(3);
		if(dataPtr != NULL)
		OneNet_RevPro(dataPtr);
		HAL_Delay(10);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//�����������һЩ����ɨ��ͻص�������

//���ڽ����жϻص�����
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == UART5)
	{
		LCD_Clear(0xFFFF);
		char lcd_std[39];
	
		char *string1  = strstr((const char *)rx_buffer, "Amb");
		char *string2  = strstr((const char *)rx_buffer, "Object");
		char *string3  = strstr((const char *)rx_buffer, "Body");
		
		LCD_ShowString(66,66,500,24,24,(uint8_t*)string1);
		LCD_ShowString(66,106,500,24,24,(uint8_t*)string2);
		LCD_ShowString(66,146,500,24,24,(uint8_t*)string3);	
		
		Body_int_x =  ((int)string3[5] - 48)*10+((int)string3[6]-48);
		Body_deci_x = ((int)string3[8] - 48)*10+((int)string3[9]-48);
		
		sprintf((char*)lcd_std,"Body TEMP : %s \r\n",&string3[5]);
		LCD_ShowString(66,206,500,24,24,(uint8_t*)lcd_std);
		
		
		//������´���37.5�Ⱦʹ��ڴ�ӡ������ʾ�֣��ҷ���������
		if(Body_int>38||(Body_int>=37&&Body_deci>50))
		{
			user_main_info("%s is Warming Body TEMP\r\n",&string3[5]);
			sprintf((char*)lcd_std,"%s is Warming Body TEMP\r\n",&string3[5]);
			LCD_ShowString(66,186,500,24,24,(uint8_t*)lcd_std);
			Beep_On;				HAL_Delay(1000);				Beep_Off;
			WARMING_FLAG = 1;
		}
		for(uint8_t i=0;i<39;i++)
		{
			rx_buffer[i]=0;
		}
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
