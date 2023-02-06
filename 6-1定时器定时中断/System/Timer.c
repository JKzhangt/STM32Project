#include "stm32f10x.h"                  // Device header


//extern 不同文件使用变量	extern uint16_t Num;

void Timer_Init(void)
{
	//RCC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	
	//时钟源
	TIM_InternalClockConfig(TIM2);//内部时钟
	
	//时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=10000-1;//自动重装值减小总体计数变快
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	//中断控制
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//清空中断标志位以求不会上电之后立马开始中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	//NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//qiangzhanyouxianji
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//xiangyinyouxianji
	NVIC_Init(&NVIC_InitStructure);
	
	//运行控制
	TIM_Cmd(TIM2,ENABLE);

}
//void TIM2_IRQHandler(void)//zhongduanhanshu
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)//清除标志位
//	{
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}

//}
