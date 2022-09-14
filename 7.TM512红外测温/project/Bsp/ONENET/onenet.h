#ifndef _ONENET_H_
#define _ONENET_H_


extern unsigned char WARMING_FLAG;
extern int Body_int_x;
extern int Body_deci_x;

_Bool OneNet_DevLink(void);

void OneNet_Subscribe(const char *topics[], unsigned char topic_cnt);

void OneNet_Publish(const char *topic, const char *msg);

void OneNet_RevPro(unsigned char *cmd);

void OneNet_SendData(void);

#endif
