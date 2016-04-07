#include "Player.h"


Player::Player(){
	servo = Servo::getInstance();
	solenoid = Solenoid::getInstance();
}

void Player::initialize(md::MusicData& d){
	data = d;
}

void Player::start(){
	
}
