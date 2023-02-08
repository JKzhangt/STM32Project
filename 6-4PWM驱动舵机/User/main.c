#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Servo.h"
#include "Key.h"

uint8_t KeyNum;
float Angle;

int main(void)
{
	OLED_Init();
	Servo_Init();
	Key_Init();
	
	OLED_ShowString(1,1,"Angle:");

	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
			Angle+=30;
			if(Angle>180)
			{
				Angle=0;
			}
			
		}
		Servo_SetAngle(Angle);
		OLED_ShowNum(1,7,Angle,3);
//		for(i=0;i<=100;i++)
//		{
//			PWM_SetCompare2(i);
//			Delay_ms(10);
//		}
//		for(i=0;i<=100;i++)
//		{
//			PWM_SetCompare2(100-i);
//			Delay_ms(10);
//		}
//		
		
	}
	
}
