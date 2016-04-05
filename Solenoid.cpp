#include "Solenoid.h"

Solenoid::Solenoid(){
	activated_time[0] = 0;
	activated_time[1] = 0;

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOA, GPIO_Pin_11);
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
}

void Solenoid::tap(SolenoidSide side, uint16_t duration){
	activated_time[static_cast<uint8_t>(side)] = duration;
	if(side == SolenoidSide::LEFT)
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
	else if(side == SolenoidSide::RIGHT)
		GPIO_SetBits(GPIOA, GPIO_Pin_11);
}

void Solenoid::interrupt(){
	if(activated_time[0] > 0){
		--activated_time[0];
		if(activated_time[0] == 0)
			GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	}
	if(activated_time[1] > 0){
		--activated_time[1];
		if(activated_time[1] == 0)
			GPIO_ResetBits(GPIOA, GPIO_Pin_11);
	}
}

Solenoid* Solenoid::getInstance(){
	static Solenoid instance;
	return &instance;
}

