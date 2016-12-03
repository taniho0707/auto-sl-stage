#include "Lcd.h"

Lcd::Lcd(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_10;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	RCC_LSEConfig(RCC_LSE_OFF);
	RCC_HSEConfig(RCC_HSE_OFF);

	resetRS();
	setE();
	setBits(0x38);
	Timer::wait_ms(1);
	resetE();
	Timer::wait_ms(1);
	
	resetRS();
	setE();
	setBits(0x38);
	Timer::wait_ms(1);
	resetE();
	Timer::wait_ms(1);

	resetRS();
	setE();
	setBits(0x0F);
	Timer::wait_ms(1);
	resetE();
	Timer::wait_ms(1);

	resetRS();
	setE();
	setBits(0x01);
	Timer::wait_ms(1);
	resetE();
	Timer::wait_ms(3);

	resetRS();
	setE();
	setBits(0x06);
	Timer::wait_ms(1);
	resetE();
	Timer::wait_ms(1);

	resetRS();
	setE();
	setBits(0x80);
	Timer::wait_ms(1);
	resetE();
	Timer::wait_ms(1);
}

void Lcd::setE(){
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
}
void Lcd::resetE(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
}
void Lcd::setRS(){
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
}
void Lcd::resetRS(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}
void Lcd::setBit(uint8_t pin){
	if(pin == 0)
		GPIO_SetBits(GPIOH, GPIO_Pin_0);
	else if(pin == 1)
		GPIO_SetBits(GPIOH, GPIO_Pin_1);
	else if(pin == 2)
		GPIO_SetBits(GPIOA, GPIO_Pin_7);
	else if(pin == 3)
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
	else if(pin == 4)
		GPIO_SetBits(GPIOB, GPIO_Pin_10);
	else if(pin == 5)
		GPIO_SetBits(GPIOB, GPIO_Pin_4);
	else if(pin == 6)
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
	else if(pin == 7)
		GPIO_SetBits(GPIOB, GPIO_Pin_3);
}
void Lcd::resetBit(uint8_t pin){
	if(pin == 0)
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);
	else if(pin == 1)
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);
	else if(pin == 2)
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
	else if(pin == 3)
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	else if(pin == 4)
		GPIO_ResetBits(GPIOB, GPIO_Pin_10);
	else if(pin == 5)
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);
	else if(pin == 6)
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	else if(pin == 7)
		GPIO_ResetBits(GPIOB, GPIO_Pin_3);
}
void Lcd::setBits(uint8_t data){
	for(uint8_t i=0; i<8; ++i){
		if((data & (0x1<<i)) == 0)
			resetBit(i);
		else
			setBit(i);
	}
}


void Lcd::clear(){
	resetRS();
	setE();
	setBits(0x01);
	Timer::wait_ms(1);
	resetE();
	Timer::wait_ms(3);

	resetRS();
	setE();
	setBits(0x06);
	Timer::wait_ms(1);
	resetE();
	Timer::wait_ms(2);
}
void Lcd::printChar(const char c){
	setRS();
	setE();
	setBits(c);
	Timer::wait_ms(1);
	resetE();
	Timer::wait_ms(1);
}

void Lcd::goLineHead(const uint8_t line){
	
}


Lcd* Lcd::getInstance(){
	static Lcd instance;
	return &instance;
}
