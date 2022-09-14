//这个example.c主要用于放置我一些废弃后的代码，防止到时候要参考的时候找不到
//  MX_GPIO_Init();							//目前已用BEEP与SR501
//  MX_FSMC_Init();							//LCD驱动
//  MX_TIM3_Init();							//LCD专属us级延时
//  MX_TIM5_Init();							//DHT11专属us级延时
//  MX_TIM4_Init();							//ESP01S专属us级延时
//  MX_USART6_UART_Init();			//用于串口重定向
//  MX_USART1_UART_Init();			//ESP01Sat指令发送串口


//LCD显示例程
//		LCD_ShowString(30,40,250,24,24,(uint8_t*)"Explorer STM32F4");	
//		LCD_ShowString(30,70,200,16,16,(uint8_t*)"TFTLCD TEST");
//		LCD_ShowString(30,90,200,16,16,(uint8_t*)"ATOM@ALIENTEK");
//		sprintf((char*)lcd_std,"LCD ID:%04X",lcddev.id);
//		LCD_ShowString(30,110,200,16,16,lcd_std);
//		sprintf((char*)lcd_std,"KEY:%04d",key_val);
//		LCD_ShowString(30,130,200,12,12,lcd_std);  
		
		//DHT11例程
//		if(DHT11_ReadData(&DHT11_Data))
//		{	
//			user_main_info("\r\nDHT11 Read Success!\r\n");
//			
//			sprintf(uart_std,"\r\n湿度为%d.%d ％RH\r\n", DHT11_Data.humi_int,DHT11_Data.humi_deci);
//			HAL_UART_Transmit(&huart6,(uint8_t*)uart_std,21,0XFFFF);
//			
//			sprintf(uart_std,"\r\n温度为%d.%d  ℃  \r\n", DHT11_Data.temp_int,DHT11_Data.temp_deci);
//			HAL_UART_Transmit(&huart6,(uint8_t*)uart_std,21,0XFFFF);
//		}
//		else
//		{
//			user_main_error("Read DHT11 ERROR!\r\n");
//		}
//		HAL_Delay(3000);

		//BEEP例程
//		
//		for(int i=0;i<10;i++)
//		{
//			HAL_Delay(1000);//延时
//		}
//		Beep_Off;//关闭蜂鸣器
//		for(int i=0;i<10;i++)
//		{
//			HAL_Delay(1000);//延时
//		}

		//SR501人体红外传感器例程
//		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_10) == 1)
//		{
//			
//			printf("有人\r\n");
//			HAL_Delay(100);
//		}
//		else  
//		{
//			printf("没人\r\n");
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
////	if(strcmp((char*)usart1_rxbuf,"OK \r\n") == 0){user_main_info("OK！\r\n");}
////	else{user_main_error("ERROR！\r\n");}
//}


//函数名称：2字符串比较函数
////参数：string1待比较字符串  string2标准字符串 count比较长度
////返回值：2字符串差值
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
////	函数名称：	ESP8266_Clear
////
////	函数功能：	清空缓存
////
////	入口参数：	无
////
////	返回参数：	无
////
////	说明：		
////==========================================================
//void ESP8266_Clear(void)
//{

//	memset(usart1_rxbuf, 0, sizeof(usart1_rxbuf));
//	esp8266_cnt = 0;

//}

////==========================================================
////	函数名称：	ESP8266_WaitRecive
////
////	函数功能：	等待接收完成
////
////	入口参数：	无
////
////	返回参数：	REV_OK-接收完成		REV_WAIT-接收超时未完成
////
////	说明：		循环调用检测是否接收完成
////==========================================================
//_Bool ESP8266_WaitRecive(void)
//{
//	esp8266_cntPre = esp8266_cnt;
//	
//	if(esp8266_cnt == 0) 							//如果接收计数为0 则说明没有处于接收数据中，所以直接跳出，结束函数
//		return REV_WAIT;
//		
//	if(esp8266_cnt == esp8266_cntPre)				//如果上一次的值和这次相同，则说明接收完毕
//	{
//		esp8266_cnt = 0;							//清0接收计数
//			
//		return REV_OK;								//返回接收完成标志
//	}
//		
//						//置为相同
//	
//	return REV_WAIT;								//返回接收未完成标志

//}


////==========================================================
////	函数名称：	ESP8266_SendCmd
////
////	函数功能：	发送命令
////
////	入口参数：	cmd：命令
////				res：需要检查的返回指令
////
////	返回参数：	0-成功	1-失败
////
////	说明：		
////==========================================================
//_Bool ESP8266_SendCmd(char *usart1_txbuf, char *res)
//{
//	
//	unsigned char timeOut = 200;

//	HAL_UART_Transmit(&huart1,(unsigned char *)usart1_txbuf, strlen(usart1_txbuf), 0xffff);
//	
//	LCD_ShowString(30,110,500,16,16,usart1_txbuf);
//	ESP8266_Clear();//清空缓存	
//			
////	delay_ms(10);
////	return 0;
//	
//}

