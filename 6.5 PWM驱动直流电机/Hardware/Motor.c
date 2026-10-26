#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Motor_Init(void)
{
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开GPLOA端口
	
	GPIO_InitTypeDef GPIO_InitStructre;//定义GPIO结构体
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出模式
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);
	GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5);
	
	PWM_Init ();
	
}

void Motor_SetSpeed(int8_t Speed)
{
	if(Speed>=0)
	{
		GPIO_SetBits(GPIOA ,GPIO_Pin_5 );
		GPIO_ResetBits(GPIOA ,GPIO_Pin_4 );
		PWM_SetCompare3(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA ,GPIO_Pin_5 );
		GPIO_SetBits(GPIOA ,GPIO_Pin_4 );
		PWM_SetCompare3(-Speed);
	}
}
















