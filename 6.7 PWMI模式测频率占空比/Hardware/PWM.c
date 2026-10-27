#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启时钟 72MHz
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开GPLOA端口

	
	GPIO_InitTypeDef GPIO_InitStructre;//定义GPIO结构体
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出模式
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);
	
	
//	计算公式
//	PWM频率:Freq = CK_PSC / (PSC + 1) / (ARR + 1)
//	PWM占空比:Duty=CCR/(ARR+1)
//	PWM分辨率:Reso=1/(ARR+1)


	TIM_InternalClockConfig(TIM2);//选择时钟源，不写默认内部时钟
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//时基结构体
	TIM_TimeBaseInitStruct.TIM_Prescaler=720-1;//PSC预分频器的值 0~65535
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数模式
	TIM_TimeBaseInitStruct.TIM_Period=100-1;//ARR自动重装器的值 0~65535
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//时间分频
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//重复寄存器，高级定时器才用
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);//初始化时基单元
	
	//计数器溢出频率:CK_CNT_OV=CK_CNT/(ARR+1)= CK_PSC / T (PSC + 1) / (ARR + 1)
	TIM_OCInitTypeDef TIM_OCInitStructure;//输出比较结构体
	TIM_OCStructInit(&TIM_OCInitStructure);//给结构体赋初始值
	/*列出了通用定时器的设置变量*/
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//设置输出比较模式 8种
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCNPolarity_High;//设置输出比较的极性
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//设置输出使能
	TIM_OCInitStructure.TIM_Pulse=0;//设置CCR
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);//查看引脚映射表找对应PA1的初始化OC函数
	
	
	
	TIM_Cmd(TIM2,ENABLE);//定时器启动
	
}

void PWM_SetCompare(uint16_t Compare)
{
	TIM_SetCompare1(TIM2, Compare);
}

void PWM_SetPrescaler(uint16_t Prescaler)
{
	TIM_PrescalerConfig(TIM2, Prescaler, TIM_PSCReloadMode_Immediate);
}










