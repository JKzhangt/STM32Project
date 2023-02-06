#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count;//统计中断触发次数

//显示提示CTRL+ALT+SPACE
void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开机GPIOB适中
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开启适中
	//EXTI不需要开始时钟
	//NVIC默认开启（内核内外设）
	
	//配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//配置EXTI
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//中断模式
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
	EXTI_Init(&EXTI_InitStructure);
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//分组
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//响应优先级
	NVIC_Init(&NVIC_InitStructure);
	

}
uint16_t CountSensor_Get(void)
{
	
	return CountSensor_Count;
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetFlagStatus(EXTI_Line14)==SET)//如果是执行中断
	{
		CountSensor_Count++;
		EXTI_ClearITPendingBit(EXTI_Line14);//清除中断标志位
		
	}
}

