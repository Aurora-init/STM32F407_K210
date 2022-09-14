/**
	*	文件名： 	onenet.c
	*
	*	作者： 		张继瑞
	*
	*	日期： 		2017-05-08
	*
	*	版本： 		V1.1
	*
	*	说明： 		与onenet平台的数据交互接口层
	*
	*	修改记录：	V1.0：协议封装、返回判断都在同一个文件，并且不同协议接口不同。
	*							V1.1：提供统一接口供应用层使用，根据不同协议文件来封装协议相关的内容。
**/

//网络设备
#include "ESP/bsp_esp01s.h"
//协议文件
#include "ONENET/onenet.h"
#include "MQTT/mqttkit.h"
//硬件驱动
#include "usart.h"

//外设宏包
#include "COMMON/bsp_common.h"	//STD基本宏包
#include "DHT11/bsp_dht11.h"		//DHT11温湿度传感器
#include "BEEP/bsp_beep.h"			//BEEP蜂鸣器

//产品ID
#define PROID		"535146"
//设备ID
#define DEVID		"970751245"
//鉴权信息
#define AUTH_INFO	"123" 

extern unsigned char esp8266_buf[128];
uint8_t flag_change = 0;

//==========================================================
//	函数名称：	OneNet_DevLink
//
//	函数功能：	与onenet创建连接
//
//	入口参数：	无
//
//	返回参数：	1-成功	0-失败
//
//	说明：		与onenet平台建立连接
//==========================================================
_Bool OneNet_DevLink(void)
{
	//协议包
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};					

	unsigned char *dataPtr;
	
	_Bool status = 1;
	
	UsartPrintf(&huart6, "OneNet_DevLink\r\n""PROID: %s,	AUIF: %s,	DEVID:%s\r\n" , PROID, AUTH_INFO, DEVID);
	
	if(MQTT_PacketConnect(PROID, AUTH_INFO, DEVID, 256, 0, MQTT_QOS_LEVEL0, NULL, NULL, 0, &mqttPacket) == 0)
	{
		//上传平台
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);			
		UsartPrintf(&huart6, "连接上传完成\r\n等待响应\r\n");
		//等待平台响应
		dataPtr = ESP8266_GetIPD(250);														
		if(dataPtr != NULL)
		{
			UsartPrintf(&huart6, "平台已响应\r\n");
			if(MQTT_UnPacketRecv(dataPtr) == MQTT_PKT_CONNACK)
			{
				switch(MQTT_UnPacketConnectAck(dataPtr))
				{
					case 0:UsartPrintf(&huart6, "Tips:	连接成功\r\n");status = 0;break;
					
					case 1:UsartPrintf(&huart6, "WARN:	连接失败：协议错误\r\n");break;
					case 2:UsartPrintf(&huart6, "WARN:	连接失败：非法的clientid\r\n");break;
					case 3:UsartPrintf(&huart6, "WARN:	连接失败：服务器失败\r\n");break;
					case 4:UsartPrintf(&huart6, "WARN:	连接失败：用户名或密码错误\r\n");break;
					case 5:UsartPrintf(&huart6, "WARN:	连接失败：非法链接(比如token非法)\r\n");break;
					
					default:UsartPrintf(&huart6, "ERR:	连接失败：未知错误\r\n");break;
				}
			}
		}
		//删包
		MQTT_DeleteBuffer(&mqttPacket);								
	}
	else
	{	UsartPrintf(&huart6, "平台无响应\r\n");
		UsartPrintf(&huart6, "WARN:	MQTT_PacketConnect Failed\r\n");
	}
	return status;
	
}

//==========================================================
//	函数名称：	OneNet_Subscribe
//
//	函数功能：	订阅
//
//	入口参数：	topics：订阅的topic
//				topic_cnt：topic个数
//
//	返回参数：	SEND_TYPE_OK-成功	SEND_TYPE_SUBSCRIBE-需要重发
//
//	说明：		
//==========================================================
void OneNet_Subscribe(const char *topics[], unsigned char topic_cnt)
{
	
	unsigned char i = 0;
	//协议包
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};							
	
	for(; i < topic_cnt; i++)
		UsartPrintf(&huart6, "Subscribe Topic: %s\r\n", topics[i]);
	
	if(MQTT_PacketSubscribe(MQTT_SUBSCRIBE_ID, MQTT_QOS_LEVEL0, topics, topic_cnt, &mqttPacket) == 0)
	{
		//向平台发送订阅请求
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);					
		//删包
		MQTT_DeleteBuffer(&mqttPacket);											
	}

}

