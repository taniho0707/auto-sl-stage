#include "MusicData.h"

using namespace std;
using namespace md;

Score::Score(){
	
}

multimap<uint32_t, struct Notedata>::iterator Score::addNote(struct Notedata data){
	return notes.insert(make_pair(data.getNumber(), data));
}

bool Score::removeNote(uint32_t number, Noteline line){
	using iterator = multimap<uint32_t, struct Notedata>::iterator;
	std::pair<iterator, iterator> ret = notes.equal_range(number);
	for(iterator it = ret.first; it != ret.second; ++it) {
		if(it->second.line == line){
			notes.erase(it);
			return true;
		}
	}
	return false;
}

