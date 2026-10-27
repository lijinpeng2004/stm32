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

uint16_t Num;
uint16_t Speed;

int main(void )
{
	OLED_Init();
	Timer_Init();
	Encoder_Time_Init();

	OLED_ShowString (1,1,"Speed:");
	while(1)
	{
		OLED_ShowSignedNum (1,7,Speed,5);
		
	}
}
void TIM2_IRQHandler(void)//中断函数 ，在启动文件里找,中断函数可以放在主函数下面
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		Speed=Encoder_Time_Get ();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除标志位和EXTI中断相似
	}
}