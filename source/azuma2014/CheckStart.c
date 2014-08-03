/*******************************************************************************
**  ファイル名  ：CheckStart.c
**  概要        ：スタート判定クラス
**  詳細        ：スタートの判定を行う
*******************************************************************************/

#include "CheckStart.h"

static void CheckStart_start(CheckStart* this, Info* info);

// 初期化する
void CheckStart_init(CheckStart* this)
{
	this->started = 0;
}

/*------------------------------------------------------------------------------
--  関数名      ：CheckStart_isStart
--  概要        ：スタートしたかどうかを返す
--              ：
--  引数        ：なし
--  戻り値      ：スタート状態 (TRUE スタート / FALSE 未スタート)
------------------------------------------------------------------------------*/
BOOL CheckStart_isStart(CheckStart* this)
{
	if(this->started == 1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*------------------------------------------------------------------------------
--  関数名      ：CheckStart_waitStart
--  概要        ：スタートの合図があるまで待機する
--              ：
--  引数        ：info 全情報(スタートフラグを使用)
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void CheckStart_waitStart(CheckStart* this, Info* info)
{
	if(this->started == 1)
	{
		return;
	}
	// タッチセンサが押されるまで、待ち続ける
	// 完全倒立状態にする
	Tail_setAngle(this->tail, info->runnerInfo->tail);

	if(info->startFlag == TRUE)
	{
		CheckStart_start(this, info);
	}

	if(TouchSensor_isPressed(this->touchSensor))
	{
		CheckStart_start(this, info);
	}
}

/*------------------------------------------------------------------------------
--  関数名      ：CheckStart_start
--  概要        ：スタートの合図を受けたときに実行する
--              ：
--  引数        ：info 全情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void CheckStart_start(CheckStart* this, Info* info)
{
	ecrobot_sound_tone(659, 100, 70);
	this->started = 1;
	info->runnerInfo->tail = 0;
	info->strategyState = 9;
	if(info->autoStrategyFlag == TRUE)
	{
		info->strategyState = 1;
	}
}

