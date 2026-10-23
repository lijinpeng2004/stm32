#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "OLED.h"
#include "CounterSensor.h"


int main(void )
{
	OLED_Init();
	OLED_ShowString(1,1,"Count:");
	CountSensor_Init();
	
	while(1)
	{
		OLED_ShowNum(1,7,CountSensor_Get()/2,5);
		
	}
}
