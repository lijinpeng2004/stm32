#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void )
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开GPLOA端口
	
	GPIO_InitTypeDef GPIO_InitStructre;//定义GPIO结构体
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);
	
	
	while(1)
	{
		GPIO_Write(GPIOA,~0x0001); //直接设置十六个引脚的电平
		Delay_ms(100);
		GPIO_Write(GPIOA,~0x0002);
		Delay_ms(100);
		GPIO_Write(GPIOA,~0x0004);
		Delay_ms(100);
		GPIO_Write(GPIOA,~0x0008);
		Delay_ms(100);
		GPIO_Write(GPIOA,~0x0010);
		Delay_ms(100);
		GPIO_Write(GPIOA,~0x0020);
		Delay_ms(100);
		GPIO_Write(GPIOA,~0x0040);
		Delay_ms(100);
		GPIO_Write(GPIOA,~0x0080);
		Delay_ms(100);
	}
}
