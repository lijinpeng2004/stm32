#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void )
{
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//打开GPLOA端口
//	
//	GPIO_InitTypeDef GPIO_InitStructre;//定义GPIO结构体
//	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_12;
//	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitStructre);
//	
//	
//	while(1)
//	{
//		GPIO_WriteBit(GPIOB,GPIO_Pin_12,(BitAction)0); 
//		Delay_ms(100);
//		GPIO_WriteBit(GPIOB,GPIO_Pin_12,(BitAction)1);
//		Delay_ms(100);
//		GPIO_WriteBit(GPIOB,GPIO_Pin_12,(BitAction)0); 
//		Delay_ms(100);
//		GPIO_WriteBit(GPIOB,GPIO_Pin_12,(BitAction)1);
//		Delay_ms(700);

//	}
}
