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


int main(void )
{
	OLED_Init();
	Serial_Init ();
	
	Serial_SendByte (0x41);
	
	uint8_t MyArray[]={0x42,0x43,0x44,0x45};
	Serial_SendArray(MyArray,4);
	Serial_SendString ("\r\nNum1=");//换行需要两个转义字符
	Serial_SendNumber(111,3);
	
	printf("\r\nNum2=%d",222);
	char String[100];
	sprintf(String,"\r\nNum3=%d",333);
	Serial_SendString (String );
	Serial_Printf ("\r\nNum4=%d",444);
	Serial_Printf ("\r\n");
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
