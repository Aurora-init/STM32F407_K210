//���example.c��Ҫ���ڷ�����һЩ������Ĵ��룬��ֹ��ʱ��Ҫ�ο���ʱ���Ҳ���
//  MX_GPIO_Init();							//Ŀǰ����BEEP��SR501
//  MX_FSMC_Init();							//LCD����
//  MX_TIM3_Init();							//LCDר��us����ʱ
//  MX_TIM5_Init();							//DHT11ר��us����ʱ
//  MX_TIM4_Init();							//ESP01Sר��us����ʱ
//  MX_USART6_UART_Init();			//���ڴ����ض���
//  MX_USART1_UART_Init();			//ESP01Satָ��ʹ���


//LCD��ʾ����
//		LCD_ShowString(30,40,250,24,24,(uint8_t*)"Explorer STM32F4");	
//		LCD_ShowString(30,70,200,16,16,(uint8_t*)"TFTLCD TEST");
//		LCD_ShowString(30,90,200,16,16,(uint8_t*)"ATOM@ALIENTEK");
//		sprintf((char*)lcd_std,"LCD ID:%04X",lcddev.id);
//		LCD_ShowString(30,110,200,16,16,lcd_std);
//		sprintf((char*)lcd_std,"KEY:%04d",key_val);
//		LCD_ShowString(30,130,200,12,12,lcd_std);  
		
		//DHT11����
//		if(DHT11_ReadData(&DHT11_Data))
//		{	
//			user_main_info("\r\nDHT11 Read Success!\r\n");
//			
//			sprintf(uart_std,"\r\nʪ��Ϊ%d.%d ��RH\r\n", DHT11_Data.humi_int,DHT11_Data.humi_deci);
//			HAL_UART_Transmit(&huart6,(uint8_t*)uart_std,21,0XFFFF);
//			
//			sprintf(uart_std,"\r\n�¶�Ϊ%d.%d  ��  \r\n", DHT11_Data.temp_int,DHT11_Data.temp_deci);
//			HAL_UART_Transmit(&huart6,(uint8_t*)uart_std,21,0XFFFF);
//		}
//		else
//		{
//			user_main_error("Read DHT11 ERROR!\r\n");
//		}
//		HAL_Delay(3000);

		//BEEP����
//		
//		for(int i=0;i<10;i++)
//		{
//			HAL_Delay(1000);//��ʱ
//		}
//		Beep_Off;//�رշ�����
//		for(int i=0;i<10;i++)
//		{
//			HAL_Delay(1000);//��ʱ
//		}

		//SR501������⴫��������
//		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_10) == 1)
//		{
//			
//			printf("����\r\n");
//			HAL_Delay(100);
//		}
//		else  
//		{
//			printf("û��\r\n");
//			HAL_Delay(1000);
//		}

//void ESP01S_SEND_AT(void)
//{
////	sprintf((char*)usart1_txbuf,"AT \r\n");
////	HAL_UART_Transmit(&huart1,(unsigned char *)usart1_txbuf, strlen(usart1_txbuf), 0xffff);
//	
//	HAL_UART_Transmit(&huart1,(uint8_t*)"AT\r\n",6,50);  WIFI_delay_us(100);
//	
//	HAL_UART_Transmit(&huart1,(uint8_t*)"AT+CWMODE_CUR=1\r\n",19,50);  WIFI_delay_us(100);
//	
//	char ssid[] = "Ace2";
//	char pswd[] = "123780807";
//	sprintf((char*)usart1_txbuf,"AT+CWJAP_CUR=\"%s\",\"%s\"\r\n",ssid,pswd);  
//	HAL_UART_Transmit(&huart1,usart1_txbuf,39,50);
//	
////	HAL_UART_Receive(&huart1,usart1_rxbuf,strlen(usart1_rxbuf),0xffff);WIFI_delay_us(100);
////	
////	LCD_ShowString(30,90,200,16,16,(uint8_t*)"ATOM@ALIENTEK");
////	LCD_ShowString(30,110,200,16,16,usart1_rxbuf);
////	
////	if(strcmp((char*)usart1_rxbuf,"OK \r\n") == 0){user_main_info("OK��\r\n");}
////	else{user_main_error("ERROR��\r\n");}
//}


//�������ƣ�2�ַ����ȽϺ���
////������string1���Ƚ��ַ���  string2��׼�ַ��� count�Ƚϳ���
////����ֵ��2�ַ�����ֵ
//uint8_t my_strncmp(uint8_t *string1,uint8_t *string2,size_t count)
//{
//	uint8_t res,k=1;
//	while(*string1!='\0'&&*string2!='\0'&&k<=count)
//	{
//		
//		k++;
//		if(*string1==*string2)
//		{
//      string1++;
//      string2++;     
//		}
//		else    break;
//	}
//  res=*string1-*string2;
//  return res;
//}



