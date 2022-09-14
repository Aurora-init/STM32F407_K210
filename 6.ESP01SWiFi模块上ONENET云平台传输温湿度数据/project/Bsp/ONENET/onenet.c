/**
	*	�ļ����� 	onenet.c
	*
	*	���ߣ� 		�ż���
	*
	*	���ڣ� 		2017-05-08
	*
	*	�汾�� 		V1.1
	*
	*	˵���� 		��onenetƽ̨�����ݽ����ӿڲ�
	*
	*	�޸ļ�¼��	V1.0��Э���װ�������ж϶���ͬһ���ļ������Ҳ�ͬЭ��ӿڲ�ͬ��
	*							V1.1���ṩͳһ�ӿڹ�Ӧ�ò�ʹ�ã����ݲ�ͬЭ���ļ�����װЭ����ص����ݡ�
**/

//�����豸
#include "ESP/bsp_esp01s.h"
//Э���ļ�
#include "ONENET/onenet.h"
#include "MQTT/mqttkit.h"
//Ӳ������
#include "usart.h"

//������
#include "COMMON/bsp_common.h"	//STD�������
#include "DHT11/bsp_dht11.h"		//DHT11��ʪ�ȴ�����
#include "BEEP/bsp_beep.h"			//BEEP������

//��ƷID
#define PROID		"535146"
//�豸ID
#define DEVID		"970751245"
//��Ȩ��Ϣ
#define AUTH_INFO	"123" 

extern unsigned char esp8266_buf[128];
uint8_t flag_change = 0;

//==========================================================
//	�������ƣ�	OneNet_DevLink
//
//	�������ܣ�	��onenet��������
//
//	��ڲ�����	��
//
//	���ز�����	1-�ɹ�	0-ʧ��
//
//	˵����		��onenetƽ̨��������
//==========================================================
_Bool OneNet_DevLink(void)
{
	//Э���
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};					

	unsigned char *dataPtr;
	
	_Bool status = 1;
	
	UsartPrintf(&huart6, "OneNet_DevLink\r\n""PROID: %s,	AUIF: %s,	DEVID:%s\r\n" , PROID, AUTH_INFO, DEVID);
	
	if(MQTT_PacketConnect(PROID, AUTH_INFO, DEVID, 256, 0, MQTT_QOS_LEVEL0, NULL, NULL, 0, &mqttPacket) == 0)
	{
		//�ϴ�ƽ̨
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);			
		UsartPrintf(&huart6, "�����ϴ����\r\n�ȴ���Ӧ\r\n");
		//�ȴ�ƽ̨��Ӧ
		dataPtr = ESP8266_GetIPD(250);														
		if(dataPtr != NULL)
		{
			UsartPrintf(&huart6, "ƽ̨����Ӧ\r\n");
			if(MQTT_UnPacketRecv(dataPtr) == MQTT_PKT_CONNACK)
			{
				switch(MQTT_UnPacketConnectAck(dataPtr))
				{
					case 0:UsartPrintf(&huart6, "Tips:	���ӳɹ�\r\n");status = 0;break;
					
					case 1:UsartPrintf(&huart6, "WARN:	����ʧ�ܣ�Э�����\r\n");break;
					case 2:UsartPrintf(&huart6, "WARN:	����ʧ�ܣ��Ƿ���clientid\r\n");break;
					case 3:UsartPrintf(&huart6, "WARN:	����ʧ�ܣ�������ʧ��\r\n");break;
					case 4:UsartPrintf(&huart6, "WARN:	����ʧ�ܣ��û������������\r\n");break;
					case 5:UsartPrintf(&huart6, "WARN:	����ʧ�ܣ��Ƿ�����(����token�Ƿ�)\r\n");break;
					
					default:UsartPrintf(&huart6, "ERR:	����ʧ�ܣ�δ֪����\r\n");break;
				}
			}
		}
		//ɾ��
		MQTT_DeleteBuffer(&mqttPacket);								
	}
	else
	{	UsartPrintf(&huart6, "ƽ̨����Ӧ\r\n");
		UsartPrintf(&huart6, "WARN:	MQTT_PacketConnect Failed\r\n");
	}
	return status;
	
}

//==========================================================
//	�������ƣ�	OneNet_Subscribe
//
//	�������ܣ�	����
//
//	��ڲ�����	topics�����ĵ�topic
//				topic_cnt��topic����
//
//	���ز�����	SEND_TYPE_OK-�ɹ�	SEND_TYPE_SUBSCRIBE-��Ҫ�ط�
//
//	˵����		
//==========================================================
void OneNet_Subscribe(const char *topics[], unsigned char topic_cnt)
{
	
	unsigned char i = 0;
	//Э���
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};							
	
	for(; i < topic_cnt; i++)
		UsartPrintf(&huart6, "Subscribe Topic: %s\r\n", topics[i]);
	
	if(MQTT_PacketSubscribe(MQTT_SUBSCRIBE_ID, MQTT_QOS_LEVEL0, topics, topic_cnt, &mqttPacket) == 0)
	{
		//��ƽ̨���Ͷ�������
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);					
		//ɾ��
		MQTT_DeleteBuffer(&mqttPacket);											
	}

}

