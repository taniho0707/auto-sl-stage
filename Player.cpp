#include "Player.h"

using namespace md;

Player::Player(){
	solenoid = Solenoid::getInstance();
	motor = Motor::getInstance();
}

void Player::initialize(Score& d){
	score = d;
}

void Player::start(){
	
}
