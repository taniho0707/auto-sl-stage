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


using namespace md;

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

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

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

	// ComPc* compc = ComPc::getInstance();
	ComPc compc;

	Servo* srv = Servo::getInstance();
	srv->enable(ServoSide::LEFT);
	srv->enable(ServoSide::RIGHT);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_ResetBits(GPIOB, GPIO_Pin_14 | GPIO_Pin_15);
	srv->setAngle(-40, ServoSide::LEFT);
	srv->setAngle(45, ServoSide::RIGHT);
	srv->setLineDefault(md::noteline::LEFT, -5, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::LEFTMIDDLE, 25, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::MIDDLE, 40, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::RIGHTMIDDLE, 65, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::RIGHT, 85, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::LEFT, -85, ServoSide::RIGHT);
	srv->setLineDefault(md::noteline::LEFTMIDDLE, -55, ServoSide::RIGHT);
	srv->setLineDefault(md::noteline::MIDDLE, -35, ServoSide::RIGHT);
	srv->setLineDefault(md::noteline::RIGHTMIDDLE, -7, ServoSide::RIGHT);
	srv->setLineDefault(md::noteline::RIGHT, 20, ServoSide::RIGHT);

	Solenoid* solenoid = Solenoid::getInstance();
	solenoid->tap(SolenoidSide::LEFT);
	solenoid->tap(SolenoidSide::RIGHT);

	compc.printf("Hello auto-sl-stage\n\n");

	const uint16_t T_4 = 320;
	const uint16_t T_8 = 160;

	md::MusicData d;
	compc.printf("MusicData initializing...\n");
	d.setNoteManual(0, notetype::SINGLE, noteline::LEFT, 8, notehand::LEFT, 0);
	d.setNoteManual(1, notetype::SINGLE, noteline::RIGHT, 1, notehand::RIGHT, 0);
	d.setNoteManual(2, notetype::SINGLE, noteline::RIGHT, 2, notehand::RIGHT, T_4);
	d.setNoteManual(3, notetype::SINGLE, noteline::RIGHT, 3, notehand::RIGHT, T_4);
	d.setNoteManual(4, notetype::SINGLE, noteline::RIGHT, 4, notehand::RIGHT, T_4 * 2);
	d.setNoteManual(5, notetype::SINGLE, noteline::RIGHTMIDDLE, 5, notehand::RIGHT, T_8);
	d.setNoteManual(6, notetype::SINGLE, noteline::MIDDLE, 6, notehand::RIGHT, T_8);
	d.setNoteManual(7, notetype::SINGLE, noteline::LEFTMIDDLE, 10, notehand::RIGHT, T_8);
	d.setNoteManual(8, notetype::SINGLE, noteline::LEFTMIDDLE, 11, notehand::LEFT, 0);
	compc.printf("All data loaded.\n\n");

	Player player;
	compc.printf("Player initializing...\n");
	player.initialize(d);
	compc.printf("Player loading done\n");

	while (1){
		// int16_t a = 0;
		// int16_t b = 0;
		// while(1){
		// 	if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13)){
		// 		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		// 		Delay(100);
		// 		a += 5; b += 5;
		// 		while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15));
		// 		Delay(100);
		// 	} else if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)){
		// 		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		// 		Delay(100);
		// 		a -= 5; b -= 5;
		// 		while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15));
		// 		Delay(100);
		// 	}
		// 	if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)){
		// 		Delay(100);
		// 		solenoid->tap(SolenoidSide::RIGHT);
		// 		while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
		// 		Delay(100);
		// 	}
		// 	GPIO_ResetBits(GPIOB, GPIO_Pin_14 | GPIO_Pin_15);
		// 	srv->setAngle(a, ServoSide::LEFT);
		// 	// srv->setAngle(b, ServoSide::RIGHT);
		// 	// USART_myprintf(USART1, "SrvAngle: %d\n", a);
		// 	Delay(20);
		// }

		Delay(500);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
		player.start();
		while(true){
			player.interrupt();
			Delay(1);
			if(player.done()) break;
		}

		compc.printf("DONE!\n");
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

