#include "stm32f10x.h"                  // Device header

void Encoder_Time_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//开启时钟 72MHz
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开GPLOA端口

	
	GPIO_InitTypeDef GPIO_InitStructre;//定义GPIO结构体
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_IPU;//上拉输入模式
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);
	


	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//时基结构体
	TIM_TimeBaseInitStruct.TIM_Prescaler=1-1;//PSC预分频器的值 0~65535
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数模式
	TIM_TimeBaseInitStruct.TIM_Period=65536-1;//ARR自动重装器的值 0~65535
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//时间分频
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//重复寄存器，高级定时器才用
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);//初始化时基单元
	
	TIM_ICInitTypeDef TIM_ICInitStructure;//编码器只有通道一和通道二
	TIM_ICStructInit (&TIM_ICInitStructure);//结构体初始化 用于不完整的结构体变量赋初值
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//选择IC的通道共四个
	TIM_ICInitStructure.TIM_ICFilter = 0xF;//滤波器的选择

	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//选择IC的通道共四个
	TIM_ICInitStructure.TIM_ICFilter = 0xF;//滤波器的选择
	
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	

	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//设置编码器模式//选择极性，上升沿下降沿都触发
	
	TIM_Cmd(TIM3,ENABLE);//启动编码器
}

int16_t Encoder_Time_Get(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	return Temp;
}






















