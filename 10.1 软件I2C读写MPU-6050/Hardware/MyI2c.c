#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void MyI2C_W_SCL(uint8_t BitValue)//使用函数封装写入操作
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	Delay_us(10);
}
void MyI2C_W_SDA(uint8_t BitValue)//使用函数封装写入操作
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	Delay_us(10);
}

uint8_t MyI2C_R_SDA(void)//读取
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return BitValue;
}

void MyI2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//打开GPLOA端口
	
	GPIO_InitTypeDef GPIO_InitStructre;//定义GPIO结构体
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_Out_OD;//开漏输出模式
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructre);
	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);//把引脚先置高电平
	
	
}

void MyI2C_Start(void)//起始条件
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);//先拉低SDA再拉低SCL
	MyI2C_W_SCL(0);	
}
void MyI2C_Stop(void)//终止条件
{
	MyI2C_W_SDA(0);//先拉高SCL再拉高SDA
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte)//主机发送一个字节
{
	uint8_t i;
	for(i = 0 ; i < 8 ; i ++)
	{
		MyI2C_W_SDA(Byte & (0x80 >> i));//这种写入方式非0即1
		MyI2C_W_SCL(1);//释放SCL让从机读取
		MyI2C_W_SCL(0);//拉低SCL让主机写入
	}

}

uint8_t MyI2C_ReceiveByte(void)//主机接收一个字节
{
	uint8_t i,Byte = 0x00;
	
	MyI2C_W_SDA(1);//主机释放SDA，从机写入
	for(i=0 ;i<8;i++)
	{
		MyI2C_W_SCL(1);//释放SCL主机开始读取
		if(MyI2C_R_SDA() == 1) {Byte |= (0x80 >> i);}
		MyI2C_W_SCL(0);//拉低SCL从机开始写入
	}
	return Byte;
}

void MyI2C_SendAck(uint8_t AckBit)//主机发送应答
{

	MyI2C_W_SDA(AckBit);//写入ACK
	MyI2C_W_SCL(1);//释放SCL让从机读取
	MyI2C_W_SCL(0);//拉低SCL让主机写入
}

uint8_t MyI2C_ReceiveAck(void)//主机接收应答
{
	uint8_t AckBit;
	
	MyI2C_W_SDA(1);//主机释放SDA，从机写入
	MyI2C_W_SCL(1);//释放SCL主机开始读取
	AckBit = MyI2C_R_SDA();//0有应答，1无应答
	MyI2C_W_SCL(0);//拉低SCL从机开始写入

	return AckBit;
}





