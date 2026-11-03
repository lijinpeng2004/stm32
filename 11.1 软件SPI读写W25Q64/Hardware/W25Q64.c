#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"

void W25Q64_Init(void)
{
	MySPI_Init ();
}

void W25Q64_ReadID(uint8_t *MID,uint16_t *DID)//厂商ID，设备ID
{
	MySPI_Start();
	MySPI_SwapByte (W25Q64_JEDEC_ID	);//读ID号的指令
	*MID=MySPI_SwapByte (W25Q64_DUMMY_BYTE);//获取厂商ID号
	*DID=MySPI_SwapByte (W25Q64_DUMMY_BYTE);//获取设备ID号高八位
	*DID <<= 8 ;//左移八位
	*DID |=MySPI_SwapByte (W25Q64_DUMMY_BYTE);//获取设备ID号第八位
	MySPI_Stop();
}

void W25Q64_WriteEnable(void)//写使能
{
	MySPI_Start();
	MySPI_SwapByte (W25Q64_WRITE_ENABLE);//写使能指令
	MySPI_Stop();
}

void W25Q64_WaitBusy(void)//每次写入后芯片进入忙状态 等待busy为0
{
	uint32_t Timeout;
	MySPI_Start();
	MySPI_SwapByte (W25Q64_READ_STATUS_REGISTER_1);//读状态寄存器1指令
	while((MySPI_SwapByte (W25Q64_DUMMY_BYTE) & 0x01) == 0x01)//返回状态寄存器1的状态，busy为0跳出循环
	{
		Timeout--;
		if(Timeout == 0)
		{
			break;
		}
	}
	MySPI_Stop();
	
}

void W25Q64_PageProgram(uint32_t Address,uint8_t *DataArray,uint16_t Count)//指定地址写入多组数据
{
	uint16_t i;
	
	W25Q64_WriteEnable();//写使能
	
	MySPI_Start();
	MySPI_SwapByte (W25Q64_PAGE_PROGRAM);//发送写page指令
	MySPI_SwapByte (Address>>16);//发送24位地址
	MySPI_SwapByte (Address>>8);
	MySPI_SwapByte (Address);
	for(i=0;i<Count;i++)
	{
		MySPI_SwapByte (DataArray[i]);
	}
	MySPI_Stop();
	W25Q64_WaitBusy();//事后等待
}

void W25Q64_SectorErase(uint32_t Address)//擦除指定地址
{
	W25Q64_WriteEnable();//写使能
	MySPI_Start();
	MySPI_SwapByte (W25Q64_SECTOR_ERASE_4KB	);
	MySPI_SwapByte (Address>>16);//发送24位地址
	MySPI_SwapByte (Address>>8);
	MySPI_SwapByte (Address);
	MySPI_Stop();
	W25Q64_WaitBusy();//事后等待
}

void W25Q64_ReadData(uint32_t Address,uint8_t *DataArray,uint32_t Count)//读取指定地址数据
{
	uint32_t i;
	MySPI_Start();
	MySPI_SwapByte (W25Q64_READ_DATA);//发送写page指令
	MySPI_SwapByte (Address>>16);//发送24位地址
	MySPI_SwapByte (Address>>8);
	MySPI_SwapByte (Address);
	for(i=0;i<Count;i++)
	{
		DataArray[i]=MySPI_SwapByte (W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();
	
}







