#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "OLED.h"
#include "CounterSensor.h"
#include "Encoder.h"
#include "Timer.h"
#include "Servo.h"
#include "Motor.h"
#include "PWM.h"
#include "IC.h"
#include "Encoder_Time.h"
#include "AD.h"
#include "MyDMA.h"
#include "Serial.h"
#include <string.h>
#include <MPU6050.h>
#include "W25Q64.h"
                             
uint8_t MID;
uint16_t DID;
uint8_t ArrayWrite[]={0x01,0x02,0x03,0x04};
uint8_t ArrayRead[4];
int main(void )
{
	OLED_Init();
	W25Q64_Init();
	
	OLED_ShowString (1,1,"MID:   DID:");
	OLED_ShowString (2,1,"W:");	
	OLED_ShowString (3,1,"R:");
	W25Q64_ReadID (&MID,&DID );
	OLED_ShowHexNum (1,5,MID,2);
	OLED_ShowHexNum (1,12,DID,4);
	W25Q64_SectorErase(0x000000);
	W25Q64_PageProgram(0x000000,ArrayWrite,4);
	
	W25Q64_ReadData(0x000000,ArrayRead,4);
	OLED_ShowHexNum (2,3,ArrayWrite[0],2);
	OLED_ShowHexNum (2,6,ArrayWrite[1],2);
	OLED_ShowHexNum (2,9,ArrayWrite[2],2);
	OLED_ShowHexNum (2,12,ArrayWrite[3],2);
	

	OLED_ShowHexNum (3,3,ArrayRead [0],2);
	OLED_ShowHexNum (3,6,ArrayRead [1],2);
	OLED_ShowHexNum (3,9,ArrayRead [2],2);
	OLED_ShowHexNum (3,12,ArrayRead [3],2);
	while(1)
	{

	}

}


//void TIM2_IRQHandler(void)//中断函数 ，在启动文件里找,中断函数可以放在主函数下面
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
//	{
//		Speed=Encoder_Time_Get ();
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除标志位和EXTI中断相似
//	}
//}
