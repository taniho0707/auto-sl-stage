#include "Servo.h"

Servo::Servo(){
	TIM_TimeBaseInitTypeDef TIM_initstr;
	TIM_OCInitTypeDef TIM_OC_initstr;
	GPIO_InitTypeDef GPIO_initstr;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	GPIO_initstr.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
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
	TIM_TimeBaseInit(TIM3, &TIM_initstr);
	TIM_TimeBaseInit(TIM5, &TIM_initstr);

	TIM_OC_initstr.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_initstr.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC_initstr.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC_initstr.TIM_Pulse = 4500-1;
	TIM_OC3Init(TIM2,&TIM_OC_initstr);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Disable);
	TIM_OC4Init(TIM3,&TIM_OC_initstr);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Disable);
	TIM_OC4Init(TIM5,&TIM_OC_initstr);
	TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Disable);

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

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM3);
	TIM_TimeBaseInit(TIM3, &TIM_initstr);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_CtrlPWMOutputs(TIM3, ENABLE);

	for(auto i=0; i<2; ++i)
		for(auto j=0; j<5; ++j)
			defaultpos[i][j] = 0;
}

void Servo::enable(ServoSide side){
	if(side == ServoSide::LEFT){
		TIM_Cmd(TIM2, ENABLE);
	} else if(side == ServoSide::FRONT){
		TIM_Cmd(TIM3, ENABLE);
	} else if(side == ServoSide::RIGHT){
		TIM_Cmd(TIM5, ENABLE);
	}
}

void Servo::disable(ServoSide side){
	if(side == ServoSide::LEFT){
		TIM_Cmd(TIM2, DISABLE);
	} else if(side == ServoSide::FRONT){
		TIM_Cmd(TIM3, DISABLE);
	} else if(side == ServoSide::RIGHT){
		TIM_Cmd(TIM5, DISABLE);
	}
}

void Servo::setAngle(int16_t angle, ServoSide side){
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

	if(side == ServoSide::LEFT){
		TIM_TimeBaseInit(TIM2, &TIM_initstr);
		TIM_OC3Init(TIM2,&TIM_OC_initstr);
		TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	} else if(side == ServoSide::FRONT){
		TIM_TimeBaseInit(TIM3, &TIM_initstr);
		TIM_OC4Init(TIM3,&TIM_OC_initstr);
		TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	} else if(side == ServoSide::RIGHT){
		TIM_TimeBaseInit(TIM5, &TIM_initstr);
		TIM_OC4Init(TIM5,&TIM_OC_initstr);
		TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable);
	}
}

void Servo::setLineDefault(
	md::noteline line, int16_t angle, ServoSide side){
	defaultpos[static_cast<uint16_t>(side)][static_cast<uint16_t>(line)] = angle;
}

void Servo::goLine(md::noteline line, ServoSide side){
	setAngle(defaultpos[static_cast<uint16_t>(side)][static_cast<uint16_t>(line)], side);
}


Servo* Servo::getInstance(){
	static Servo instance;
	return &instance;
}
