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
	OLED_ShowString (1,1,"WWDG TEST");
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST)==SET)//判断是不是看门狗进行的复位操作
	{
		OLED_ShowString (2,1,"WWDGRST");
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
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_WWDG ,ENABLE );//36MHz
	WWDG_SetPrescaler(WWDG_Prescaler_8);//预分频器
	WWDG_SetWindowValue(0x40|21);//窗口值      //30ms 最小时间 
	WWDG_Enable(0x40|54);//最高位为1，设置超时间 //50ms
	
	while(1)
	{
		Key_GetNum();
		
		
		OLED_ShowString(4,1,"FEED");
		Delay_ms(20);
		OLED_ShowString(4,1,"    ");
		Delay_ms(20);
		WWDG_SetCounter(0x40|54);
	}
}
