#include "Player.h"

using namespace md;

Player::Player(){
	servo = Servo::getInstance();
	solenoid = Solenoid::getInstance();
	curpos[0] = 0;
	curpos[1] = 0;
	releasetime[0] = 0;
	releasetime[1] = 0;
	enabled = false;
	time = 0;
}

void Player::initialize(md::MusicData& d){
	data = d;
	endtime = data.getTime(data.size()-1) + 100;
	servo->goLine(data.getLine(curpos.at(static_cast<uint8_t>(notehand::LEFT))), ServoSide::LEFT);
	servo->goLine(data.getLine(curpos.at(static_cast<uint8_t>(notehand::RIGHT))), ServoSide::RIGHT);
}

void Player::start(){
	enabled = true;
}

bool Player::done(){
	if(enabled) return false;
	else return true;
}

void Player::interrupt(){
	if(enabled){
		// if time to tap next note
		if(data.getTime(curpos[static_cast<uint8_t>(notehand::LEFT)]) == time){
			uint16_t tmp_length = 50;
			switch(data.getType(curpos.at(static_cast<uint8_t>(notehand::LEFT)))){
			case notetype::SINGLE:
				tmp_length = 50;
				releasetime.at(static_cast<uint8_t>(notehand::LEFT)) = time + 50;
				solenoid->tap(SolenoidSide::LEFT, tmp_length);
				break;
			case notetype::LONG_START:
			case notetype::SLIDERIGHT_START:
			case notetype::SLIDELEFT_START:
				tmp_length
					= data.getTime(data.getNext(curpos.at(static_cast<uint8_t>(notehand::LEFT))))
					- data.getTime(curpos.at(static_cast<uint8_t>(notehand::LEFT)))
					+ 1;
				// @TODO
				releasetime.at(static_cast<uint8_t>(notehand::LEFT)) = time + tmp_length - 1;
				// @TODO
				solenoid->tap(SolenoidSide::LEFT, tmp_length);
				break;
			case notetype::LONG_END:
				tmp_length = 0;
				break;
			case notetype::SLIDERIGHT_CONT:
			case notetype::SLIDERIGHT_END:
				tmp_length
					= data.getTime(data.getNext(curpos.at(static_cast<uint8_t>(notehand::LEFT))))
					- data.getTime(curpos.at(static_cast<uint8_t>(notehand::LEFT)))
					+ 1;
				// @TODO
				releasetime.at(static_cast<uint8_t>(notehand::LEFT)) = time + tmp_length - 1;
				// @TODO
				solenoid->extend(SolenoidSide::LEFT, tmp_length);
				switch(data.getLine(curpos.at(static_cast<uint8_t>(notehand::LEFT)))){
				case noteline::LEFT:
					servo->goLine(noteline::LEFTMIDDLE, ServoSide::LEFT);
					break;
				case noteline::LEFTMIDDLE:
					servo->goLine(noteline::MIDDLE, ServoSide::LEFT);
					break;
				case noteline::MIDDLE:
					servo->goLine(noteline::RIGHTMIDDLE, ServoSide::LEFT);
					break;
				case noteline::RIGHTMIDDLE:
					servo->goLine(noteline::RIGHT, ServoSide::LEFT);
					break;
				case noteline::RIGHT:
					servo->goLine(noteline::MORERIGHT, ServoSide::LEFT);
					break;
				default:
					break;
				}
				break;
			case notetype::SLIDELEFT_CONT:
			case notetype::SLIDELEFT_END:
				tmp_length
					= data.getTime(data.getNext(curpos.at(static_cast<uint8_t>(notehand::LEFT))))
					- data.getTime(curpos.at(static_cast<uint8_t>(notehand::LEFT)))
					+ 1;
				// @TODO
				releasetime.at(static_cast<uint8_t>(notehand::LEFT)) = time + tmp_length - 1;
				// @TODO
				solenoid->extend(SolenoidSide::LEFT, tmp_length);
				switch(data.getLine(curpos.at(static_cast<uint8_t>(notehand::LEFT)))){
				case noteline::LEFT:
					servo->goLine(noteline::MORELEFT, ServoSide::LEFT);
					break;
				case noteline::LEFTMIDDLE:
					servo->goLine(noteline::LEFT, ServoSide::LEFT);
					break;
				case noteline::MIDDLE:
					servo->goLine(noteline::LEFTMIDDLE, ServoSide::LEFT);
					break;
				case noteline::RIGHTMIDDLE:
					servo->goLine(noteline::MIDDLE, ServoSide::LEFT);
					break;
				case noteline::RIGHT:
					servo->goLine(noteline::RIGHTMIDDLE, ServoSide::LEFT);
					break;
				default:
					break;
				}
				break;
			default:
				tmp_length = 0;
				break;
			}
			++ curpos.at(static_cast<uint8_t>(notehand::LEFT));
		}
		if(data.getTime(curpos[static_cast<uint8_t>(notehand::RIGHT)]) == time){
			uint16_t tmp_length = 50;
			switch(data.getType(curpos.at(static_cast<uint8_t>(notehand::RIGHT)))){
			case notetype::SINGLE:
				tmp_length = 50;
				releasetime.at(static_cast<uint8_t>(notehand::RIGHT)) = time + 50;
				solenoid->tap(SolenoidSide::RIGHT, tmp_length);
				break;
			case notetype::LONG_START:
			case notetype::SLIDERIGHT_START:
			case notetype::SLIDELEFT_START:
				tmp_length
					= data.getTime(data.getNext(curpos.at(static_cast<uint8_t>(notehand::RIGHT))))
					- data.getTime(curpos.at(static_cast<uint8_t>(notehand::RIGHT)))
					+ 1;
				// @TODO
				releasetime.at(static_cast<uint8_t>(notehand::RIGHT)) = time + tmp_length - 1;
				// @TODO
				solenoid->tap(SolenoidSide::LEFT, tmp_length);
				break;
			case notetype::LONG_END:
				tmp_length = 0;
				break;
			case notetype::SLIDERIGHT_CONT:
			case notetype::SLIDERIGHT_END:
				tmp_length
					= data.getTime(data.getNext(curpos.at(static_cast<uint8_t>(notehand::RIGHT))))
					- data.getTime(curpos.at(static_cast<uint8_t>(notehand::RIGHT)))
					+ 1;
				// @TODO
				releasetime.at(static_cast<uint8_t>(notehand::RIGHT)) = time + tmp_length - 1;
				// @TODO
				solenoid->extend(SolenoidSide::RIGHT, tmp_length);
				switch(data.getLine(curpos.at(static_cast<uint8_t>(notehand::RIGHT)))){
				case noteline::LEFT:
					servo->goLine(noteline::LEFTMIDDLE, ServoSide::RIGHT);
					break;
				case noteline::LEFTMIDDLE:
					servo->goLine(noteline::MIDDLE, ServoSide::RIGHT);
					break;
				case noteline::MIDDLE:
					servo->goLine(noteline::RIGHTMIDDLE, ServoSide::RIGHT);
					break;
				case noteline::RIGHTMIDDLE:
					servo->goLine(noteline::RIGHT, ServoSide::RIGHT);
					break;
				case noteline::RIGHT:
					servo->goLine(noteline::MORERIGHT, ServoSide::RIGHT);
					break;
				default:
					break;
				}
				break;
			case notetype::SLIDELEFT_CONT:
			case notetype::SLIDELEFT_END:
				tmp_length
					= data.getTime(data.getNext(curpos.at(static_cast<uint8_t>(notehand::RIGHT))))
					- data.getTime(curpos.at(static_cast<uint8_t>(notehand::RIGHT)))
					+ 1;
				// @TODO
				releasetime.at(static_cast<uint8_t>(notehand::RIGHT)) = time + tmp_length - 1;
				// @TODO
				solenoid->extend(SolenoidSide::RIGHT, tmp_length);
				switch(data.getLine(curpos.at(static_cast<uint8_t>(notehand::RIGHT)))){
				case noteline::LEFT:
					servo->goLine(noteline::MORELEFT, ServoSide::RIGHT);
					break;
				case noteline::LEFTMIDDLE:
					servo->goLine(noteline::LEFT, ServoSide::RIGHT);
					break;
				case noteline::MIDDLE:
					servo->goLine(noteline::LEFTMIDDLE, ServoSide::RIGHT);
					break;
				case noteline::RIGHTMIDDLE:
					servo->goLine(noteline::MIDDLE, ServoSide::RIGHT);
					break;
				case noteline::RIGHT:
					servo->goLine(noteline::RIGHTMIDDLE, ServoSide::RIGHT);
					break;
				default:
					break;
				}
				break;
			default:
				tmp_length = 0;
				break;
			}
			++ curpos.at(static_cast<uint8_t>(notehand::RIGHT));
		}
		
		// if time to release
		if(releasetime.at(static_cast<uint8_t>(notehand::LEFT)) == time){
			switch(data.getType(curpos.at(static_cast<uint8_t>(notehand::LEFT)) - 1)){
			case notetype::SINGLE:
			case notetype::LONG_END:
			case notetype::SLIDERIGHT_END:
			case notetype::SLIDELEFT_END:
				servo->goLine(data.getLine(curpos.at(static_cast<uint8_t>(notehand::LEFT))), ServoSide::LEFT);
				break;
			default:
				break;
			}
		}
		if(releasetime.at(static_cast<uint8_t>(notehand::RIGHT)) == time){
			switch(data.getType(curpos.at(static_cast<uint8_t>(notehand::RIGHT)) - 1)){
			case notetype::SINGLE:
			case notetype::LONG_END:
			case notetype::SLIDERIGHT_END:
			case notetype::SLIDELEFT_END:
				servo->goLine(data.getLine(curpos.at(static_cast<uint8_t>(notehand::RIGHT))), ServoSide::RIGHT);
				break;
			default:
				break;
			}
		}
		
		++ time;
		if(endtime < time) enabled = false;
	}
}
