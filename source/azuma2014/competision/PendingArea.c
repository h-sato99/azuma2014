/*******************************************************************************
**  ファイル名  ：PendingArea.c
**  概要        ：仕様未確定エリア攻略クラス
**  詳細        ：仕様未確定エリア攻略に関する処理を定義。
*******************************************************************************/
#include "PendingArea.h"

#define NONE						0		// 初期値
#define NORMAL						40		// 通常
#define TURN_LEFT_ANGLE				100		// 左旋回
#define TURN_RIGHT_ANGLE			-10		// 右旋回
#define TURN_LEFT_OBLIQUE_ANGLE		50		// 左斜め旋回
#define TURN_RIGHT_OBLIQUE_ANGLE	-50		// 右斜め旋回
#define STRAIGHT_DISTANCE			30		// 走行距離(直進)
#define OBLIQUE_DISTANCE			50		// 走行距離(斜め)
#define TURN_DISTANCE 				60		// 走行距離(その場旋回)
#define STOP_TIME 					3000	// 停止時間

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
		PendingArea_privateModeInit(this);
		this->mode = PENDINGAREA_CHECK_POINT1;
		break;
	case PENDINGAREA_CHECK_POINT1:
		if(PendingArea_leftOblique(this))
		{
			ecrobot_sound_tone(800, 200, 95);
			this->mode = PENDINGAREA_CHECK_POINT1;
		}
		break;
	case PENDINGAREA_CHECK_POINT2:
		if(PendingArea_rightOblique(this))
		{
			ecrobot_sound_tone(800, 200, 95);
			this->orderNum = OrderList_manualRunning(this->orderList,NONE,NONE,NONE,STOP_TIME,NONE);
			this->mode = PENINGAREA_FINISHED;
		}
		break;
	case PENINGAREA_FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			ecrobot_sound_tone(800, 200, 95);
			return TRUE;
		}
	}
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
		// 直進する
		this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, NONE, NONE, NONE, STRAIGHT_DISTANCE);
		this->privateMode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 直進が完了した場合、終了処理を実行する
			this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, TURN_INIT, STOP_TIME, NONE);
			this->privateMode = PENINGAREA_FINISHED;
		}
		break;

	case PENINGAREA_FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// trueを返す
			return TRUE;
		}
		break;
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
		// 左旋回する
		this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_LEFT_ANGLE, TURN_LEFT, NONE, TURN_DISTANCE);
		this->privateMode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 左旋回が完了した場合、直進する
			this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, NONE, NONE, NONE, STRAIGHT_DISTANCE);
			this->privateMode = PENDINGAREA_CHECK_POINT2;
		}
		break;

	case PENDINGAREA_CHECK_POINT2:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 直進が完了した場合、右旋回する
			this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_RIGHT_ANGLE, TURN_RIGHT, NONE, TURN_DISTANCE);
			this->privateMode = PENINGAREA_FINISHED;
		}
		break;

	case PENDINGAREA_CHECK_POINT3:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 右旋回が完了した場合、終了処理を実行する
			this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, TURN_INIT, STOP_TIME, NONE);
			this->privateMode = PENINGAREA_FINISHED;
		}
		break;

	case PENINGAREA_FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// trueを返す
			return TRUE;
		}
		break;
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
		// 右旋回する
		this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_RIGHT_ANGLE, TURN_RIGHT, NONE, TURN_DISTANCE);
		this->privateMode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 右旋回が完了した場合、直進する
			this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, NONE, NONE, NONE, STRAIGHT_DISTANCE);
			this->privateMode = PENDINGAREA_CHECK_POINT2;
		}
		break;

	case PENDINGAREA_CHECK_POINT2:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 直進が完了した場合、左旋回する
			this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_LEFT_ANGLE, TURN_LEFT, NONE, TURN_DISTANCE);
			this->privateMode = PENINGAREA_FINISHED;
		}
		break;

	case PENDINGAREA_CHECK_POINT3:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 左旋回が完了した場合、終了処理を実行する
			this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, TURN_INIT, STOP_TIME, NONE);
			this->privateMode = PENINGAREA_FINISHED;
		}
		break;

	case PENINGAREA_FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// trueを返す
			return TRUE;
		}
		break;
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
		// 左斜めに旋回しつつ前進する
		this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_LEFT_OBLIQUE_ANGLE, TURN_FRONT, NONE, STRAIGHT_DISTANCE);
		this->privateMode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 左斜め旋回が完了した場合、右斜めに旋回しつつ直進する
			this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_RIGHT_OBLIQUE_ANGLE, TURN_FRONT, NONE, STRAIGHT_DISTANCE);
			this->privateMode = PENDINGAREA_CHECK_POINT2;
		}
		break;

	case PENDINGAREA_CHECK_POINT2:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 右斜め旋回が完了した場合、終了処理を実行する
			this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, TURN_INIT, STOP_TIME, NONE);
			this->privateMode = PENINGAREA_FINISHED;
		}
		break;

	case PENINGAREA_FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// trueを返す
			return TRUE;
		}
		break;
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
		// 右斜めに旋回しつつ前進する
		this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_RIGHT_OBLIQUE_ANGLE, TURN_FRONT, NONE, STRAIGHT_DISTANCE);
		this->privateMode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 右斜め旋回が完了した場合、左斜めに旋回しつつ直進する
			this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_LEFT_OBLIQUE_ANGLE, TURN_FRONT, NONE, STRAIGHT_DISTANCE);
			this->privateMode = PENDINGAREA_CHECK_POINT2;
		}
		break;

	case PENDINGAREA_CHECK_POINT2:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 左斜め旋回が完了した場合、終了処理を実行する
			this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, TURN_INIT, STOP_TIME, NONE);
			this->privateMode = PENINGAREA_FINISHED;
		}
		break;

	case PENINGAREA_FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// trueを返す
			return TRUE;
		}
		break;
	}
	// falseを返す
	return FALSE;
}
