#include "INFO/bsp_info.h"
#include "main.h"


/*****************************************************************
ʹ��UART6�������ݷ���

��ֲ�������
���ܣ��ض���printf()

*****************************************************************/

int fputc(int ch,FILE *f)
{
    uint8_t temp[1]={ch};
    HAL_UART_Transmit(&huart6,temp,1,2);
	return 0;
}

