#pragma once

#include <array>

#include "ComPc.h"

#include "MusicData.h"
#include "ComPc.h"
#include "Servo.h"
#include "Solenoid.h"


class Player{
private:
	Servo* servo;
	Solenoid* solenoid;
	md::MusicData data;
	ComPc cp;

	std::array<uint16_t, 2> curpos;
	std::array<uint16_t, 2> releasetime;

	uint32_t time;
	bool enabled;
	uint32_t endtime;

public:
	Player();

	void initialize(md::MusicData&);
	void start();
	bool done();

	void interrupt();
};

