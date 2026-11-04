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
#include "MyRTC.h"                         


int main(void )
{
	OLED_Init();
	MyRTC_Init ();
	
	OLED_ShowString(1,1,"Date:XXXX-XX-XX");
	OLED_ShowString(2,1,"Time:XX:XX:XX");
	OLED_ShowString(3,1,"CNT:");
	OLED_ShowString(4,1,"DIV:");
	while(1)
	{
		MyRTC_ReadTime();
		
		OLED_ShowNum(1,6,MyRTC_Time[0],4);
		OLED_ShowNum(1,11,MyRTC_Time[1],2);
		OLED_ShowNum(1,14,MyRTC_Time[2],2);
		OLED_ShowNum(2,6,MyRTC_Time[3],2);
		OLED_ShowNum(2,9,MyRTC_Time[4],2);
		OLED_ShowNum(2,12,MyRTC_Time[5],2);
		
		OLED_ShowNum(3,6,RTC_GetCounter (),10);
		OLED_ShowNum(4,6,RTC_GetDivider (),10);

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
