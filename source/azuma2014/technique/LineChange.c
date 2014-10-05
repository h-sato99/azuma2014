/*******************************************************************************
**  ファイル名  ：LineChange.c
**  概要        ：ライン切替クラス
**  詳細        ：
*******************************************************************************/

#include "LineChange.h"

#define NONE			0		// 初期値
#define NORMAL			50		// 通常
#define TURN			30		// 旋回値
#define DISTANCE		3000	// 走行距離

void LineChange_init(LineChange* this)
{
	this->orderNum = NONE;
	this->mode = 0;
}

/*------------------------------------------------------------------------------
--  関数名      ：LineChange_action
--  概要        ：ライン切替処理を実行する
--              ：
--  引数        ：
--  戻り値      ：なし
------------------------------------------------------------------------------*/
BOOL LineChange_action(LineChange* this)
{
	int edge;
	int turn;
	//ecrobot_sound_tone(659, 70, 95);
	switch(this->mode)
	{
	case 0:
		// ラインの逆側へ走行する
		ecrobot_sound_tone(659, 70, 95);
		edge = LineTracer_getEdge(this->lineTracer);
		if(edge == LINE_EGE_LEFT)
		{
			turn = TURN;
		}
		else
		{
			turn = TURN * -1;
		}
		OrderList_manualRunning(this->orderList,NORMAL,turn,TURN_FRONT,NONE,DISTANCE);
		this->mode = 1;
		break;
	case 1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			if(edge == LINE_EGE_LEFT)
			{
				LineTracer_setLeftEdge(this->lineTracer);
			}
			else
			{
				LineTracer_setRightEdge(this->lineTracer);
			}
			return TRUE;
		}
		break;
	}
	/*
	// ラインの逆側へ走行する
	this->orderNum = OrderList_manualRunning(this->orderList,NORMAL,TURN,TURN_FRONT,NONE,DISTANCE);

	if(OrderList_checkFinished(this->orderList,this->orderNum))
	{
		// ラインの逆側へ走行が完了した場合、エッジ切替処理を行い、trueを返す
		// TODO エッジ切替処理が必要
		return TRUE;
	}
	*/

	// falseを返す
	return FALSE;
}