//==========================================================
//	函数名称：	OneNet_Publish
//
//	函数功能：	发布消息
//
//	入口参数：	topic：发布的主题
//				msg：消息内容
//
//	返回参数：	SEND_TYPE_OK-成功	SEND_TYPE_PUBLISH-需要重送
//
//	说明：		
//==========================================================
void OneNet_Publish(const char *topic, const char *msg)
{
	//协议包
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};							
	
	UsartPrintf(&huart6, "Publish Topic: %s, Msg: %s\r\n", topic, msg);
	
	if(MQTT_PacketPublish(MQTT_PUBLISH_ID, topic, msg, strlen(msg), MQTT_QOS_LEVEL0, 0, 1, &mqttPacket) == 0)
	{
		//向平台发送订阅请求
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);					
		//删包
		MQTT_DeleteBuffer(&mqttPacket);											
	}

}
//这个函数是用来打包数据信息的
unsigned char OneNet_FillBuf(char *buf)
{
	char text[16];
	DHT11_Data_TypeDef DHT11_Data;
	DHT11_ReadData(&DHT11_Data);
	
	user_main_info("\r\n湿度为%d.%d ％RH,温度为%d.%d ℃\r\n",DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
	//初始化数据流BUFF
	memset(text, 0, sizeof(text));
	
	//温度Temp数据流
	if(flag_change == 1)
	{
		user_main_info("\r\n本次输出温度\r\n");
		strcpy(buf, "{");
		
		memset(text, 0, sizeof(text));
		sprintf(text, "\"Temp\":%d.%d",DHT11_Data.temp_int,DHT11_Data.temp_deci);
		strcat(buf, text);
		
		strcat(buf, "}");
		flag_change = 2;
	}
	
	//湿度Humi数据流
	if(flag_change == 0)
	{
		user_main_info("\r\n本次输出湿度\r\n");
		strcpy(buf, "{");
	
		memset(text, 0, sizeof(text));
		sprintf(text, "\"Humi\":%d.%d",DHT11_Data.humi_int,DHT11_Data.humi_deci);
		strcat(buf, text);
		
		strcat(buf, "}");
		flag_change = 1;
	}
	//回到开头
	if(flag_change == 2)
	{
		flag_change = 0;
	}
	
	return strlen(buf);
}

//==========================================================
//	函数名称：	OneNet_SendData
//
//	函数功能：	上传数据到平台
//
//	入口参数：	type：发送数据的格式
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_SendData(void)
{
	//协议包
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};												
	
	char buf[128];
	
	short body_len = 0, i = 0;
	
	UsartPrintf(&huart6, "Tips:	OneNet_SendData-MQTT\r\n");
	
	memset(buf, 0, sizeof(buf));
	//获取当前需要发送的数据流的总长度
	body_len = OneNet_FillBuf(buf);																	
	
	if(body_len)
	{
		//封包
		if(MQTT_PacketSaveData(DEVID, body_len, NULL, 3, &mqttPacket) == 0)							
		{
			for(; i < body_len; i++)
				mqttPacket._data[mqttPacket._len++] = buf[i];
			//上传数据到平台
			ESP8266_SendData(mqttPacket._data, mqttPacket._len);									
			UsartPrintf(&huart6, "Send %d Bytes\r\n", mqttPacket._len);
			//删包
			MQTT_DeleteBuffer(&mqttPacket);															
		}
		else
			UsartPrintf(&huart6, "WARN:	EDP_NewBuffer Failed\r\n");
	}
}

//==========================================================
//	函数名称：	OneNet_RevPro
//
//	函数功能：	平台返回数据检测
//
//	入口参数：	dataPtr：平台返回的数据
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_RevPro(unsigned char *cmd)
{
	//协议包
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};								
	
	char *req_payload = NULL;
	char *cmdid_topic = NULL;
	
	unsigned short req_len = 0;
	
	unsigned char type = 0;
	
	short result = 0;
	
	type = MQTT_UnPacketRecv(cmd);
	switch(type)
	{
		//命令下发
		case MQTT_PKT_CMD:															
			
			result = MQTT_UnPacketCmd(cmd, &cmdid_topic, &req_payload, &req_len);//解出topic和消息体
			if(result == 0)
			{
				UsartPrintf(&huart6, "cmdid: %s, req: %s, req_len: %d\r\n", cmdid_topic, req_payload, req_len);
				if(MQTT_PacketCmdResp(cmdid_topic, req_payload, &mqttPacket) == 0)//命令回复组包
				{
					UsartPrintf(&huart6, "Tips:	Send CmdResp\r\n");
					
					ESP8266_SendData(mqttPacket._data, mqttPacket._len);//回复命令
					MQTT_DeleteBuffer(&mqttPacket);//删包
				}
			}
		break;
			
		case MQTT_PKT_PUBACK://发送Publish消息，平台回复的Ack
		
			if(MQTT_UnPacketPublishAck(cmd) == 0)
				UsartPrintf(&huart6, "Tips:	MQTT Publish Send OK\r\n");
			
		break;
		
		default:
			result = -1;
		break;
	}
	
	ESP8266_Clear();//清空缓存
	
	if(result == -1)
		return;

	if(strstr((char *)req_payload, "OPEN"))//搜索"OPEN"
	{
			UsartPrintf(&huart6, "Blue_Led_ON\r\n");
			Beep_On;

	}
	else if(strstr((char *)req_payload, "CLOED"))//搜索"CLOED"
	{
			UsartPrintf(&huart6, "Blue_Led_OFF\r\n");
			Beep_Off;
	}
	if(type == MQTT_PKT_CMD || type == MQTT_PKT_PUBLISH)
	{
		MQTT_FreeBuffer(cmdid_topic);
		MQTT_FreeBuffer(req_payload);
	}

}
