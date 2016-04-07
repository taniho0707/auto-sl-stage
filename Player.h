#pragma once

#include "MusicData.h"
#include "ComPc.h"
#include "Servo.h"
#include "Solenoid.h"


class Player{
private:
	Servo* servo;
	Solenoid* solenoid;
	md::MusicData data;

	Player();

public:
	void initialize(md::MusicData&);
	void start();
};