////==========================================================
////	�������ƣ�	ESP8266_Clear
////
////	�������ܣ�	��ջ���
////
////	��ڲ�����	��
////
////	���ز�����	��
////
////	˵����		
////==========================================================
//void ESP8266_Clear(void)
//{

//	memset(usart1_rxbuf, 0, sizeof(usart1_rxbuf));
//	esp8266_cnt = 0;

//}

////==========================================================
////	�������ƣ�	ESP8266_WaitRecive
////
////	�������ܣ�	�ȴ��������
////
////	��ڲ�����	��
////
////	���ز�����	REV_OK-�������		REV_WAIT-���ճ�ʱδ���
////
////	˵����		ѭ�����ü���Ƿ�������
////==========================================================
//_Bool ESP8266_WaitRecive(void)
//{
//	esp8266_cntPre = esp8266_cnt;
//	
//	if(esp8266_cnt == 0) 							//������ռ���Ϊ0 ��˵��û�д��ڽ��������У�����ֱ����������������
//		return REV_WAIT;
//		
//	if(esp8266_cnt == esp8266_cntPre)				//�����һ�ε�ֵ�������ͬ����˵���������
//	{
//		esp8266_cnt = 0;							//��0���ռ���
//			
//		return REV_OK;								//���ؽ�����ɱ�־
//	}
//		
//						//��Ϊ��ͬ
//	
//	return REV_WAIT;								//���ؽ���δ��ɱ�־

//}


////==========================================================
////	�������ƣ�	ESP8266_SendCmd
////
////	�������ܣ�	��������
////
////	��ڲ�����	cmd������
////				res����Ҫ���ķ���ָ��
////
////	���ز�����	0-�ɹ�	1-ʧ��
////
////	˵����		
////==========================================================
//_Bool ESP8266_SendCmd(char *usart1_txbuf, char *res)
//{
//	
//	unsigned char timeOut = 200;

//	HAL_UART_Transmit(&huart1,(unsigned char *)usart1_txbuf, strlen(usart1_txbuf), 0xffff);
//	
//	LCD_ShowString(30,110,500,16,16,usart1_txbuf);
//	ESP8266_Clear();//��ջ���	
//			
////	delay_ms(10);
////	return 0;
//	
//}

////==========================================================
////	�������ƣ�	ESP8266_SendData
////
////	�������ܣ�	��������
////
////	��ڲ�����	data������
////				len������
////
////	���ز�����	��
////
////	˵����		
////==========================================================
//void ESP8266_SendData(unsigned char *data, unsigned short len)
//{

//	char cmdBuf[32];
//	
//	ESP8266_Clear();								//��ս��ջ���
//	sprintf(cmdBuf, "AT+CIPSEND=%d\r\n", len);		//��������
//	if(!ESP8266_SendCmd(cmdBuf, ">"))				//�յ���>��ʱ���Է�������
//	{
//		HAL_UART_Transmit(&huart1,(unsigned char *)usart1_txbuf, strlen(usart1_txbuf), 0xffff);
//	}

//}
//unsigned char *ESP8266_GetIPD(unsigned short timeOut)
//{

//	char *ptrIPD = NULL;
//	
//	do
//	{
//		if(ESP8266_WaitRecive() == REV_OK)										//����������
//		{
//			UsartPrintf(&huart6, "%s\r\n",esp8266_buf);
//			ptrIPD = strstr((char *)esp8266_buf, "IPD,");				//������IPD��ͷ
//			if(ptrIPD == NULL)																	//���û�ҵ���������IPDͷ���ӳ٣�������Ҫ�ȴ�һ�ᣬ�����ᳬ���趨��ʱ��
//			{
//				//UsartPrintf(&huart1, "\"IPD\" not found\r\n");
//			}
//			else
//			{
//				ptrIPD = strchr(ptrIPD, ':');							//�ҵ�':'
//				if(ptrIPD != NULL)
//				{
//					ptrIPD++;
//					return (unsigned char *)(ptrIPD);
//				}
//				else
//					return NULL;
//				
//			}
//		}
//		
//		HAL_Delay(5);																//��ʱ�ȴ�
//	} while(timeOut--);
//	
//	return NULL;																	//��ʱ��δ�ҵ������ؿ�ָ��
//		ipd_rx = ESP8266_GetIPD();
//		if(ipd_rx.len>0)
//		{
//			if(strstr((char *)ipd_rx.IPD_buff, "LED_ON"))
//			{
//				user_main_info("led_on\r\n");
//				HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_SET);
//				ipd_rx.len = 0;
//				ipd_rx.IPD_buff = NULL;
//			}
//			if(strstr((char *)ipd_rx.IPD_buff, "LED_OFF"))
//			{
//				user_main_info("led_off\r\n");
//				HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_RESET);
//				ipd_rx.len = 0;
//				ipd_rx.IPD_buff = NULL;
//			}
//		}
//}

