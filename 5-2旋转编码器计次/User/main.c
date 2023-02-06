#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Encoder.h"

int16_t Num;

//中断仅仅操作标志位；减少代码耦合性
int main(void)
{
	OLED_Init();
	Encoder_Init();
	OLED_ShowString(1,1,"Num:");
	

	while(1)
	{
		Num+=Encoder_Get();
		OLED_ShowSignedNum(1,5,Num,5);
		
		
	}
	
}