////==========================================================
////	函数名称：	ESP8266_SendData
////
////	函数功能：	发送数据
////
////	入口参数：	data：数据
////				len：长度
////
////	返回参数：	无
////
////	说明：		
////==========================================================
//void ESP8266_SendData(unsigned char *data, unsigned short len)
//{

//	char cmdBuf[32];
//	
//	ESP8266_Clear();								//清空接收缓存
//	sprintf(cmdBuf, "AT+CIPSEND=%d\r\n", len);		//发送命令
//	if(!ESP8266_SendCmd(cmdBuf, ">"))				//收到‘>’时可以发送数据
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
//		if(ESP8266_WaitRecive() == REV_OK)										//如果接收完成
//		{
//			UsartPrintf(&huart6, "%s\r\n",esp8266_buf);
//			ptrIPD = strstr((char *)esp8266_buf, "IPD,");				//搜索“IPD”头
//			if(ptrIPD == NULL)																	//如果没找到，可能是IPD头的延迟，还是需要等待一会，但不会超过设定的时间
//			{
//				//UsartPrintf(&huart1, "\"IPD\" not found\r\n");
//			}
//			else
//			{
//				ptrIPD = strchr(ptrIPD, ':');							//找到':'
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
//		HAL_Delay(5);																//延时等待
//	} while(timeOut--);
//	
//	return NULL;																	//超时还未找到，返回空指针
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
////	函数名称：	ESP8266_GetIPD
////
////	函数功能：	获取平台返回的数据
////
////	入口参数：	等待的时间(乘以10ms)
////
////	返回参数：	平台返回的原始数据
////
////	说明：		不同网络设备返回的格式不同，需要去调试
////				如ESP8266的返回格式为	"+IPD,x:yyy"	x代表数据长度，yyy是数据内容
////==========================================================
//unsigned char *ESP8266_GetIPD(unsigned short timeOut)
//{

//	char *ptrIPD = NULL;
//	
//	do
//	{
//		if(ESP8266_WaitRecive() == REV_OK)								//如果接收完成
//		{
//			ptrIPD = strstr((char *)usart1_rxbuf, "IPD,");				//搜索“IPD”头
//			if(ptrIPD == NULL)											//如果没找到，可能是IPD头的延迟，还是需要等待一会，但不会超过设定的时间
//			{
//				//DEBUG_LOG("\"IPD\" not found\r\n");
//			}
//			else
//			{
//				ptrIPD = strchr(ptrIPD, ':');							//找到':'
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
//		timeOut--;	//延时等待
//	} while(timeOut > 0);
//	
//	return NULL;														//超时还未找到，返回空指针

//}

////==========================================================
////	函数名称：	ESP8266_Init
////
////	函数功能：	初始化ESP8266
////
////	入口参数：	无
////
////	返回参数：	无
////
////	说明：		
////==========================================================
//void ESP8266_Init(void)
//{
//	
//	ESP8266_Clear();
//	
//	user_main_debug("0. AT - 测试MCU-8266通讯");
//	ESP8266_SendCmd("AT\r\n", "OK");
//	delay_ms(500);
//	
//	user_main_debug("1. AT+RST - 软复位8266");
//	ESP8266_SendCmd("AT+RST\r\n", "");
//	delay_ms(500);
//	
//	ESP8266_SendCmd("AT+CIPCLOSE\r\n", "");
//	delay_ms(500);
//	
//	user_main_debug("2. AT+CWMODE=1,1 - 设置8266工作模式为STA");
//	ESP8266_SendCmd("AT+CWMODE=1\r\n", "OK");
//	delay_ms(500);
//	
//	user_main_debug("3. AT+CWDHCP=1,1 - 使能STA模式下DHCP");
//	ESP8266_SendCmd("AT+CWDHCP=1,1\r\n", "OK");
//	delay_ms(500);
//	
//	user_main_debug("4. AT+CWJAP - 连接WIFI");
//	ESP8266_SendCmd(ESP8266_WIFI_INFO, "GOT IP");
//	delay_ms(500);
//	
//	user_main_debug("5. AT+CIPSTART - TCP透传开启");
//	ESP8266_SendCmd(ESP8266_ONENET_INFO, "CONNECT");
//	delay_ms(500);

//	user_main_debug("6. ESP8266 Init OK - ESP8266初始化成功");
//	user_main_debug("ESP8266初始化			[OK]");
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
//			Beep_Off;//关闭蜂鸣器
//			HAL_Delay(10000);//延时
//		}
//		else if(dataPtr == NULL)
//		{
//			Beep_On;//打开蜂鸣器
//		}

//		sprintf((char*)check_str1,"%d,1#",LEN+2);
//		sprintf((char*)check_str2,"%d,2#",LEN+2);
//		if(strcmp((char*)dataPtr,(char*)check_str1) == 0)
//		{
//			Beep_On;//打开蜂鸣器
//			for(int i=0;i<10;i++)
//			{
//				HAL_Delay(1000);//延时
//			}
//		}
//		else if(strcmp((char*)dataPtr,(char*)check_str2) == 0)
//		{
//			Beep_Off;//关闭蜂鸣器
//			for(int i=0;i<10;i++)
//			{
//				HAL_Delay(1000);//延时
//			}
//		}
//		else{}
