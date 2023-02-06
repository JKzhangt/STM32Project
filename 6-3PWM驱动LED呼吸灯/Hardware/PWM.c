#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	//RCC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//GPIO初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//如果不配置时钟那么寄存器将不会工作
	GPIO_InitTypeDef	GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//GPIO_Pin_15
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
//	//AFIO
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	//时钟源
	TIM_InternalClockConfig(TIM2);//内部时钟
	
	//时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=100-1;//自动重装值减小总体计数变快 ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	
	TIM_OCInitTypeDef	TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//输出比较模式
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//输出比较极性
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//输出使能
	TIM_OCInitStructure.TIM_Pulse=0;//CCR设置
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	
	//运行控制
	TIM_Cmd(TIM2,ENABLE);

	
}
void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);

}
