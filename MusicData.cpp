#include "MusicData.h"

using namespace std;

md::MusicData::MusicData(){
	
}

md::MusicData::~MusicData(){
	
}

bool md::MusicData::setNote(uint16_t num, struct note d){
	if(data.size() < num) data.resize(num);
	data.at(num) = d;
	return true;
}

uint16_t md::MusicData::setNotes(uint16_t start, struct note* d, uint16_t length){
	if(data.size() < start+length) data.resize(start+length);
	for(auto i = 0; i < length; ++i)
		setNote(start+i, d[i]);
	return length;
}

md::notetype md::MusicData::getType(uint16_t num){
	if(data.size() < num) return md::notetype::ERROR;
	auto ret = data.at(num).type;
	return static_cast<md::notetype>(ret);
}

uint32_t md::MusicData::getTime(uint16_t num){
	if(data.size() < num) return 4294967295;
	return data.at(num).time;
}

uint16_t md::MusicData::getNext(uint16_t num){
	if(data.size() < num) return 65535;
	return data.at(num).next;
}

md::notehand md::MusicData::getHand(uint16_t num){
	if(data.size() < num) return md::notehand::ERROR;
	return static_cast<md::notehand>(data.at(num).hand);
}

md::noteline md::MusicData::getLine(uint16_t num){
	if(data.size() < num) return md::noteline::NONE;
	return static_cast<md::noteline>(data.at(num).line);

}

