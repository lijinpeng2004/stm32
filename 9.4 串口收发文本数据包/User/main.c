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

int main(void )
{
	OLED_Init();
	LED_Init();
	Serial_Init ();

	OLED_ShowString (1,1,"TxPacket");
	OLED_ShowString (3,1,"RxPacket");
	



	while(1)
	{
		if(Serial_RxFlag==1)//防止数据包错位
		{
			OLED_ShowString (4,1,"                " );//相当于先擦除第四行,一定要16个空格不能是4个tab
			OLED_ShowString (4,1,Serial_RxPacket );
			
			if(strcmp (Serial_RxPacket ,"LED_ON")==0)
			{
				LED1_ON();
				Serial_SendString("LED_ON_OK\r\n");
				OLED_ShowString (2,1,"                " );//相当于先擦除第四行,一定要16个空格不能是4个tab
				OLED_ShowString (2,1,"LED_ON_OK");
			}
			else if(strcmp (Serial_RxPacket ,"LED_OFF")==0)
			{
				LED1_OFF();
				Serial_SendString("LED_OFF_OK\r\n");
				OLED_ShowString (2,1,"                " );//相当于先擦除第四行,一定要16个空格不能是4个tab
				OLED_ShowString (2,1,"LED_OFF_OK");
			}
			else
			{
				Serial_SendString("ERROR_COMMAND\r\n");
				OLED_ShowString (2,1,"                " );//相当于先擦除第四行,一定要16个空格不能是4个tab
				OLED_ShowString (2,1,"ERROR_COMMAND");
			}
			Serial_RxFlag=0;
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
