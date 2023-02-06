#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "CountSensor.h"

int main(void)
{
	OLED_Init();
	CountSensor_Init();


	OLED_ShowString(1,2,"Count:");

	
	while(1)
	{
		OLED_ShowNum(1,7,CountSensor_Get(),5);
		
		
	}
	
}
