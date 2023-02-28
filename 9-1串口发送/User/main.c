#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Serial.h"


int main(void)
{
	OLED_Init();
	Serial_Init();
	
	Serial_SendByte(0x41);
	uint8_t MyArray[]={0x42,0x43,0x44,0x45};
	Serial_SendArray(MyArray,4);
	Serial_SendString("\r\nHelloworld!\r\n");
	Serial_SendNumber(111,3);
	printf("\r\nNumber2=%d\r\n",222);
	char String[100];
	sprintf(String,"\r\nNumber3=%d\r\n",333);
	Serial_SendString(String);
	Serial_printf("\r\nNumber4=%d",444);
	Serial_printf("\r\n");
	while(1)
	{
		
		
		
	}
	
}
