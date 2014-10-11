/*******************************************************************************
**  ファイル名  ：TrialDecision.c
**  概要        ：難所検知クラス
**  詳細        ：
*******************************************************************************/

#include "TrialDecision.h"

#define NONE			0		// 初期値
#define TARGET			550		// 閾値
#define LOW				25		// 低速
#define NORMAL			50		// 通常
#define HIGH			100		// 高速
#define	BACK			-40		// 後退
#define BACK_DISTANCE	100		// 走行距離(後退)
#define DASH_DISTANCE	140		// 走行距離(加速)
#define STOP_TIME		2000	// 停止時間

typedef enum State
{
	START,
	CHECK_BUMP,
	BACK_RUN,
	TAIL_CHANGE,
	FINISHED
} State;

void TrialDecision_init(TrialDecision* this)
{
	this->mode = START;
	this->orderNum = NONE;
}

/*------------------------------------------------------------------------------
--  関数名      ：TrialDecision_action
--  概要        ：難所検知処理を実行する
--              ：
--  引数        ：
--  戻り値      ：true(処理完了)、false(処理未完了)
------------------------------------------------------------------------------*/
BOOL TrialDecision_action(TrialDecision* this)
{
	switch(this->mode)
	{
	case START:
		// 低速走行に切り替える
		this->orderNum = OrderList_lineTraceRunning(this->orderList,LOW,TARGET,TURN_FRONT,NONE,NONE);
		this->mode = CHECK_BUMP;
		break;

	case CHECK_BUMP:
		// 衝撃を検知したか判定する
		if (BumpDecision_checkBump(this->bumpDecision))
		{
			// 衝撃を検知した場合、後退走行に切り替える
			OrderList_finishOrder(this->orderList,this->orderNum);
			this->orderNum = OrderList_manualRunning(this->orderList,BACK,NONE,NONE,NONE,BACK_DISTANCE);
			this->mode = BACK_RUN;
		}
		break;

	case BACK_RUN:
		// 後退走行が完了したか判定する
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 後退走行が完了した場合、加速走行に切り替える
			this->orderNum = OrderList_manualRunning(this->orderList,HIGH,NONE,NONE,NONE,DASH_DISTANCE);
			this->mode = TAIL_CHANGE;
		}
		break;

	case TAIL_CHANGE:
		// 加速走行が完了したか判定する
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 加速走行が完了した場合、終了処理を実行する
			this->orderNum = OrderList_manualRunning(this->orderList,NONE,NONE,NONE,STOP_TIME,NONE);
			this->mode = FINISHED;
		}
		break;

	case FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 一定時間停止した場合、trueを返す
			return TRUE;
		}
		break;
	}
	// falseを返す
	return FALSE;
}
