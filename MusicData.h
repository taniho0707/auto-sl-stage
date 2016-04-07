#pragma once

#include <vector>
#include <stdint.h>

namespace md{

	enum class notetype : unsigned char {
		SINGLE,
		LONG_START,
		LONG_END,
		SLIDERIGHT_START,
		SLIDERIGHT_CONT,
		SLIDERIGHT_END,
		SLIDELEFT_START,
		SLIDELEFT_CONT,
		SLIDELEFT_END,
		ERROR = 15
	};

	enum class noteline : uint8_t {
		LEFT,
		LEFTMIDDLE,
		MIDDLE,
		RIGHTMIDDLE,
		RIGHT,
		MORELEFT,
		MORERIGHT,
		NONE = 7
	};

	enum class notehand : uint8_t {
		LEFT,
		RIGHT,
		ERROR = 3
	};

	enum class notetap : uint8_t {
		TAP,
		NOTAP,
		ERROR = 3
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
	   4. 演奏腕
	      1bit
	      右，左
	   5. ノーツライン
	      3bit
	   6. 打鍵有無
	      1bit
	      あり，なし
	*/
	struct note {
		unsigned type : 4;
		unsigned time : 18;
		unsigned next : 10;
		unsigned hand : 2;
		unsigned line : 3;
		unsigned tap : 2;
		unsigned : 25;
	} __attribute__ ((__packed__));

	class MusicData {
	private:
		std::vector<struct note> data;
		
	public:
		MusicData();

		bool setNote(uint16_t, struct note);
		uint16_t setNotes(uint16_t, struct note*, uint16_t);

		notetype getType(uint16_t);
		uint32_t getTime(uint16_t);
		uint16_t getNext(uint16_t);
		notehand getHand(uint16_t);
		noteline getLine(uint16_t);
		notetap getTap(uint16_t);
		
		~MusicData();
	};
}
