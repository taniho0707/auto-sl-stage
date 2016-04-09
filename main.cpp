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
	srv->setLineDefault(md::noteline::MORELEFT, -50, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::LEFT, -32, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::LEFTMIDDLE, -10, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::MIDDLE, 13, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::RIGHTMIDDLE, 35, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::RIGHT, 55, ServoSide::LEFT);
	srv->setLineDefault(md::noteline::MORERIGHT, 90, ServoSide::LEFT);

	srv->setLineDefault(md::noteline::MORELEFT, -60, ServoSide::RIGHT);
	srv->setLineDefault(md::noteline::LEFT, -35, ServoSide::RIGHT);
	srv->setLineDefault(md::noteline::LEFTMIDDLE, -15, ServoSide::RIGHT);
	srv->setLineDefault(md::noteline::MIDDLE, 5, ServoSide::RIGHT);
	srv->setLineDefault(md::noteline::RIGHTMIDDLE, 28, ServoSide::RIGHT);
	srv->setLineDefault(md::noteline::RIGHT, 55, ServoSide::RIGHT);
	srv->setLineDefault(md::noteline::MORERIGHT, 80, ServoSide::RIGHT);

	Solenoid* solenoid = Solenoid::getInstance();
	solenoid->tap(SolenoidSide::LEFT);
	solenoid->tap(SolenoidSide::RIGHT);

	compc.printf("Hello auto-sl-stage\n\n");

	if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)){
		Delay(500);
		int16_t a = 0;
		int16_t b = 0;
		while(1){
			if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13)){
				Delay(100);
				a += 5;
				while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13));
				Delay(100);
			} else if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)){
				Delay(100);
				a -= 5;
				while(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7));
				Delay(100);
			}
			if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)){
				Delay(100);
				b += 5;
				while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15));
				Delay(100);
			} else if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)){
				Delay(100);
				b -= 5;
				while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1));
				Delay(100);
			}
			if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)){
				Delay(100);
				solenoid->tap(SolenoidSide::RIGHT);
				while(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
				Delay(100);
			}
			srv->setAngle(a, ServoSide::LEFT);
			srv->setAngle(b, ServoSide::RIGHT);
			compc.printf("SrvAngle LEFT: %d, RIGHT: %d\n", a, b);
			Delay(100);
		}
	}

	const uint16_t T_4 = 326;
	const uint16_t T_8 = 163;

	md::MusicData d;
	compc.printf("MusicData initializing...\n");
	d.setNoteManual(0, notetype::SINGLE, noteline::LEFT, 8, notehand::LEFT, 0); //Dummy
	d.setNoteManual(1, notetype::SINGLE, noteline::MIDDLE, 2, notehand::RIGHT, 0);
	d.setNoteManual(2, notetype::SINGLE, noteline::RIGHT, 3, notehand::RIGHT, T_4);
	d.setNoteManual(3, notetype::SINGLE, noteline::RIGHT, 4, notehand::RIGHT, T_4);
	d.setNoteManual(4, notetype::SINGLE, noteline::RIGHT, 5, notehand::RIGHT, T_4 * 2);
	d.setNoteManual(5, notetype::SINGLE, noteline::RIGHTMIDDLE, 6, notehand::RIGHT, T_8);
	d.setNoteManual(6, notetype::SINGLE, noteline::MIDDLE, 7, notehand::RIGHT, T_8);
	d.setNoteManual(7, notetype::SINGLE, noteline::LEFTMIDDLE, 10, notehand::RIGHT, T_8);
	d.setNoteManual(8, notetype::LONG_START, noteline::LEFTMIDDLE, 9, notehand::LEFT, T_4 * 2);
	d.setNoteManual(9, notetype::LONG_END, noteline::LEFT, 16, notehand::LEFT, T_4);
	d.setNoteManual(10, notetype::SINGLE, noteline::LEFTMIDDLE, 11, notehand::RIGHT, 0);
	d.setNoteManual(11, notetype::SINGLE, noteline::RIGHT, 12, notehand::RIGHT, T_8);
	d.setNoteManual(12, notetype::SINGLE, noteline::RIGHTMIDDLE, 13, notehand::RIGHT, T_4);
	d.setNoteManual(13, notetype::SINGLE, noteline::RIGHTMIDDLE, 14, notehand::RIGHT, T_4 * 2);
	d.setNoteManual(14, notetype::SINGLE, noteline::MIDDLE, 15, notehand::RIGHT, T_8);
	d.setNoteManual(15, notetype::SINGLE, noteline::LEFTMIDDLE, 17, notehand::RIGHT, T_8);
	d.setNoteManual(16, notetype::LONG_START, noteline::LEFT, 18, notehand::LEFT, T_4);
	d.setNoteManual(17, notetype::LONG_START, noteline::LEFTMIDDLE, 19, notehand::RIGHT, T_8 * 3);
	d.setNoteManual(18, notetype::LONG_END, noteline::LEFT, 20, notehand::LEFT, T_8 * 3);
	d.setNoteManual(19, notetype::LONG_END, noteline::LEFTMIDDLE, 24, notehand::RIGHT, 0);
	d.setNoteManual(20, notetype::SINGLE, noteline::LEFT, 21, notehand::LEFT, T_4);
	d.setNoteManual(21, notetype::SINGLE, noteline::LEFT, 22, notehand::LEFT, T_8);
	d.setNoteManual(22, notetype::SINGLE, noteline::LEFTMIDDLE, 23, notehand::LEFT, T_8);
	d.setNoteManual(23, notetype::SINGLE, noteline::MIDDLE, 28, notehand::LEFT, T_8);
	d.setNoteManual(24, notetype::SINGLE, noteline::RIGHT, 25, notehand::RIGHT, 0);
	d.setNoteManual(25, notetype::SINGLE, noteline::MIDDLE, 26, notehand::RIGHT, T_4);
	d.setNoteManual(26, notetype::SINGLE, noteline::RIGHTMIDDLE, 27, notehand::RIGHT, T_8);
	d.setNoteManual(27, notetype::SINGLE, noteline::RIGHT, 32, notehand::RIGHT, T_8);
	d.setNoteManual(28, notetype::SINGLE, noteline::LEFT, 29, notehand::LEFT, 0);
	d.setNoteManual(29, notetype::SINGLE, noteline::RIGHTMIDDLE, 30, notehand::LEFT, T_4);
	d.setNoteManual(30, notetype::SINGLE, noteline::MIDDLE, 31, notehand::LEFT, T_8);
	d.setNoteManual(31, notetype::SINGLE, noteline::LEFTMIDDLE, 38, notehand::LEFT, T_8);
	d.setNoteManual(32, notetype::SINGLE, noteline::RIGHT, 33, notehand::RIGHT, T_8 * 3);
	d.setNoteManual(33, notetype::LONG_START, noteline::MIDDLE, 34, notehand::RIGHT, T_4);
	d.setNoteManual(34, notetype::LONG_END, noteline::MIDDLE, 35, notehand::RIGHT, T_4 * 2);
	d.setNoteManual(35, notetype::SINGLE, noteline::LEFTMIDDLE, 36, notehand::RIGHT, T_8);
	d.setNoteManual(36, notetype::SINGLE, noteline::MIDDLE, 37, notehand::RIGHT, T_8);
	d.setNoteManual(37, notetype::SINGLE, noteline::RIGHTMIDDLE, 40, notehand::RIGHT, T_8);
	d.setNoteManual(38, notetype::LONG_START, noteline::LEFT, 39, notehand::LEFT, 0);
	d.setNoteManual(39, notetype::LONG_END, noteline::LEFT, 41, notehand::LEFT, T_4);
	d.setNoteManual(40, notetype::SINGLE, noteline::RIGHTMIDDLE, 42, notehand::RIGHT, 0);
	d.setNoteManual(41, notetype::SINGLE, noteline::LEFTMIDDLE, 43, notehand::LEFT, T_8);
	d.setNoteManual(42, notetype::SINGLE, noteline::RIGHT, 47, notehand::RIGHT, 0);
	d.setNoteManual(43, notetype::SINGLE, noteline::RIGHTMIDDLE, 44, notehand::LEFT, T_4);
	d.setNoteManual(44, notetype::SINGLE, noteline::MIDDLE, 45, notehand::LEFT, T_8);
	d.setNoteManual(45, notetype::SINGLE, noteline::LEFTMIDDLE, 46, notehand::LEFT, T_8);
	d.setNoteManual(46, notetype::LONG_START, noteline::LEFTMIDDLE, 54, notehand::LEFT, T_8);
	d.setNoteManual(47, notetype::SINGLE, noteline::RIGHT, 48, notehand::RIGHT, 0);
	d.setNoteManual(48, notetype::SINGLE, noteline::MIDDLE, 49, notehand::RIGHT, T_8);
	d.setNoteManual(49, notetype::SINGLE, noteline::RIGHTMIDDLE, 50, notehand::RIGHT, T_8 * 3);
	d.setNoteManual(50, notetype::SINGLE, noteline::RIGHTMIDDLE, 51, notehand::RIGHT, T_8 * 3);
	d.setNoteManual(51, notetype::SINGLE, noteline::RIGHT, 52, notehand::RIGHT, T_8 * 3);
	d.setNoteManual(52, notetype::SINGLE, noteline::MIDDLE, 53, notehand::RIGHT, T_8 * 3);
	d.setNoteManual(53, notetype::LONG_START, noteline::RIGHTMIDDLE, 55, notehand::RIGHT, T_8 * 3);
	d.setNoteManual(54, notetype::SLIDELEFT_END, noteline::LEFTMIDDLE, 64, notehand::LEFT, T_8 * 7);
	d.setNoteManual(55, notetype::SLIDERIGHT_END, noteline::RIGHTMIDDLE, 56, notehand::RIGHT, 0);
	d.setNoteManual(56, notetype::SLIDERIGHT_START, noteline::MIDDLE, 57, notehand::RIGHT, T_4);
	d.setNoteManual(57, notetype::SLIDERIGHT_END, noteline::RIGHTMIDDLE, 58, notehand::RIGHT, T_8 / 2);
	d.setNoteManual(58, notetype::SLIDERIGHT_START, noteline::MIDDLE, 59, notehand::RIGHT, T_4 * 3 / 4);
	d.setNoteManual(59, notetype::SLIDERIGHT_END, noteline::RIGHTMIDDLE, 60, notehand::RIGHT, T_8 / 2);
	d.setNoteManual(60, notetype::SLIDERIGHT_START, noteline::RIGHTMIDDLE, 61, notehand::RIGHT, T_4 * 3 / 4);
	d.setNoteManual(61, notetype::SLIDERIGHT_END, noteline::RIGHT, 62, notehand::RIGHT, T_8 / 2);
	d.setNoteManual(62, notetype::SLIDERIGHT_START, noteline::RIGHTMIDDLE, 63, notehand::RIGHT, T_4 * 3 / 4);
	d.setNoteManual(63, notetype::SLIDERIGHT_END, noteline::RIGHT, 65, notehand::RIGHT, T_8 / 2);
	d.setNoteManual(64, notetype::SINGLE, noteline::LEFT, 66, notehand::LEFT, T_4 * 3 / 4);
	d.setNoteManual(65, notetype::SINGLE, noteline::RIGHT, 80, notehand::RIGHT, 0);
	d.setNoteManual(66, notetype::SINGLE, noteline::MIDDLE, 67, notehand::LEFT, T_4);
//	d.setNoteManual(, notetype::, noteline::, , notehand::, T_);
	compc.printf("All data loaded.\n\n");

	Player player;
	compc.printf("Player initializing...\n");
	player.initialize(d, 60000);
	compc.printf("Player loading done\n");

	while (1){
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

