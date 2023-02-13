#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"

uint16_t Speed;
int main(void)
{
	OLED_Init();
	Timer_Init();
	Encoder_Init();
	
	OLED_ShowString(1,1,"Speed:");

	

	while(1)
	{
		
		OLED_ShowSignedNum(1,7,Speed,5);
		Delay_ms(1000);
		//可以试一试下面代码
		//OLED_ShowNum(2,5,TIM_GetCounter(TIM2),5);
	}
	
}

void TIM2_IRQHandler(void)//zhongduanhanshu
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)//清除标志位
	{
		Speed=Encoder_Get();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}

}
