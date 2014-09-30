/*******************************************************************************
**  ファイル名  ：PendingArea.c
**  概要        ：仕様未確定エリア攻略クラス
**  詳細        ：仕様未確定エリア攻略に関する処理を定義。
*******************************************************************************/
#include "PendingArea.h"

#define NONE				0		// 初期値
#define NORMAL				40		// 通常
#define TURN_LEFT			90		// 左旋回
#define TURN_RIGHT			-90		// 右旋回
#define STRAIGHT_DISTANCE	3000	// 走行距離(直進)
#define OBLIQUE_DISTANCE	5000	// 走行距離(斜め)

/*------------------------------------------------------------------------------
--  関数名      ：PendingArea_init
--  概要        ：初期化
--              ：
--  引数        ：
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void PendingArea_init(PendingArea* this)
{
	this->orderNum = NONE;
	this->mode = PENDINGAREA_START;
	this->privateMode = PENDINGAREA_START;
}

/*------------------------------------------------------------------------------
--  関数名      ：PendingArea_action
--  概要        ：仕様未確定エリア攻略
--              ：
--  引数        ：
--  戻り値      ：なし
------------------------------------------------------------------------------*/
BOOL PendingArea_action(PendingArea* this)
{
	switch(this->mode)
	{
	case PENDINGAREA_START:
		this->mode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		this->mode = PENINGAREA_FINISHED;
		break;

	case PENINGAREA_FINISHED:
		// trueを返す
		return TRUE;
	}
	// falseを返す
	return FALSE;
}

/*------------------------------------------------------------------------------
--  関数名      ：PendingArea_privateModeInit
--  概要        ：プライベートモード初期化
--              ：
--  引数        ：
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void PendingArea_privateModeInit(PendingArea* this)
{
	this->privateMode = PENDINGAREA_START;
}

/*------------------------------------------------------------------------------
--  関数名      ：PendingArea_straight
--  概要        ：直進
--              ：
--  引数        ：
--  戻り値      ：なし
------------------------------------------------------------------------------*/
BOOL PendingArea_straight(PendingArea* this)
{
	switch(this->privateMode)
	{
	case PENDINGAREA_START:
		this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, NONE, NONE, NONE, STRAIGHT_DISTANCE);
		this->mode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			this->mode = PENINGAREA_FINISHED;
		}
		break;

	case PENINGAREA_FINISHED:
		// trueを返す
		return TRUE;
	}
	// falseを返す
	return FALSE;
}

/*------------------------------------------------------------------------------
--  関数名      ：PendingArea_left
--  概要        ：左方向に直進
--              ：
--  引数        ：
--  戻り値      ：なし
------------------------------------------------------------------------------*/
BOOL PendingArea_left(PendingArea* this)
{
	switch(this->privateMode)
	{
	case PENDINGAREA_START:
//		this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, NONE, NONE, STRAIGHT_DISTANCE);
		this->mode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		this->mode = PENINGAREA_FINISHED;
		break;

	case PENINGAREA_FINISHED:
		// trueを返す
		return TRUE;
	}
	// falseを返す
	return FALSE;
}

/*------------------------------------------------------------------------------
--  関数名      ：PendingArea_right
--  概要        ：右方向に直進
--              ：
--  引数        ：
--  戻り値      ：なし
------------------------------------------------------------------------------*/
BOOL PendingArea_right(PendingArea* this)
{
	switch(this->privateMode)
	{
	case PENDINGAREA_START:
//		this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, NONE, NONE, STRAIGHT_DISTANCE);
		this->mode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		this->mode = PENINGAREA_FINISHED;
		break;

	case PENINGAREA_FINISHED:
		// trueを返す
		return TRUE;
	}
	// falseを返す
	return FALSE;
}

/*------------------------------------------------------------------------------
--  関数名      ：PendingArea_leftOblique
--  概要        ：左斜め方向に直進
--              ：
--  引数        ：
--  戻り値      ：なし
------------------------------------------------------------------------------*/
BOOL PendingArea_leftOblique(PendingArea* this)
{
	switch(this->privateMode)
	{
	case PENDINGAREA_START:
//		this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, NONE, NONE, STRAIGHT_DISTANCE);
		this->mode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		this->mode = PENINGAREA_FINISHED;
		break;

	case PENINGAREA_FINISHED:
		// trueを返す
		return TRUE;
	}
	// falseを返す
	return FALSE;
}

/*------------------------------------------------------------------------------
--  関数名      ：PendingArea_rightOblique
--  概要        ：右斜め方向に直進
--              ：
--  引数        ：
--  戻り値      ：なし
------------------------------------------------------------------------------*/
BOOL PendingArea_rightOblique(PendingArea* this)
{
	switch(this->privateMode)
	{
	case PENDINGAREA_START:
//		this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, NONE, NONE, STRAIGHT_DISTANCE);
		this->mode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		this->mode = PENINGAREA_FINISHED;
		break;

	case PENINGAREA_FINISHED:
		// trueを返す
		return TRUE;
	}
	// falseを返す
	return FALSE;
}
