#include "stm32f10x.h"                  // Device header

void LightSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructre;//定义GPIO结构体
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructre);
}

uint8_t LightSensor_Get(void)
{

	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);	
}

