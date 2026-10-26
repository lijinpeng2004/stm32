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

uint16_t Num;
uint8_t KeyNum;
int8_t Speed;

int main(void )
{
	OLED_Init();
	Key_Init ();
	Motor_Init ();
	
	OLED_ShowString (1,1,"Speed:");
	
	while(1)
	{
		KeyNum = Key_GetNum ();
		if(KeyNum ==1)
		{
			Speed +=20;
			if(Speed > 100)
			{
				Speed =-100;
			}
		}
		Motor_SetSpeed(Speed);
		OLED_ShowSignedNum (1,7,Speed,3);
		
	}
}
