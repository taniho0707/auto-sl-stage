#pragma once

#include "stm32f4xx.h"

enum class SolenoidSide : uint8_t {
	LEFT,
	RIGHT,
};

class Solenoid {
private:
	explicit Solenoid();

	uint16_t activated_time[2];

public:
	void tap(SolenoidSide, uint16_t duration = 10);

	void interrupt();
	static Solenoid* getInstance();
};
