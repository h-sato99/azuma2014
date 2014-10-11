/*******************************************************************************
**  ファイル名  ：Jump.c
**  概要        ：ジャンプ台クラス
**  詳細        ：ジャンプ台攻略に関する処理を定義。
*******************************************************************************/

#include "Jump.h"

#define NONE			0		// 初期値
#define TARGET			500		// 閾値
#define LOW				30		// 低速
#define NORMAL			50		// 通常
#define	BACK			-50		// 後退
#define HOLE_DISTANCE	100		// 走行距離(穴)
#define BACK_DISTANCE	50		// 走行距離(後退)
#define FINISH_DISTANCE	150		// 走行距離(攻略)
#define STOP_TIME		2000	// 停止時間

void Jump_init(Jump* this)
{
	this->mode = START;
	this->orderNum = NONE;
}


BOOL Jump_action(Jump* this)
{
	switch(this->mode)
	{
	case START:
		// 穴検知に切り替える
		this->orderNum = OrderList_lineTraceRunning(this->orderList,LOW,TARGET,NONE,NONE,HOLE_DISTANCE);
		this->mode = CHECK_HOLE;
		break;

	case CHECK_HOLE:
		// 穴を検知したか判定する
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 穴を検知した場合、尻尾走行に切り替える
			this->orderNum = OrderList_manualRunning(this->orderList,BACK,NONE,NONE,NONE,BACK_DISTANCE);
			this->mode = TAIL_CHANGE;
		}
		break;

	case TAIL_CHANGE:
		// 尻尾走行切替が完了したか判定する
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			this->orderNum = OrderList_manualRunning(this->orderList,NORMAL,NONE,NONE,NONE,FINISH_DISTANCE);
			// 尻尾走行切替が完了した場合、尻尾走行を実行する
			this->mode = TAIL_RUN;
		}
		break;

	case TAIL_RUN:
		// 尻尾走行が完了したか判定する
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			this->orderNum = OrderList_manualRunning(this->orderList,NONE,NONE,NONE,STOP_TIME,NONE);
			// 尻尾走行が完了した場合、終了処理を実行する
			this->mode = FINISHED;
		}
		break;

	case FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 一定時間停止した場合、trueを返す
			return TRUE;
		}
	}
	// falseを返す
	return FALSE;
}

