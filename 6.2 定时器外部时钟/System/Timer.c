#include "stm32f10x.h"                  // Device header

extern uint16_t Num;//定义外部变量

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启时钟 72MHz
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
//	TIM_InternalClockConfig(TIM2);//选择时钟源，不写默认内部时钟
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x0F);//选择时钟源，外部时钟 参数 定时器 时钟分频 触发方式 滤波器选择
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//时基结构体
	TIM_TimeBaseInitStruct.TIM_Prescaler=1-1;//PSC预分频器的值 0~65535
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数模式
	TIM_TimeBaseInitStruct.TIM_Period=10-1;//ARR自动重装器的值 0~65535
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//时钟源分频
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//重复寄存器，高级定时器才用
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);//初始化时基单元
	
	//计数器溢出频率:CK_CNT_OV=CK_CNT/(ARR+1)= CK_PSC / T (PSC + 1) / (ARR + 1)
	
	TIM_ClearFlag(TIM2,TIM_IT_Update);//避免初始化后立刻进入中断
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//定时器中断使能，选择更新中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//NVIC选择分组
	
	NVIC_InitTypeDef NVIC_InitStructure;//NVIC结构体配置
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;//中断通道选择
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//响应优先级
	NVIC_Init(&NVIC_InitStructure);//NVIC初始化
	
	TIM_Cmd(TIM2,ENABLE);//定时器启动
	
}

uint16_t Timer_GetCounter(void)
{
	return TIM_GetCounter(TIM2);//返回计数器（ARR）的值
}

void TIM2_IRQHandler(void)//中断函数 ，在启动文件里找,中断函数可以放在主函数下面
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		Num ++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除标志位和EXTI中断相似
	}
}
























