#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[4];

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE );//打开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE );
		RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA1,ENABLE);//打开DMA时钟在AHB总线上
	RCC_ADCCLKConfig(RCC_PCLK2_Div6 );//设置时钟分频72/6=12MHZ
	
	GPIO_InitTypeDef GPIO_InitStructre;//定义GPIO结构体
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_AIN;//模拟输入模式
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);//设置规则组通道
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);//设置规则组通道
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);//设置规则组通道
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);//设置规则组通道

	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;//ADC模式
	ADC_InitStructure.ADC_ScanConvMode=ENABLE;//指定扫描模式（多通道）还是非扫描模式（单通道）
	ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;//转换模式连续还是单次
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//外部触发源选择
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//数据对齐方式 左对齐或者右对齐
	ADC_InitStructure.ADC_NbrOfChannel=4;//通道数目
	
	ADC_Init(ADC1,&ADC_InitStructure);//用结构体初始化ADC
	

	
	

	
	DMA_InitTypeDef DMA_InitStructure;//定义DMA结构体
	DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t )&ADC1->DR;//外设 起始地址
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;//外设 数据宽度
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable ;//外设 是否自增
	DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t )AD_Value;//存储器 起始地址
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord  ;//存储器 数据宽度
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;//存储器 是否自增
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;//传输方向
	DMA_InitStructure.DMA_BufferSize=4;//缓冲区大小
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular ;//自动重装器模式
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;//硬件触发 软件触发
	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;//优先级
	
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);//DMA1的通道1 初始化
	
	DMA_Cmd(DMA1_Channel1,ENABLE);//暂时不转运
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);//打开ADC
	
	ADC_ResetCalibration(ADC1);//等待复位校准
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);//标志位判断
	ADC_StartCalibration(ADC1);//启动校准
	while(ADC_GetCalibrationStatus(ADC1) ==SET);//标志位判断
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//软件触发转换

}


//void AD_GetValue(void)
//{
//	DMA_Cmd(DMA1_Channel1,DISABLE);
//	DMA_SetCurrDataCounter(DMA1_Channel1,4);//转运数据
//	DMA_Cmd(DMA1_Channel1,ENABLE);
//	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//软件触发转换

//	
//	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);//转运完成标志位
//	DMA_ClearFlag(DMA1_FLAG_TC1);//清除标志位
//}
















