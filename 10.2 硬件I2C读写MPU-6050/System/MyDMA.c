#include "stm32f10x.h"                  // Device header

uint16_t MyDMA_Size;

void MyDMA_Init(uint32_t AddrA , uint32_t AddrB,uint16_t Size)
{
	MyDMA_Size=Size;
	
	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA1,ENABLE);//打开DMA时钟在AHB总线上
	
	DMA_InitTypeDef DMA_InitStructure;//定义DMA结构体
	DMA_InitStructure.DMA_PeripheralBaseAddr=AddrA;//外设 起始地址
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;//外设 数据宽度
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Enable ;//外设 是否自增
	DMA_InitStructure.DMA_MemoryBaseAddr=AddrB;//存储器 起始地址
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte  ;//存储器 数据宽度
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;//存储器 是否自增
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;//传输方向
	DMA_InitStructure.DMA_BufferSize=Size;//缓冲区大小
	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;//自动重装器模式
	DMA_InitStructure.DMA_M2M=DMA_M2M_Enable;//硬件触发 软件触发
	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;//优先级
	
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);//DMA1的通道1 初始化
	
	DMA_Cmd(DMA1_Channel1,DISABLE);//暂时不转运
}

void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1,MyDMA_Size);//转运数据
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);//转运完成标志位
	DMA_ClearFlag(DMA1_FLAG_TC1);//清除标志位
}










