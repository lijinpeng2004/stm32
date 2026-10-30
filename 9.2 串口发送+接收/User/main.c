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


uint16_t Num;
uint8_t RxData;

int main(void )
{
	OLED_Init();
	Serial_Init ();
	OLED_ShowString (1,1,"RxData:");
	

	while(1)
	{
		if(Serial_GetRxFlag()==1)
		{
			RxData=Serial_GetRxData();
			Serial_SendByte (RxData);
			OLED_ShowHexNum (1,8,RxData,2);
		}
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
