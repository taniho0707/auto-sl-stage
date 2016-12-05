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

	/* PWR and BKP Periph clock enable */
	// RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB2Periph_BKP, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	/* GPIOC Periph clock enable */
	// RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	RCC_LSEConfig(RCC_LSE_OFF); // Disable LSE - PC14 PC15 as GPIO
	RCC_HSEConfig(RCC_HSE_OFF);
	// /* Configure PC14 and PC15 in output pushpull mode */
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	// GPIO_Init(GPIOC, &GPIO_InitStructure);

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

	ComPc* compc = ComPc::getInstance();
	// compc->printf("Welcome to auto-sl-stage\n");

	Motor* motor = Motor::getInstance();
	motor->enable();
	motor->setDuty(MotorSide::LEFT, 50);
	motor->setDuty(MotorSide::RIGHT, 50);

	Solenoid* solenoid = Solenoid::getInstance();
	solenoid->tap(SolenoidSide::LEFT);
	solenoid->tap(SolenoidSide::RIGHT);

	while (1){
		
	}
}

