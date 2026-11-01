#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS		0xD0



void MPU6050_Write(uint8_t RegAddress,uint8_t Data)//指定地址写（一个字节数据）
{
	MyI2C_Start ();
	MyI2C_SendByte(MPU6050_ADDRESS);//发送设备地址
	MyI2C_ReceiveAck ();//暂时不判断
	MyI2C_SendByte(RegAddress);//发送寄存器地址
	MyI2C_ReceiveAck ();
	MyI2C_SendByte(Data);//写入数据
	MyI2C_ReceiveAck ();
	MyI2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)//指定地址读（一个字节数据）
{
	uint8_t Data;
	
	MyI2C_Start ();//寻找设备和寄存器
	MyI2C_SendByte(MPU6050_ADDRESS);//发送设备地址
	MyI2C_ReceiveAck ();//暂时不判断
	MyI2C_SendByte(RegAddress);//发送寄存器地址
	MyI2C_ReceiveAck ();
	
	MyI2C_Start ();//重起始
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);//要求读取数据
	MyI2C_ReceiveAck ();
	Data=MyI2C_ReceiveByte();//从机发送数据，主机接收
	MyI2C_SendAck(1);//不给应答，相当于结束
	MyI2C_Stop();//停止位
	
	return Data;
}

void MPU6050_Init(void)
{
	MyI2C_Init ();
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











