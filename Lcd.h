#pragma once

#include "stm32f4xx.h"

#include "Timer.h"

class Lcd {
private:
	explicit Lcd();

	void setE();
	void resetE();
	void setRS();
	void resetRS();
	void setBit(const uint8_t pin);
	void resetBit(const uint8_t pin);
	void setBits(const uint8_t data);

public:
	static Lcd *getInstance();

	void clear();
	void printChar(const char data);
	void goLineHead(const uint8_t line);
};

