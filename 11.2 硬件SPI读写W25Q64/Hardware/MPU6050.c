#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS		0xD0

void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)//封装等待函数
{
	uint32_t Timeout = 10000;
	while(I2C_CheckEvent(I2Cx, I2C_EVENT)!=SUCCESS)//检查事件，读取状态
	{
		Timeout -- ;
		if(Timeout == 0)
		{
			break;
		}
	}
}

void MPU6050_Write(uint8_t RegAddress,uint8_t Data)//指定地址写（一个字节数据）
{
	

	I2C_GenerateSTART(I2C2,ENABLE);//起始条件
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);//检查事件，读取状态
	
	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Transmitter);//发送设备地址，自带应答
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);//检查事件，读取状态
	
	I2C_SendData(I2C2,RegAddress);//发送寄存器地址
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING);//检查事件，读取状态
	
	I2C_SendData(I2C2,Data);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED);//检查事件，读取状态
	
	I2C_GenerateSTOP(I2C2,ENABLE);//停止位
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)//指定地址读（一个字节数据）
{
	uint8_t Data;

	I2C_GenerateSTART(I2C2,ENABLE);//起始条件
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);//检查事件，读取状态
	
	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Transmitter);//发送设备地址，自带应答
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);//检查事件，读取状态
	
	I2C_SendData(I2C2,RegAddress);//发送寄存器地址
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED);//检查事件，读取状态
	
	I2C_GenerateSTART(I2C2,ENABLE);//重复起始条件，开始读
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);//检查事件，读取状态

	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Receiver);//发送设备地址，自带应答
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED );//检查事件，读取状态

	I2C_AcknowledgeConfig(I2C2,DISABLE);//停止应答，让从机停止给数据
	I2C_GenerateSTOP(I2C2,ENABLE);//申请产生终止条件
	//在完成一个字节的读取后需要先进行这两步操作
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED  );//检查事件，读取状态
	Data = I2C_ReceiveData(I2C2);//接收一个字节
	
	I2C_AcknowledgeConfig(I2C2,ENABLE);//
	
	return Data;
}

void MPU6050_Init(void)
{
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_I2C2,ENABLE );//开启I2C2的时钟
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructre;//定义GPIO结构体
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_AF_OD;//复用开漏模式
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructre);
	
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Mode=I2C_Mode_I2C;//I2C的模式
	I2C_InitStructure.I2C_DutyCycle=I2C_DutyCycle_2;//时钟占空比，时钟速度大于100khz才有用，小于100，默认1：1
	I2C_InitStructure.I2C_ClockSpeed=50000;//设置时钟速度，最大50kHz
	I2C_InitStructure.I2C_Ack=I2C_Ack_Enable;//应答位配置
	I2C_InitStructure.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;//选择响应地址位数
	I2C_InitStructure.I2C_OwnAddress1=0x00;//stm32自身地址作为从机使用
	I2C_Init(I2C2,&I2C_InitStructure);
	
	I2C_Cmd(I2C2,ENABLE);
	
	MPU6050_Write(MPU6050_PWR_MGMT_1,0x01);//配置电源管理寄存器1
	MPU6050_Write(MPU6050_PWR_MGMT_2,0x00);//配置电源管理寄存器2
	MPU6050_Write(MPU6050_SMPLRT_DIV,0x09);//配置十分频
	MPU6050_Write(MPU6050_CONFIG,0x06);//配置寄存器与滤波器
	MPU6050_Write(MPU6050_GYRO_CONFIG,0x18);//陀螺仪寄存器，最大量程
	MPU6050_Write(MPU6050_ACCEL_CONFIG,0x18);//加速度计寄存器，最大量程，高通滤波器
}

uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

void MPU6050_GetData(int16_t *AccX,int16_t *AccY,int16_t *AccZ,
						int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ)
{
	uint8_t DataH,DataL;
	//实际上地址是连续的可以使用更好的办法
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);//加速度寄存器高8位
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);//加速度寄存器低8位
	*AccX=(DataH << 8) | DataL;
	
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);//加速度寄存器高8位
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);//加速度寄存器低8位
	*AccY=(DataH << 8) | DataL;
	
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);//加速度寄存器高8位
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);//加速度寄存器低8位
	*AccZ=(DataH << 8) | DataL;
	
	DataH=MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX=(DataH << 8) | DataL;
	
	DataH=MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY=(DataH << 8) | DataL;
	
	DataH=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ=(DataH << 8) | DataL;	
}