//==========================================================
//	�������ƣ�	OneNet_Publish
//
//	�������ܣ�	������Ϣ
//
//	��ڲ�����	topic������������
//				msg����Ϣ����
//
//	���ز�����	SEND_TYPE_OK-�ɹ�	SEND_TYPE_PUBLISH-��Ҫ����
//
//	˵����		
//==========================================================
void OneNet_Publish(const char *topic, const char *msg)
{
	//Э���
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};							
	
	UsartPrintf(&huart6, "Publish Topic: %s, Msg: %s\r\n", topic, msg);
	
	if(MQTT_PacketPublish(MQTT_PUBLISH_ID, topic, msg, strlen(msg), MQTT_QOS_LEVEL0, 0, 1, &mqttPacket) == 0)
	{
		//��ƽ̨���Ͷ�������
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);					
		//ɾ��
		MQTT_DeleteBuffer(&mqttPacket);											
	}

}
//����������������������Ϣ��
unsigned char OneNet_FillBuf(char *buf)
{
	char text[16];
	DHT11_Data_TypeDef DHT11_Data;
	DHT11_ReadData(&DHT11_Data);
	
	user_main_info("\r\nʪ��Ϊ%d.%d ��RH,�¶�Ϊ%d.%d ��\r\n",DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
	//��ʼ��������BUFF
	memset(text, 0, sizeof(text));
	
	//�¶�Temp������
	if(flag_change == 1)
	{
		user_main_info("\r\n��������¶�\r\n");
		strcpy(buf, "{");
		
		memset(text, 0, sizeof(text));
		sprintf(text, "\"Temp\":%d.%d",DHT11_Data.temp_int,DHT11_Data.temp_deci);
		strcat(buf, text);
		
		strcat(buf, "}");
		flag_change = 2;
	}
	
	//ʪ��Humi������
	if(flag_change == 0)
	{
		user_main_info("\r\n�������ʪ��\r\n");
		strcpy(buf, "{");
	
		memset(text, 0, sizeof(text));
		sprintf(text, "\"Humi\":%d.%d",DHT11_Data.humi_int,DHT11_Data.humi_deci);
		strcat(buf, text);
		
		strcat(buf, "}");
		flag_change = 1;
	}
	//�ص���ͷ
	if(flag_change == 2)
	{
		flag_change = 0;
	}
	
	return strlen(buf);
}

//==========================================================
//	�������ƣ�	OneNet_SendData
//
//	�������ܣ�	�ϴ����ݵ�ƽ̨
//
//	��ڲ�����	type���������ݵĸ�ʽ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_SendData(void)
{
	//Э���
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};												
	
	char buf[128];
	
	short body_len = 0, i = 0;
	
	UsartPrintf(&huart6, "Tips:	OneNet_SendData-MQTT\r\n");
	
	memset(buf, 0, sizeof(buf));
	//��ȡ��ǰ��Ҫ���͵����������ܳ���
	body_len = OneNet_FillBuf(buf);																	
	
	if(body_len)
	{
		//���
		if(MQTT_PacketSaveData(DEVID, body_len, NULL, 3, &mqttPacket) == 0)							
		{
			for(; i < body_len; i++)
				mqttPacket._data[mqttPacket._len++] = buf[i];
			//�ϴ����ݵ�ƽ̨
			ESP8266_SendData(mqttPacket._data, mqttPacket._len);									
			UsartPrintf(&huart6, "Send %d Bytes\r\n", mqttPacket._len);
			//ɾ��
			MQTT_DeleteBuffer(&mqttPacket);															
		}
		else
			UsartPrintf(&huart6, "WARN:	EDP_NewBuffer Failed\r\n");
	}
}

//==========================================================
//	�������ƣ�	OneNet_RevPro
//
//	�������ܣ�	ƽ̨�������ݼ��
//
//	��ڲ�����	dataPtr��ƽ̨���ص�����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_RevPro(unsigned char *cmd)
{
	//Э���
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};								
	
	char *req_payload = NULL;
	char *cmdid_topic = NULL;
	
	unsigned short req_len = 0;
	
	unsigned char type = 0;
	
	short result = 0;
	
	type = MQTT_UnPacketRecv(cmd);
	switch(type)
	{
		//�����·�
		case MQTT_PKT_CMD:															
			
			result = MQTT_UnPacketCmd(cmd, &cmdid_topic, &req_payload, &req_len);//���topic����Ϣ��
			if(result == 0)
			{
				UsartPrintf(&huart6, "cmdid: %s, req: %s, req_len: %d\r\n", cmdid_topic, req_payload, req_len);
				if(MQTT_PacketCmdResp(cmdid_topic, req_payload, &mqttPacket) == 0)//����ظ����
				{
					UsartPrintf(&huart6, "Tips:	Send CmdResp\r\n");
					
					ESP8266_SendData(mqttPacket._data, mqttPacket._len);//�ظ�����
					MQTT_DeleteBuffer(&mqttPacket);//ɾ��
				}
			}
		break;
			
		case MQTT_PKT_PUBACK://����Publish��Ϣ��ƽ̨�ظ���Ack
		
			if(MQTT_UnPacketPublishAck(cmd) == 0)
				UsartPrintf(&huart6, "Tips:	MQTT Publish Send OK\r\n");
			
		break;
		
		default:
			result = -1;
		break;
	}
	
	ESP8266_Clear();//��ջ���
	
	if(result == -1)
		return;

	if(strstr((char *)req_payload, "OPEN"))//����"OPEN"
	{
			UsartPrintf(&huart6, "Blue_Led_ON\r\n");
			Beep_On;

	}
	else if(strstr((char *)req_payload, "CLOED"))//����"CLOED"
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
