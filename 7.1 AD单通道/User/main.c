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

uint16_t Num;
uint16_t ADValue;
float  Volatge;

int main(void )
{
	OLED_Init();
	AD_Init ();
	OLED_ShowString (1,1,"ADValue:");
	OLED_ShowString (2,1,"Volatge:0.00V");
	
	while(1)
	{
		ADValue=AD_GetValue();
		Volatge=(float)ADValue / 4095 * 3.3;
		OLED_ShowNum (1,9,ADValue ,4);
		OLED_ShowNum (2,9,Volatge ,1);
		OLED_ShowNum (2,11,(uint16_t )(Volatge*100) %100 ,2);
		Delay_ms (100);
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
