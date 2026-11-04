#ifndef __MYSPI_H
#define __MYSPI_H

void MySPI_Init(void);
void MySPI_Start(void);//起始信号
void MySPI_Stop(void);//终止信号
uint8_t MySPI_SwapByte(uint8_t ByteSend);//字节交换时序


#endif













