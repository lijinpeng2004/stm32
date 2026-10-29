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
uint16_t AD0,AD1,AD2,AD3;
//const uint8_t aa=0x66; //只能读不能写，使用const定义的变量，是存储到Flash里的
////当程序中出现一大批数据且不需要更改时使用const节省SRAM的空间
uint8_t DataA[] ={0x01,0x02,0x03,0x04};
uint8_t DataB[] ={0,0,0,0} ;

int main(void )
{
	OLED_Init();
	MyDMA_Init((uint32_t)DataA,(uint32_t)DataB,4);	
	OLED_ShowString(1,1,"DataA");
	OLED_ShowString(3,1,"DataB");	
	OLED_ShowHexNum(1,8,(uint32_t)DataA,8);
	OLED_ShowHexNum(3,8,(uint32_t)DataB,8);
	
	OLED_ShowHexNum(2,1,DataA[0],2);
	OLED_ShowHexNum(2,4,DataA[1],2);
	OLED_ShowHexNum(2,7,DataA[2],2);
	OLED_ShowHexNum(2,10,DataA[3],2);
	OLED_ShowHexNum(4,1,DataB[0],2);
	OLED_ShowHexNum(4,4,DataB[1],2);
	OLED_ShowHexNum(4,7,DataB[2],2);
	OLED_ShowHexNum(4,10,DataB[3],2);
	

	while(1)
	{
		DataA[0]++;
		DataA[1]++;
		DataA[2]++;
		DataA[3]++;
		
		OLED_ShowHexNum(2,1,DataA[0],2);
		OLED_ShowHexNum(2,4,DataA[1],2);
		OLED_ShowHexNum(2,7,DataA[2],2);
		OLED_ShowHexNum(2,10,DataA[3],2);
		OLED_ShowHexNum(4,1,DataB[0],2);
		OLED_ShowHexNum(4,4,DataB[1],2);
		OLED_ShowHexNum(4,7,DataB[2],2);
		OLED_ShowHexNum(4,10,DataB[3],2);
		
		Delay_ms(1000);
		
		MyDMA_Transfer();
		
		OLED_ShowHexNum(2,1,DataA[0],2);
		OLED_ShowHexNum(2,4,DataA[1],2);
		OLED_ShowHexNum(2,7,DataA[2],2);
		OLED_ShowHexNum(2,10,DataA[3],2);
		OLED_ShowHexNum(4,1,DataB[0],2);
		OLED_ShowHexNum(4,4,DataB[1],2);
		OLED_ShowHexNum(4,7,DataB[2],2);
		OLED_ShowHexNum(4,10,DataB[3],2);
		
		Delay_ms(1000);
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
