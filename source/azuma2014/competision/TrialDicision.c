/*******************************************************************************
**  ファイル名  ：TrialDicision.c
**  概要        ：難所検知クラス
**  詳細        ：
*******************************************************************************/

#include "TrialDicision.h"

#define NONE			0		// 初期値
#define TARGET			500		// 閾値
#define LOW				40		// 低速
#define NORMAL			80		// 通常
#define HIGH			120		// 高速
#define	BACK			-80		// 後退
#define BACK_DISTANCE	100		// 走行距離(後退)
#define DASH_DISTANCE	120		// 走行距離(加速)

typedef enum State
{
	START,
	CHECK_BUMP,
	BACK_RUN,
	DASH_RUN,
	FINISHED
};

void TrialDicision_init(TrialDicision* this)
{
	this->mode = START;
	this->orderNum = NONE;
}

/*------------------------------------------------------------------------------
--  関数名      ：TrialDicision_action
--  概要        ：難所検知処理を実行する
--              ：
--  引数        ：
--  戻り値      ：true(処理完了)、false(処理未完了)
------------------------------------------------------------------------------*/
BOOL TrialDicision_action(TrialDicision* this)
{
	switch(this->mode)
	{
	case START:
		// 低速走行に切り替える
		this->orderNum = OrderList_lineTraceRunning(this,TARGET,LOW,NONE,NONE,NONE);
		this->mode = CHECK_BUMP;
		break;

	case CHECK_BUMP:
		// 衝撃を検知したか判定する
		if (BumpDecision_checkBump(this))
		{
			// 衝撃を検知した場合、後退走行に切り替える
			this->orderNum = OrderList_lineTraceRunning(this,TARGET,BACK,NONE,NONE,BACK_DISTANCE);
			this->mode = BACK_RUN;
		}
		break;

	case BACK_RUN:
		// 後退走行が完了したか判定する
		if (OrderList_checkFinished(this,this->orderNum))
		{
			// 後退走行が完了した場合、加速走行に切り替える
			this->orderNum = OrderList_lineTraceRunning(this,TARGET,HIGH,NONE,NONE,DASH_DISTANCE);
			this->mode = DASH_RUN;
		}
		break;

	case DASH_RUN:
		// 加速走行が完了したか判定する
		if (OrderList_checkFinished(this,this->orderNum))
		{
			// 加速走行が完了した場合、終了処理を実行する
			this->mode = FINISHED;
		}
		break;

	case FINISHED:
		// trueを返す
		return true;
	}
	// falseを返す
	return false;
}

// 設計に基づいた実装の場合
BOOL TrialDicision_action2(TrialDicision* this)
{
	// 低速走行に切り替える
	this->orderNum = OrderList_lineTraceRunning(this,TARGET,LOW,NONE,NONE,NONE);

	while(1)
	{
		if(BumpDecision_checkBump(this))
		{
			break;
		}
	}

	// 後退走行に切り替える
	this->orderNum = OrderList_lineTraceRunning(this,TARGET,BACK,NONE,NONE,BACK_DISTANCE);

	while(1)
	{
		if(OrderList_checkFinished(this->orderNum))
		{
			break;
		}
	}

	// 加速走行に切り替える
	this->orderNum = OrderList_lineTraceRunning(this,TARGET,HIGH,NONE,NONE,DASH_DISTANCE);

	while(1)
	{
		if(OrderList_checkFinished(this->orderNum))
		{
			break;
		}
	}

	return true;
}
