#include "main.h"

static __IO uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

static void Delay(__IO uint32_t nTime);


void setE(){
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
}
void resetE(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
}
void setRS(){
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
}
void resetRS(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}
void setLcdBit(uint8_t pin){
	if(pin == 0)
		GPIO_SetBits(GPIOB, GPIO_Pin_6);
	else if(pin == 1)
		GPIO_SetBits(GPIOC, GPIO_Pin_7);
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
void resetLcdBit(uint8_t pin){
	if(pin == 0)
		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	else if(pin == 1)
		GPIO_ResetBits(GPIOC, GPIO_Pin_7);
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
void setLcdBits(uint8_t data){
	for(uint8_t i=0; i<8; ++i){
		if((data & (0x1<<i)) == 0)
			resetLcdBit(i);
		else
			setLcdBit(i);
	}
}
void initLCD(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_10;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	resetRS();
	setE();
	setLcdBits(0x3C);
	Delay(1);
	resetE();
	Delay(1);
	
	resetRS();
	setE();
	setLcdBits(0x3C);
	Delay(1);
	resetE();
	Delay(1);

	resetRS();
	setE();
	setLcdBits(0x06);
	Delay(1);
	resetE();
	Delay(1);

	resetRS();
	setE();
	setLcdBits(0x01);
	Delay(1);
	resetE();
	Delay(3);

	resetRS();
	setE();
	setLcdBits(0x07);
	Delay(1);
	resetE();
	Delay(1);
}
void clearLcd(){
	resetRS();
	setE();
	setLcdBits(0x01);
	Delay(1);
	resetE();
	Delay(3);

	resetRS();
	setE();
	setLcdBits(0x02);
	Delay(1);
	resetE();
	Delay(2);
}
void printChar(uint8_t c){
	setRS();
	setE();
	setLcdBits(c);
	Delay(1);
	resetE();
	Delay(1);
}


int main(void){
	SystemInit();
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 960);

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

	Delay(500);
	initLCD();
	Delay(500);
//	clearLcd();
	printChar('H');
	printChar('e');
	printChar('l');
	printChar('l');
	printChar('o');

	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	Delay(50);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	Delay(20);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	Delay(50);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	Delay(20);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	Delay(50);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	Delay(20);

//	ComPc* compc = ComPc::getInstance();

	Servo* srv = Servo::getInstance();
	srv->enable(ServoSide::LEFT);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_ResetBits(GPIOB, GPIO_Pin_14 | GPIO_Pin_15);
	srv->setLineDefault(md::noteline::LEFT, -15, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::LEFTMIDDLE, 5, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::MIDDLE, 40, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::RIGHTMIDDLE, 60, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::RIGHT, 75, ServoSide::LEFT);

	Solenoid* solenoid = Solenoid::getInstance();
	solenoid->tap(SolenoidSide::LEFT);
	solenoid->tap(SolenoidSide::RIGHT);

	int16_t a = 0;
	int16_t b = 0;

	while (1){
		// while(1){
		// 	if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13)){
		// 		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		// 		Delay(100);
		// 		a += 5; b += 10;
		// 		while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15));
		// 		Delay(100);
		// 	} else if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)){
		// 		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		// 		Delay(100);
		// 		a -= 5; b -= 10;
		// 		while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15));
		// 		Delay(100);
		// 	}
		// 	if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)){
		// 		Delay(100);
		// 		solenoid->tap(SolenoidSide::LEFT);
		// 		while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
		// 		Delay(100);
		// 	}
		// 	GPIO_ResetBits(GPIOB, GPIO_Pin_14 | GPIO_Pin_15);
		// 	srv->setAngle(a, ServoSide::LEFT);
		// 	USART_myprintf(USART1, "SrvAngle: %d\n", a);
		// 	Delay(20);
		// }

//		compc->printf("START\n");
		srv->goLine(md::noteline::RIGHTMIDDLE, ServoSide::LEFT);
		Delay(500);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)); {
			Delay(100);
			solenoid->tap(SolenoidSide::LEFT);
			while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
			Delay(100);
		}
		srv->goLine(md::noteline::LEFTMIDDLE, ServoSide::LEFT);
		Delay(500);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)); {
			Delay(100);
			solenoid->tap(SolenoidSide::LEFT);
			while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
			Delay(100);
		}
		srv->goLine(md::noteline::MIDDLE, ServoSide::LEFT);
		Delay(500);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)); {
			Delay(100);
			solenoid->tap(SolenoidSide::LEFT);
			while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
			Delay(100);
		}
		srv->goLine(md::noteline::MIDDLE, ServoSide::LEFT);
		Delay(500);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)); {
			Delay(100);
			solenoid->tap(SolenoidSide::LEFT, 2000);
			while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
			Delay(2000);
		}
		srv->goLine(md::noteline::RIGHTMIDDLE, ServoSide::LEFT);
		Delay(500);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)); {
			Delay(100);
			solenoid->tap(SolenoidSide::LEFT);
			while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
			Delay(100);
		}
		srv->goLine(md::noteline::LEFTMIDDLE, ServoSide::LEFT);
		Delay(500);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)); {
			Delay(100);
			solenoid->tap(SolenoidSide::LEFT);
			while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
			Delay(100);
		}
		srv->goLine(md::noteline::RIGHTMIDDLE, ServoSide::LEFT);
		Delay(500);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)); {
			Delay(100);
			solenoid->tap(SolenoidSide::LEFT);
			while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
			Delay(100);
		}
		srv->goLine(md::noteline::LEFTMIDDLE, ServoSide::LEFT);
		Delay(500);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)); {
			Delay(100);
			solenoid->tap(SolenoidSide::LEFT);
			while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
			Delay(100);
		}
		srv->goLine(md::noteline::LEFTMIDDLE, ServoSide::LEFT);
		Delay(500);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)); {
			Delay(100);
			solenoid->tap(SolenoidSide::LEFT);
			while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
			Delay(100);
		}
		srv->goLine(md::noteline::RIGHTMIDDLE, ServoSide::LEFT);
		Delay(500);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)); {
			Delay(100);
			solenoid->tap(SolenoidSide::LEFT);
			while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
			Delay(100);
		}
		srv->goLine(md::noteline::RIGHTMIDDLE, ServoSide::LEFT);
		Delay(500);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)); {
			Delay(100);
			solenoid->tap(SolenoidSide::LEFT);
			while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
			Delay(100);
		}
		srv->goLine(md::noteline::MIDDLE, ServoSide::LEFT);
		Delay(500);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)); {
			Delay(100);
			solenoid->tap(SolenoidSide::LEFT, 2000);
			while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
			Delay(2000);
		}
//		compc->printf("END\n");
		while(true);
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

