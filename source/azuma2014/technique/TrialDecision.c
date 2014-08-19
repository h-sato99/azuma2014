/*******************************************************************************
**  ファイル名  ：TrialDecision.c
**  概要        ：難所検知クラス
**  詳細        ：
*******************************************************************************/

#include "TrialDecision.h"

#define NONE			0		// 初期値
#define TARGET			500		// 閾値
#define LOW				40		// 低速
#define NORMAL			80		// 通常
#define HIGH			120		// 高速
#define	BACK			-40		// 後退
#define BACK_DISTANCE	2000		// 走行距離(後退)
#define DASH_DISTANCE	3000		// 走行距離(加速)

typedef enum State
{
	START,
	CHECK_BUMP,
	BACK_RUN,
	DASH_RUN,
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
//		this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,LOW,NONE,NONE,NONE);
//		this->orderNum = OrderList_manualRunning(this->orderList,LOW,NONE,NONE,NONE,NONE);
//		this->mode = CHECK_BUMP;
		OrderList_manualRunning(this->orderList,LOW,NONE,TURN_DRIVING,BACK_DISTANCE,NONE);
		OrderList_manualRunning(this->orderList,BACK,NONE,TURN_DRIVING,BACK_DISTANCE,NONE);
		this->orderNum = OrderList_manualRunning(this->orderList,HIGH,TURN_DRIVING,NONE,DASH_DISTANCE,NONE);
		this->mode = DASH_RUN;
		break;

	case CHECK_BUMP:
		// 衝撃を検知したか判定する
//		if (BumpDecision_checkBump(this->bumpDecision))
//		{
			// 衝撃を検知した場合、後退走行に切り替える
			OrderList_finishOrder(this->orderList,this->orderNum);
//			this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,BACK,NONE,NONE,BACK_DISTANCE);
			this->orderNum = OrderList_manualRunning(this->orderList,BACK,NONE,NONE,BACK_DISTANCE,NONE);
			this->mode = BACK_RUN;
//		}
		break;

	case BACK_RUN:
		// 後退走行が完了したか判定する
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 後退走行が完了した場合、加速走行に切り替える
//			this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,HIGH,NONE,NONE,DASH_DISTANCE);
			this->orderNum = OrderList_manualRunning(this->orderList,HIGH,NONE,NONE,DASH_DISTANCE,NONE);
			this->mode = DASH_RUN;
		}
		break;

	case DASH_RUN:
		// 加速走行が完了したか判定する
		if (OrderList_checkFinished(this->orderList,this->orderNum))
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
//BOOL TrialDecision_action2(TrialDecision* this)
//{
//	// 低速走行に切り替える
//	this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,LOW,NONE,NONE,NONE);
//
//	while(1)
//	{
//		if(BumpDecision_checkBump(this->bumpDecision))
//		{
//			break;
//		}
//	}
//
//	// 後退走行に切り替える
//	this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,BACK,NONE,NONE,BACK_DISTANCE);
//
//	while(1)
//	{
//		if(OrderList_checkFinished(this->orderList, this->orderNum))
//		{
//			break;
//		}
//	}
//
//	// 加速走行に切り替える
//	this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,HIGH,NONE,NONE,DASH_DISTANCE);
//
//	while(1)
//	{
//		if(OrderList_checkFinished(this->orderList, this->orderNum))
//		{
//			break;
//		}
//	}
//
//	return true;
//}
