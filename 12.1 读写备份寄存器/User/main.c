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
                             
uint16_t ArrayWrite[]={0x1234,0x5678};
uint16_t ArrayRead[2];
uint8_t KeyNum;

int main(void )
{
	OLED_Init();
	Key_Init();
	
	OLED_ShowString(1,1,"W:");
	OLED_ShowString(2,1,"R:");
	
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_PWR ,ENABLE );//开启PWR时钟
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_BKP ,ENABLE );
	
	PWR_BackupAccessCmd(ENABLE);//PWR使能
	

	while(1)
	{
		KeyNum = Key_GetNum();
		
		if(KeyNum==1)
		{
			ArrayWrite[0]++;
			ArrayWrite[1]++;
			BKP_WriteBackupRegister(BKP_DR1,ArrayWrite[0]);//在BKP_DR1写入数据
			BKP_WriteBackupRegister(BKP_DR2,ArrayWrite[1]);//在BKP_DR2写入数据
			OLED_ShowHexNum(1,3,ArrayWrite[0],4);
			OLED_ShowHexNum(1,8,ArrayWrite[1],4);
		}
		ArrayRead[0]=BKP_ReadBackupRegister(BKP_DR1);
		ArrayRead[1]=BKP_ReadBackupRegister(BKP_DR2);
		
		OLED_ShowHexNum(2,3,ArrayRead[0],4);
		OLED_ShowHexNum(2,8,ArrayRead[1],4);
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
