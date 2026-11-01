#ifndef __MYI2C_H
#define __MYI2C_H

void MyI2C_Init(void);
void MyI2C_Start(void);//起始条件
void MyI2C_Stop(void);//终止条件
void MyI2C_SendByte(uint8_t Byte);//主机发送一个字节
uint8_t MyI2C_ReceiveByte(void);//主机接收一个字节
void MyI2C_SendAck(uint8_t ACKBit);//主机发送应答
uint8_t MyI2C_ReceiveAck(void);//主机接收应答

#endif
