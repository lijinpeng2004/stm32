#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void )
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructre;
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	
	while(1)
	{
//		GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)0);
//		Delay_ms(500);
//		GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)1);
//		Delay_ms(500);
	}
}
