#include "stm32f10x.h"                  // Device header


void Ic_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//开启时钟 72MHz
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开GPLOA端口

	
	GPIO_InitTypeDef GPIO_InitStructre;//定义GPIO结构体
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_IPU;//上拉输出模式
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);
	
	
//	计算公式
//	PWM频率:Freq = CK_PSC / (PSC + 1) / (ARR + 1)
//	PWM占空比:Duty=CCR/(ARR+1)
//	PWM分辨率:Reso=1/(ARR+1)


	TIM_InternalClockConfig(TIM3);//选择时钟源，不写默认内部时钟
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//时基结构体
	TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;//PSC预分频器的值 0~65535
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数模式
	TIM_TimeBaseInitStruct.TIM_Period=65536-1;//ARR自动重装器的值 0~65535
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//时间分频
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//重复寄存器，高级定时器才用
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);//初始化时基单元
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//选择IC的通道共四个
	TIM_ICInitStructure.TIM_ICFilter = 0xF;//滤波器的选择
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//选择触发方式
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//选择分频器
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//选择通道类型（直连输入）
	TIM_ICInit(TIM3, &TIM_ICInitStructure);

	TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);//快捷的把电路配制为PWMI模式的标准结构（相反）
	
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);//选择触发源
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);//配置从模式为Reset
	
	TIM_Cmd(TIM3, ENABLE);//启动定时器
	
	
}

uint32_t IC_GetFreq(void)//获取频率值
{
	return 1000000 / (TIM_GetCapture1(TIM3) + 1);//fc/N计算频率 
}

uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3) +1)* 100 / (TIM_GetCapture1(TIM3) +1);
}
















