/*******************************************************************************
**  ファイル名  ：Jump.c
**  概要        ：ジャンプ台クラス
**  詳細        ：ジャンプ台攻略に関する処理を定義。
*******************************************************************************/

#include "Jump.h"

#define NONE			0		// 初期値
#define TARGET			500		// 閾値
#define LOW				40		// 低速
#define NORMAL			80		// 通常
#define HIGH			120		// 高速
#define	BACK			-80		// 後退
#define HOLE_DISTANCE	100		// 走行距離(穴)
#define FINISH_DISTANCE	120		// 走行距離(攻略)

typedef enum State
{
	START,
	CHECK_HOLE,
	DASH_RUN,
	FINISHED
} State;

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
		this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,NORMAL,NONE,NONE,HOLE_DISTANCE);
		this->mode = CHECK_HOLE;
		break;

	case CHECK_HOLE:
		// 穴を検知したか判定する
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// 穴を検知した場合、加速走行に切り替える
			this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,HIGH,NONE,NONE,FINISH_DISTANCE);
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

