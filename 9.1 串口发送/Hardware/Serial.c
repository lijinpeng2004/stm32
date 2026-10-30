#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "stdarg.h"
void Serial_Init(void )
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructre;//定义GPIO结构体
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出模式
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=9600;//设置波特率的数值
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//是否使用硬件流控
	USART_InitStructure.USART_Mode=USART_Mode_Tx;//选择发送模式
	USART_InitStructure.USART_Parity=USART_Parity_No;//选择校验方式
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//停止位选择
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//无校验选择八位
	USART_Init(USART1 ,&USART_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
	
}

void Serial_SendByte(uint8_t Byte)//发送2位16进制数据
{
	USART_SendData(USART1,Byte);//发送数据
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//标志位 判断TX空
	
}
void Serial_SendArray(uint8_t *Array,uint16_t Length)//发送数组
{
	uint16_t i;
	for (i=0;i<Length;i++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)//发送字符串，自带结束位
{
	uint8_t i;
	for (i=0;String[i]!='\0';i++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X,uint32_t Y)
{
	uint32_t Result =1;
	while(Y--)
	{
		Result *=X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number,uint8_t Length)//发送数字
{
	uint8_t i;
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Number/Serial_Pow(10,Length-i-1)%10+'0');//取最高位数字
	}
}

int fputc(int ch,FILE*f)//重定向函数fputc到串口，移植printf,不可选择不同的UART口
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format,...)//封装移植String，可变参数,可选择不同的UART口
{
	char String[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	va_end(arg);
	Serial_SendString(String);//可选择不同的UART口
}











