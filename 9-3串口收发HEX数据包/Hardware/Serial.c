#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

//发送数据的载荷数据
uint8_t Serial_TxPacket[4];
uint8_t Serial_RxPacket[4];
uint8_t Serial_RxFlag;

void Serial_Init(void)
{
	//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//GPIO初始化
	GPIO_InitTypeDef	GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//USART初始化
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//是否使用流控制
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;//send mode
	USART_InitStructure.USART_Parity=USART_Parity_No;//无校验位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//停止位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//字长
	USART_Init(USART1,&USART_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;//中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//中断优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	//开启USART
	USART_Cmd(USART1,ENABLE);
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//查看标志位防止数据覆盖
	
}
void Serial_SendArray(uint8_t *Array,uint16_t Length)//发送数组
{
	uint16_t i;
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Array[i]);
	}

}
void Serial_SendString(char *String)
{
	uint8_t i;
	for(i=0;String[i]!='\0';i++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X,uint32_t Y)
{
	uint32_t Result=1;
	while(Y--)
	{
		Result*=X;
	
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number,uint8_t Length)
{
	uint8_t i;
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Number/Serial_Pow(10,Length-i-1)%10+'0');
	}

}
int fputc(int ch,FILE *f)//printf重定向即移植到串口
{
	Serial_SendByte(ch);
	return ch;

}
void Serial_printf(char *format,...)//...可变参数列表
{
	char String[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	va_end(arg);
	Serial_SendString(String);
	
	
}
uint8_t Serial_GetRxFlag(void)
{
	if(Serial_RxFlag==1)
	{
		Serial_RxFlag=0;
		return 1;
	}
	return 0;
}

void Serial_SendPacket(void)
{
	Serial_SendByte(0XFF);
	Serial_SendArray(Serial_TxPacket,4);
	Serial_SendByte(0XFE);
}


void USART1_IRQHandler(void)
{
	static uint8_t RxState=0;
	static uint8_t pRxPacket=0;
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		
		if(RxState==0)
		{
			if(RxData==0xFF)
			{
				RxState=1;
				pRxPacket=0;
			}
		}
		else if(RxState==1)
		{
			Serial_RxPacket[pRxPacket]=RxData;
			pRxPacket++;
			if(pRxPacket>=4)
			{
				RxState=2;
				
			}
		}
		else if(RxState==2)
		{
			if(RxData==0xFE)
			{
				RxState=0;
				Serial_RxFlag=1;
			}
		}
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}


