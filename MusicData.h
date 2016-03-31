#pragma once

#include <vector>
#include <stdint.h>

namespace md{

	enum class notetype : unsigned char {
		SINGLE,
		LONGSTART,
		LONGEND,
		SLIDESTART,
		SLIDECONT,
		SLIDEEND,
		ERROR = 255
	};

	/* ノーツデータ
	   1. ノーツタイプ
	      4bit
	      単音，連続開始，連続終了，スライド開始，スライド継続，スライド終了
	   2. 演奏時刻
	      18bit
	      in ms
	   3. 次のノーツ番号
	      10bit
	*/
	union note {
		struct {
			unsigned type : 4;
			unsigned time : 18;
			unsigned next : 10;
		} part;
		uint32_t all;
	} __attribute__ ((__packed__));

	class MusicData {
	private:
		std::vector<union note> data;
		
	public:
		MusicData();

		bool setNote(uint16_t, uint32_t);
		uint16_t setNotes(uint16_t, uint32_t*, uint16_t);

		notetype getType(uint16_t);
		uint32_t getTime(uint16_t);
		uint16_t getNext(uint16_t);
		
		~MusicData();
	};
}
