#pragma once

#include "stm32f4xx.h"
#include "MusicData.h"

enum class ServoSide : uint8_t {
	LEFT,
	RIGHT,
	FRONT,
};

enum class ServoFrom : uint8_t {
	LEFT,
	RIGHT,
};

class Servo {
private:
	explicit Servo();

	int16_t defaultpos[2][7][2] = {};
	enum md::noteline last[2];

public:
	void enable(ServoSide);
	void disable(ServoSide);
	void setAngle(int16_t angle, ServoSide side);

	void setLineDefault(md::noteline line, int16_t angle, ServoSide side, ServoFrom lastside);

	void goLine(md::noteline line, ServoSide side);

	static Servo* getInstance();
};

