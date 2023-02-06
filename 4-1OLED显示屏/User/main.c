#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"

int main(void)
{
	OLED_Init();

	OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,2,"HelloWorld!");
	OLED_ShowNum(2,1,12345,6);//无符号10进制数字
	OLED_ShowSignedNum(2,7,-66,2);
	OLED_ShowHexNum(3,1,0xAA55,4);
	OLED_ShowBinNum(4,1,0xAA55,16);
	
	OLED_Clear();
	while(1)
	{
		
		
		
	}
	
}
