#pragma once

#include "MusicData.h"
#include "ComPc.h"
#include "Solenoid.h"
#include "Motor.h"
#include "MusicData.h"

class Player{
private:
	Solenoid* solenoid;
	Motor* motor;
	md::Score score;

	Player();

public:
	void initialize(md::Score&);
	void start();
};

