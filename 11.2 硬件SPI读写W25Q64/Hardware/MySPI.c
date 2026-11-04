#include "stm32f10x.h"                  // Device header

void MySPI_W_SS(uint8_t BitValue)//写设备的SS
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction )BitValue );
}




void MySPI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开GPLOA端口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 ,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructre;//定义GPIO结构体
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出模式 SS
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);
	
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出模式  MOSI SCK
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_7;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);
	
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_IPU;//上拉输入模式 MISO
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);
	
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master ;//选择主机或从机
	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;//选择传输方式
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;//选择数据帧位数 8/16
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;//选择高位先行
	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_128 ;//选择分频72M/128
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_Low;//设置SCK默认电平，低电平
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_1Edge ;//时钟相位，第一个边缘采样或第二个边缘采样(移入)
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;//选择软件NSS
	SPI_InitStructure.SPI_CRCPolynomial=7;//校验值，不用过多了解
	SPI_Init (SPI1 ,&SPI_InitStructure);
	
	SPI_Cmd(SPI1,ENABLE);
	MySPI_W_SS(1);//默认不选择从机
}



void MySPI_Start(void)//起始信号
{
	MySPI_W_SS(0);
}

void MySPI_Stop(void)//终止信号
{
	MySPI_W_SS(1);
}

uint8_t MySPI_SwapByte(uint8_t ByteSend)//字节交换时序（非连续）
{
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) !=SET);//等待TXE为空 1，表示你可以写入了
	
	SPI_I2S_SendData(SPI1,ByteSend);//写入要发送的数据
	
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) !=SET);//等待RXNE为空 1 ，从机接收完成
	
	return SPI_I2S_ReceiveData(SPI1);//返回接受到的数据
}











