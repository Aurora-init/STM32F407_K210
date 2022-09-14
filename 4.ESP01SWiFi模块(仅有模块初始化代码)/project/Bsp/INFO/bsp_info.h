#include "stdio.h"
#include "main.h"
#include "usart.h"
#include "gpio.h"

#define USER_MAIN_DEBUG

#ifdef USER_MAIN_DEBUG
#define user_main_printf(format, ...) 	printf( format "\r\n",##__VA_ARGS__)
#define user_main_info(format, ...) 		printf("【main】info:" format "\r\n",##__VA_ARGS__)
#define user_main_debug(format, ...) 		printf("【main】debug:" format "\r\n",##__VA_ARGS__)
#define user_main_error(format, ...) 		printf("【main】error:" format "\r\n",##__VA_ARGS__)
#else
#define user_main_printf(format, ...)
#define user_main_info(format, ...)
#define user_main_debug(format, ...)
#define user_main_error(format, ...)

#endif

/*例子：

user_main_info("ESP8266阿里云MQTT登陆成功！\r\n");

*/
