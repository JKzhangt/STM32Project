#include "stm32f10x.h"                  // Device header

int16_t Encoder_Count;

void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开机GPIOB适中
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开启适中
	//EXTI不需要开始时钟
	//NVIC默认开启（内核内外设）
	
	//配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//配置EXTI
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line0|EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//中断模式
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
	EXTI_Init(&EXTI_InitStructure);
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//分组
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//响应优先级
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;//响应优先级
	NVIC_Init(&NVIC_InitStructure);
	


}
int16_t Encoder_Get(void)
{
	int16_t Temp;
	Temp=Encoder_Count;
	Encoder_Count=0;
	
	return Temp;
	


}
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET)
	{
		//左转
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
		{
			Encoder_Count--;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	
	}
	
}

void EXTI1_IRQHandler(void)
{
	//右转
	if(EXTI_GetITStatus(EXTI_Line1)==SET)
	{//****
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
		{
			Encoder_Count++;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	
	}
	
}
