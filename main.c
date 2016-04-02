#include "main.h"

static __IO uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

static void Delay(__IO uint32_t nTime);

void initUART(){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
}

void USART_Send1byte(USART_TypeDef *USARTx, char Data){
	USART_SendData(USARTx, (uint16_t)Data);
	while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
}

void USART_Sendnbyte(USART_TypeDef *USARTx, char *Data, int len){
	int i;
	for(i=0; i<len; ++i) USART_Send1byte(USARTx, Data[i]);
}

void USART_myprintf(USART_TypeDef *USARTx, const char *fmt, ...){
	static char buffer[100];
	int len = 0;
	va_list ap;
	va_start(ap, fmt);
	len = vsprintf(buffer, fmt, ap);
	USART_Sendnbyte(USARTx, buffer, len);
	va_end(ap);
	return len;
}

void initServo(){
	TIM_TimeBaseInitTypeDef TIM_initstr;
	TIM_OCInitTypeDef TIM_OC_initstr;
	GPIO_InitTypeDef GPIO_initstr;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	GPIO_initstr.GPIO_Pin = GPIO_Pin_2;
	GPIO_initstr.GPIO_Mode = GPIO_Mode_AF;
	GPIO_initstr.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_initstr.GPIO_OType = GPIO_OType_PP;
	GPIO_initstr.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_initstr);
	GPIO_initstr.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_initstr);

	TIM_initstr.TIM_Period = 60000-1;
	TIM_initstr.TIM_Prescaler = 32-1;
	TIM_initstr.TIM_ClockDivision = 0;
	TIM_initstr.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_initstr.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_initstr);

	TIM_OC_initstr.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_initstr.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC_initstr.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC_initstr.TIM_Pulse = 4500-1;
	TIM_OC3Init(TIM2,&TIM_OC_initstr);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Disable);
	TIM_OC4Init(TIM3,&TIM_OC_initstr);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Disable);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
	TIM_TimeBaseInit(TIM2, &TIM_initstr);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_CtrlPWMOutputs(TIM2, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_TIM3);
	TIM_TimeBaseInit(TIM3, &TIM_initstr);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_CtrlPWMOutputs(TIM3, ENABLE);
}

void startServo(uint8_t tim){
	if(tim == 2){
		TIM_Cmd(TIM2, ENABLE);
	} else if(tim == 3){
		TIM_Cmd(TIM3, ENABLE);
	}
}
void stopServo(uint8_t tim){
	if(tim == 2){
		TIM_Cmd(TIM2, DISABLE);
	} else if(tim == 3){
		TIM_Cmd(TIM3, DISABLE);
	}
}

void setServo(int16_t angle, uint8_t tim){
	TIM_TimeBaseInitTypeDef TIM_initstr;
	TIM_OCInitTypeDef TIM_OC_initstr;
	
	TIM_initstr.TIM_Period = 60000 - 1;
	TIM_initstr.TIM_Prescaler = 32 - 1;
	TIM_initstr.TIM_ClockDivision = 0;
	TIM_initstr.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_initstr.TIM_RepetitionCounter = 0;
	
	TIM_OC_initstr.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_initstr.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC_initstr.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC_initstr.TIM_Pulse = (4500 + 12 * angle) - 1;

	if(tim == 2){
		TIM_TimeBaseInit(TIM2, &TIM_initstr);
		TIM_OC3Init(TIM2,&TIM_OC_initstr);
		TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Disable);
	} else if(tim == 3){
		TIM_TimeBaseInit(TIM3, &TIM_initstr);
		TIM_OC4Init(TIM3,&TIM_OC_initstr);
		TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Disable);
	}
}


int main(void){
	SystemInit();
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 960);

	initUART();

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_11 | GPIO_Pin_12);

	initServo();
	startServo(2);
	startServo(3);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_ResetBits(GPIOB, GPIO_Pin_14 | GPIO_Pin_15);

	GPIO_SetBits(GPIOA, GPIO_Pin_11);
	Delay(50);
	GPIO_ResetBits(GPIOA, GPIO_Pin_11);

	int16_t a = 0;
	int16_t b = 0;

	while (1){
		if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13)){
			GPIO_SetBits(GPIOB, GPIO_Pin_14);
			Delay(100);
			a += 10; b += 10;
			while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15));
			Delay(100);
		} else if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)){
			GPIO_SetBits(GPIOB, GPIO_Pin_15);
			Delay(100);
			a -= 10; b -= 10;
			while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15));
			Delay(100);
		}
		GPIO_ResetBits(GPIOB, GPIO_Pin_14 | GPIO_Pin_15);
		setServo(a, 2);
		setServo(b, 3);
		Delay(20);
	}
}

void Delay(__IO uint32_t nTime){
	uwTimingDelay = nTime;

	while(uwTimingDelay != 0);
}

void TimingDelay_Decrement(void){
	if (uwTimingDelay != 0x00){
		uwTimingDelay--;
	}
}

