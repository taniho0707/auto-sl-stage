#include "MusicData.h"

using namespace std;

md::MusicData::MusicData(){
	
}

md::MusicData::~MusicData(){
	
}

bool md::MusicData::setNote(uint16_t num, uint32_t d){
	if(data.size() < num) return false;
	data.at(num).all = d;
	return true;
}

uint16_t md::MusicData::setNotes(uint16_t start, uint32_t* d, uint16_t length){
	data.resize(start+length);
	for(auto i = 0; i < length; ++i)
		setNote(start+i, d[i]);
	return length;
}

md::notetype md::MusicData::getType(uint16_t num){
	if(data.size() < num) return md::notetype::ERROR;
	auto ret = data.at(num).part.type;
	return static_cast<md::notetype>(ret);
}

uint32_t md::MusicData::getTime(uint16_t num){
	if(data.size() < num) return 4294967295;
	return data.at(num).part.time;
}

uint16_t md::MusicData::getNext(uint16_t num){
	if(data.size() < num) return 65535;
	return data.at(num).part.next;
}

