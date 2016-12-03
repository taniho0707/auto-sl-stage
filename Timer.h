/**
 * @file Timer.hpp
 * 正確に秒数を計ることを担ったクラス
 */
#pragma once

#include "stm32f4xx.h"

/**
 * 正確に秒数を計ることを担ったクラス
 */
class Timer{
private:
	static __IO int32_t total;
	static __IO int32_t waitnum;

	Timer();

public:
	/**
	 * @brief 指定時間待つ。時間経過後に関数から抜ける
	 * @param t 待機する時間(ms)
	 */
	static void wait_ms(__IO int32_t t);

	static void wait_ms_decrement();

	static int32_t getTime();

	/**
	 * @brief タイマーの加算を行う。<br>
	 * 正確に1msごとに呼ばれる必要がある。
	 */
	static void interrupt();


};