////==========================================================
////	�������ƣ�	ESP8266_GetIPD
////
////	�������ܣ�	��ȡƽ̨���ص�����
////
////	��ڲ�����	�ȴ���ʱ��(����10ms)
////
////	���ز�����	ƽ̨���ص�ԭʼ����
////
////	˵����		��ͬ�����豸���صĸ�ʽ��ͬ����Ҫȥ����
////				��ESP8266�ķ��ظ�ʽΪ	"+IPD,x:yyy"	x�������ݳ��ȣ�yyy����������
////==========================================================
//unsigned char *ESP8266_GetIPD(unsigned short timeOut)
//{

//	char *ptrIPD = NULL;
//	
//	do
//	{
//		if(ESP8266_WaitRecive() == REV_OK)								//����������
//		{
//			ptrIPD = strstr((char *)usart1_rxbuf, "IPD,");				//������IPD��ͷ
//			if(ptrIPD == NULL)											//���û�ҵ���������IPDͷ���ӳ٣�������Ҫ�ȴ�һ�ᣬ�����ᳬ���趨��ʱ��
//			{
//				//DEBUG_LOG("\"IPD\" not found\r\n");
//			}
//			else
//			{
//				ptrIPD = strchr(ptrIPD, ':');							//�ҵ�':'
//				if(ptrIPD != NULL)
//				{
//					ptrIPD++;
//					return (unsigned char *)(ptrIPD);
//				}
//				else
//					return NULL;
//				
//			}
//		}
//		delay_ms(5);
//		timeOut--;	//��ʱ�ȴ�
//	} while(timeOut > 0);
//	
//	return NULL;														//��ʱ��δ�ҵ������ؿ�ָ��

//}

////==========================================================
////	�������ƣ�	ESP8266_Init
////
////	�������ܣ�	��ʼ��ESP8266
////
////	��ڲ�����	��
////
////	���ز�����	��
////
////	˵����		
////==========================================================
//void ESP8266_Init(void)
//{
//	
//	ESP8266_Clear();
//	
//	user_main_debug("0. AT - ����MCU-8266ͨѶ");
//	ESP8266_SendCmd("AT\r\n", "OK");
//	delay_ms(500);
//	
//	user_main_debug("1. AT+RST - ��λ8266");
//	ESP8266_SendCmd("AT+RST\r\n", "");
//	delay_ms(500);
//	
//	ESP8266_SendCmd("AT+CIPCLOSE\r\n", "");
//	delay_ms(500);
//	
//	user_main_debug("2. AT+CWMODE=1,1 - ����8266����ģʽΪSTA");
//	ESP8266_SendCmd("AT+CWMODE=1\r\n", "OK");
//	delay_ms(500);
//	
//	user_main_debug("3. AT+CWDHCP=1,1 - ʹ��STAģʽ��DHCP");
//	ESP8266_SendCmd("AT+CWDHCP=1,1\r\n", "OK");
//	delay_ms(500);
//	
//	user_main_debug("4. AT+CWJAP - ����WIFI");
//	ESP8266_SendCmd(ESP8266_WIFI_INFO, "GOT IP");
//	delay_ms(500);
//	
//	user_main_debug("5. AT+CIPSTART - TCP͸������");
//	ESP8266_SendCmd(ESP8266_ONENET_INFO, "CONNECT");
//	delay_ms(500);

//	user_main_debug("6. ESP8266 Init OK - ESP8266��ʼ���ɹ�");
//	user_main_debug("ESP8266��ʼ��			[OK]");
//}

//		ESP01S_SEND_AT();
//		user_main_info("hello printf\r\n");
//		scanf("%s",val);
//		user_main_info("%s\r\n",val);
//		HAL_Delay(1000);
//		
//		if(strcmp(val,"123") == 0)
//		{
//			user_main_info("OK");
//		}
//			HAL_UART_Transmit(&huart1,(uint8_t*)"AT SUCCESS",10,0XFFFF);
		
//		dataPtr = ESP8266_GetIPD(0);
//		if(dataPtr != NULL)
//		{
//			Beep_Off;//�رշ�����
//			HAL_Delay(10000);//��ʱ
//		}
//		else if(dataPtr == NULL)
//		{
//			Beep_On;//�򿪷�����
//		}

//		sprintf((char*)check_str1,"%d,1#",LEN+2);
//		sprintf((char*)check_str2,"%d,2#",LEN+2);
//		if(strcmp((char*)dataPtr,(char*)check_str1) == 0)
//		{
//			Beep_On;//�򿪷�����
//			for(int i=0;i<10;i++)
//			{
//				HAL_Delay(1000);//��ʱ
//			}
//		}
//		else if(strcmp((char*)dataPtr,(char*)check_str2) == 0)
//		{
//			Beep_Off;//�رշ�����
//			for(int i=0;i<10;i++)
//			{
//				HAL_Delay(1000);//��ʱ
//			}
//		}
//		else{}
