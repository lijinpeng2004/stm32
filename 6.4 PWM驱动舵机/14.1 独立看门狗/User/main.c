#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "OLED.h"

int main(void )
{
	OLED_Init();
	Key_Init();
	OLED_ShowString (1,1,"IWDG TEST");
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST)==SET)//判断是不是看门狗进行的复位操作
	{
		OLED_ShowString (2,1,"IWDGRST");
		Delay_ms (500);
		OLED_ShowString (2,1,"       ");
		Delay_ms (100);
		
		RCC_ClearFlag ();
		
	}
	else
	{
		OLED_ShowString (3,1,"RST");
		Delay_ms (500);
		OLED_ShowString (3,1,"   ");
		Delay_ms (100);
	}
	
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//解除写保护
	IWDG_SetPrescaler(IWDG_Prescaler_16);//设置预分频系数 需要计算 1000ms
	IWDG_SetReload(2499);//设置重装值
	IWDG_ReloadCounter();//喂狗
	IWDG_Enable();//启动看门狗
	while(1)
	{
		Key_GetNum();
		IWDG_ReloadCounter();//喂狗
		OLED_ShowString(4,1,"FEED");
		Delay_ms(200);
		OLED_ShowString(4,1,"    ");
		Delay_ms(600);
	}
}
