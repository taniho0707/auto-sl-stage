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

	Servo* srv = Servo::getInstance();
	srv->enable(ServoSide::LEFT);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_ResetBits(GPIOB, GPIO_Pin_14 | GPIO_Pin_15);

	Solenoid* solenoid = Solenoid::getInstance();
	solenoid->tap(SolenoidSide::LEFT);
	solenoid->tap(SolenoidSide::RIGHT);

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
		srv->setAngle(a, ServoSide::LEFT);
		/* setServo(b, 3); */
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

