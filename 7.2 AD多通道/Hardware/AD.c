#include "stm32f10x.h"                  // Device header


void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE );//打开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE );
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6 );//设置时钟分频72/6=12MHZ
	
	GPIO_InitTypeDef GPIO_InitStructre;//定义GPIO结构体
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_AIN;//模拟输入模式
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);
	

	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;//ADC模式
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;//指定扫描模式（多通道）还是非扫描模式（单通道）
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;//转换模式连续还是单次
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//外部触发源选择
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//数据对齐方式 左对齐或者右对齐
	ADC_InitStructure.ADC_NbrOfChannel=1;//通道数目
	
	ADC_Init(ADC1,&ADC_InitStructure);//用结构体初始化ADC
	
	ADC_Cmd(ADC1,ENABLE);//打开ADC
	
	ADC_ResetCalibration(ADC1);//等待复位校准
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);//标志位判断
	ADC_StartCalibration(ADC1);//启动校准
	while(ADC_GetCalibrationStatus(ADC1) ==SET);//标志位判断

}


uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);//设置规则组通道
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//软件触发转换
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//获取标志位 选择标志位类型
	return ADC_GetConversionValue(ADC1);//获取转换值
}

















