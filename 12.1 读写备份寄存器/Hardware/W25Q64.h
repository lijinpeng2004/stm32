#ifndef __W25Q64_H
#define __W25Q64_H
void W25Q64_Init(void);
void W25Q64_ReadID(uint8_t *MID,uint16_t *DID);//厂商ID，设备ID
void W25Q64_PageProgram(uint32_t Address,uint8_t *DataArray,uint16_t Count);//指定地址写入多组数据
void W25Q64_SectorErase(uint32_t Address);//擦除指定地址
void W25Q64_ReadData(uint32_t Address,uint8_t *DataArray,uint32_t Count);//读取指定地址数据


#endif
