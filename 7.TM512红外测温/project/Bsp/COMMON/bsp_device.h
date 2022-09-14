#ifndef _BSP_DEVICE_H_
#define _BSP_DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "LCD/bsp_lcd.h"				//LCD屏幕
#include "DHT11/bsp_dht11.h"		//DHT11温湿度传感器
#include "INFO/bsp_info.h"			//USART串口打印重定向
#include "BEEP/bsp_beep.h"			//BEEP蜂鸣器
#include "ESP/bsp_esp01s.h"			//ESP01Swifi模块
#include "MQTT/MqttKit.h"				//MQTT协议文件
#include "ONENET/onenet.h"			//ONENET接入API

#endif

