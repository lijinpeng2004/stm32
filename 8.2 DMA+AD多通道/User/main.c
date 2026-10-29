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

uint16_t Num;


int main(void )
{
	OLED_Init();
	AD_Init ();
	
	OLED_ShowString (1,1,"AD0:");
	OLED_ShowString (2,1,"AD1:");	
	OLED_ShowString (3,1,"AD2:");	
	OLED_ShowString (4,1,"AD3:");	
	while(1)
	{
//		AD_GetValue ();
		OLED_ShowNum(1,5,AD_Value[0],4);
		OLED_ShowNum(2,5,AD_Value[1],4);	
		OLED_ShowNum(3,5,AD_Value[2],4);	
		OLED_ShowNum(4,5,AD_Value[3],4);
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
