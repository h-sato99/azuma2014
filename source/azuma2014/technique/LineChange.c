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
#define FRONT			1		// 前輪

void LineChange_init(LineChange* this)
{
	this->orderNum = NONE;
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
	// ラインの逆側へ走行する
	this->orderNum = OrderList_manualRunning(this->orderList,NORMAL,TURN,FRONT,NONE,DISTANCE);

	if(OrderList_checkFinished(this->orderList,this->orderNum))
	{
		// ラインの逆側へ走行が完了した場合、エッジ切替処理を行い、trueを返す
		// TODO エッジ切替処理が必要
		retun TRUE;
	}
	// falseを返す
	return FALSE;
}
