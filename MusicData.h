#pragma once

#include <map>
#include <stdint.h>

namespace md{

	enum class Notetype : uint8_t {
		SINGLE,
		LONG_START,
		LONG_END,
		SLIDERIGHT_CONT,
		SLIDERIGHT_END,
		SLIDELEFT_CONT,
		SLIDELEFT_END,
		ERROR = 15
	};

	enum class Noteline : uint8_t {
		LEFT,
		LEFTMIDDLE,
		MIDDLE,
		RIGHTMIDDLE,
		RIGHT,
		NONE = 7
	};

	enum class Notehand : uint8_t {
		LEFT,
		RIGHT,
		ERROR = 3
	};

	enum class Denom : uint16_t {
		FOUR = 4,
		EIGHT = 8,
		SIXTEEN = 16,
		THIRTYTWO = 32,
		SIXTYFOUR = 64,
		THREE = 3,
	};

	/* ノーツデータ
	   1. 分母
	      Denom
	   2. 分子
	      uint8_t
	   3. 小節
	      uint16_t
	   4. ノーツタイプ
	      Notetype
	   5. ノーツライン
	      Noteline
	   6. ノーツハンド
	      打鍵する腕
	*/
	struct Notedata {
		Denom denominator;
		uint8_t numerator;
		uint16_t measure;
		Notetype type;
		Noteline line;
		Notehand hand;

		uint32_t getNumber(){
			return 64*measure + (64/static_cast<uint16_t>(denominator)*numerator);
		}
	} __attribute__((packed));

	class Score {
	private:
		
	public:
		std::multimap<uint32_t, struct Notedata> notes;

		explicit Score();

		std::multimap<uint32_t, struct Notedata>::iterator addNote(struct Notedata);
		bool removeNote(uint32_t number, Noteline line);
	};
}
