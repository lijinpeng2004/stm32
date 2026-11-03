#include "stm32f10x.h"                  // Device header

void MySPI_W_SS(uint8_t BitValue)//写设备的SS
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction )BitValue );
}

void MySPI_W_SCK(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction )BitValue );
}

void MySPI_W_MOSI(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction )BitValue );
}

uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}


void MySPI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开GPLOA端口
	
	GPIO_InitTypeDef GPIO_InitStructre;//定义GPIO结构体
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_Out_PP;//3个输出脚 推挽输出模式
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);
	
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_IPU;//输入脚上拉输入模式
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);
	
	MySPI_W_SS(1);//SS默认高电平
	MySPI_W_SCK(0);//时钟默认低电平
	
}

void MySPI_Start(void)//起始信号
{
	MySPI_W_SS(0);
}

void MySPI_Stop(void)//终止信号
{
	MySPI_W_SS(1);
}

uint8_t MySPI_SwapByte(uint8_t ByteSend)//字节交换时序
{
	uint8_t i,ByteReceive = 0x00;
	
	for(i=0;i<8;i++)
	{
		MySPI_W_MOSI(ByteSend & (0x80>>i));//主机移出数据
		MySPI_W_SCK(1);//上升沿，从机读取数据
		if(MySPI_R_MISO() == 1){ByteReceive |=(0x80>>i);}
		MySPI_W_SCK(0);//准备移出下一位
	}
	return ByteReceive;
	
}











