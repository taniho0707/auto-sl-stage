/**
 * @file Motor.cpp
 */

#include "Motor.h"

Motor::Motor() :
	MAX_PERIOD(336-1)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	GPIO_ResetBits(GPIOC, GPIO_Pin_15);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_Period = MAX_PERIOD; // 250kHz
	TIM_InitStructure.TIM_Prescaler = 0;
	TIM_InitStructure.TIM_ClockDivision = 0;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
	TIM_TimeBaseInit(TIM5, &TIM_InitStructure);

	TIM_OCInitTypeDef TIM_OC_InitStructure;
	TIM_OC_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC_InitStructure.TIM_Pulse = 0;
	TIM_OC3Init(TIM2,&TIM_OC_InitStructure);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC4Init(TIM5,&TIM_OC_InitStructure);
	TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM5);

	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
	TIM_TimeBaseInit(TIM5, &TIM_InitStructure);

	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_CtrlPWMOutputs(TIM2, ENABLE);
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_CtrlPWMOutputs(TIM3, ENABLE);

	enabled = false;
}

void Motor::setForward(MotorSide side){
	if(side == MotorSide::LEFT)
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);
	else
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
}

void Motor::setBackward(MotorSide side){
	if(side == MotorSide::LEFT)
		GPIO_SetBits(GPIOC, GPIO_Pin_15);
	else
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
}


void Motor::enable(){
	GPIO_SetBits(GPIOC, GPIO_Pin_15);
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM5, ENABLE);
	enabled = true;
}

void Motor::disable(){
	GPIO_ResetBits(GPIOC, GPIO_Pin_15);
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM5, ENABLE);
	enabled = false;
}

bool Motor::isEnabled(){
	return enabled;
}

void Motor::setDuty(MotorSide side, int16_t duty){
	int16_t duty_t;
	if(duty < 0){
		setBackward(side);
		duty_t = -1 * duty;
	} else {
		setForward(side);
		duty_t = duty;
	}
	if(duty_t > MAX_PERIOD) duty_t = MAX_PERIOD;
	static TIM_OCInitTypeDef TIM_OC_InitStructure;
	TIM_OC_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC_InitStructure.TIM_Pulse = duty_t;
	if(side == MotorSide::LEFT){
		TIM_OC3Init(TIM2,&TIM_OC_InitStructure);
		TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	} else {
		TIM_OC4Init(TIM5,&TIM_OC_InitStructure);
		TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable);
	}
}

Motor* Motor::getInstance(){
	static Motor instance;
	return &instance;
}
