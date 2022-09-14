#include "INFO/bsp_info.h"
#include "main.h"


/*****************************************************************
使用UART6进行数据发送

移植：衾许°
功能：重定向printf()

*****************************************************************/

int fputc(int ch,FILE *f)
{
    uint8_t temp[1]={ch};
    HAL_UART_Transmit(&huart6,temp,1,2);
	return 0;
}

