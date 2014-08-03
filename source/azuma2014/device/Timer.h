/*******************************************************************************
**  ファイル名  ：Timer.h
**  概要        ：タイマークラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _Timer_H_
#define _Timer_H_

#include "kernel.h"
#include "ecrobot_interface.h"

// 属性を保持するための構造体の定義
typedef struct Timer
{
	U32 initTime;
} Timer;

// 公開操作
void Timer_init(Timer* this);
void Timer_set(Timer* this);
BOOL Timer_check(Timer* this, int timer);

#endif /* _Timer_H_ */
