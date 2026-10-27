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

uint16_t Num;


int main(void )
{
	OLED_Init();
	PWM_Init();
	Ic_Init();
	
	OLED_ShowString (1,1,"Freq:00000Hz");
	
	PWM_SetPrescaler(720-1);
	PWM_SetCompare(50);
	
	while(1)
	{
		OLED_ShowNum (1,6,IC_GetFreq (),5);
	}
}
