#ifndef __MYRTC_H
#define __MYRTC_H
extern uint16_t MyRTC_Time[];//数组外部声明不要赋值和定义长度
void MyRTC_Init(void);
void MyRTC_SetTime(void);
void MyRTC_ReadTime(void);

#endif
