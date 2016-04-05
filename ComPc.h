#pragma once

#include <string>
#include <cstdarg>
#include <cstdio>
#include <vector>

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"


class ComPc{
private:
	explicit ComPc();

	std::vector<uint8_t> recvdata;

public:
	uint8_t buffer[100];
	
	static ComPc *getInstance();

	void send1byte(const char data);
	void sendnbyte(const char *c, const int n);
	uint16_t printf(const char *fmt, ...);

	bool isEmpty();
	std::vector<uint8_t> getRecvData();

	void interrupt_recv();
};

