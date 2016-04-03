#pragma once

#include "stm32f4xx.h"

enum class ServoSide : uint8_t {
	LEFT,
	RIGHT,
	FRONT,
};

class Servo {
private:
	explicit Servo();
	
public:
	void enable(ServoSide);
	void disable(ServoSide);
	void setAngle(int16_t angle, ServoSide side);

	static Servo* getInstance();
};

