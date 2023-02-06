#include "stm32f10x.h"                  // Device header

void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//如果不配置时钟那么寄存器将不会工作
	
	GPIO_InitTypeDef	GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);

}
void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);

}
void Buzzer_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12)==0)//读取当前端口电平wei0放置1
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}

}
