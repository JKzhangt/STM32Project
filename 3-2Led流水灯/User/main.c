#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开GPIOA的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出 高低电平都有效，开漏模式低电平有效高电平无效
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;//16个端口配置为推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//50MHZ速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

	while(1)
	{
		GPIO_Write(GPIOA,~0x0001);//0000 0000 0000 0001
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0002);//0000 0000 0000 0010
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0004);//0000 0000 0000 0100
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0008);//0000 0000 0000 1000
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0010);//0000 0000 0001 0000
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0020);//0000 0000 0010 0000
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0040);//0000 0000 0100 0000
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0080);//0000 0000 1000 0000
		Delay_ms(500);
	}
	
}
