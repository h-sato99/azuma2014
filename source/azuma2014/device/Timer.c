/*******************************************************************************
**  ファイル名  ：Timer.c
**  概要        ：タイマークラス
**  詳細        ：
*******************************************************************************/

#include "Timer.h"



void Timer_init(Timer* this)
{
	this->initTime = 0;
}

// タイマーをセット
void Timer_set(Timer* this)
{
	this->initTime = systick_get_ms();
}


// セットした時間が経過したかどうかを判定
BOOL Timer_check(Timer* this, int timer)
{
	U32 nowTime;

	nowTime = systick_get_ms();

	if(nowTime - this->initTime >= timer)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
