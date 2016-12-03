#include "main.h"

RCC_ClocksTypeDef RCC_Clocks;


int main(void){
	SystemInit();
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

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
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	Timer::wait_ms(500);
	Lcd* lcd = Lcd::getInstance();
	Timer::wait_ms(500);

	lcd->printChar('H');
	lcd->printChar('e');
	lcd->printChar('l');
	lcd->printChar('l');
	lcd->printChar('o');
	lcd->printChar(' ');
	lcd->printChar('I');
	lcd->printChar('M');
	lcd->printChar('@');
	lcd->printChar('S');
	lcd->printChar(' ');
	lcd->printChar('S');
	lcd->printChar('S');
	Timer::wait_ms(100);

	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	Timer::wait_ms(50);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	Timer::wait_ms(20);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	Timer::wait_ms(50);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	Timer::wait_ms(20);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	Timer::wait_ms(50);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	Timer::wait_ms(20);

//	ComPc* compc = ComPc::getInstance();

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_1);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC, GPIO_Pin_15);
	while(true);

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_Period = 336-1; // 250kHz
	TIM_InitStructure.TIM_Prescaler = 0;
	TIM_InitStructure.TIM_ClockDivision = 0;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);

	TIM_OCInitTypeDef TIM_OC_InitStructure;
	TIM_OC_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC_InitStructure.TIM_Pulse = 100;
	TIM_OC4Init(TIM2,&TIM_OC_InitStructure);
	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM2);
	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_CtrlPWMOutputs(TIM2, ENABLE);

	TIM_Cmd(TIM2, ENABLE);
	while(true);

	Solenoid* solenoid = Solenoid::getInstance();
	solenoid->tap(SolenoidSide::LEFT);
	solenoid->tap(SolenoidSide::RIGHT);

	int16_t a = 0;
	int16_t b = 0;

	while (1){
		
	}
}

