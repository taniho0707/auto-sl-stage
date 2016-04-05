#include "ComPc.h"

ComPc::ComPc(){
	for(auto i=0; i<100; ++i) buffer[i] = 0;

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
}

void ComPc::send1byte(const char data){
	USART_SendData(USART1, (uint16_t)data);
	while( USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
}
void ComPc::sendnbyte(const char *c, const int n){
	for(auto i=0; i<n; ++i) send1byte(c[i]);
}
uint16_t ComPc::printf(const char *fmt, ...){
	static char buffer[100];
	int len = 0;
	va_list ap;
	va_start(ap, fmt);
	len = vsprintf(buffer, fmt, ap);
	sendnbyte(buffer, len);
	va_end(ap);
	return len;
}

bool ComPc::isEmpty(){}
std::vector<uint8_t> ComPc::getRecvData(){}

void ComPc::interrupt_recv(){}

ComPc* ComPc::getInstance(){
	static ComPc instance;
	return &instance;
}


// void USART1_IRQn(void){
// 	static ComPc* compc = ComPc::getInstance();
// 	compc->interrupt_recv();
// }
