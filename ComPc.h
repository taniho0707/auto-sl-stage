#pragma once

#include <string>
#include <cstdarg>
#include <cstdio>
#include <vector>

#include "stm32f4xx.h"


class ComPc {
private:
	std::vector<uint8_t> recvdata;

public:
	ComPc();
	// static ComPc* getInstance();

	void send1byte(const char);
	void sendnbyte(const char*, const int);
	uint16_t printf(const char* fmt, ...);

	bool recv1byte(uint8_t&);

	bool isEmpty();
	std::vector<uint8_t> getRecvData();

	void interrupt_recv();

};
