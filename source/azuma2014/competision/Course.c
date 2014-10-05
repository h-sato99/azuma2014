/*******************************************************************************
**  ファイル名  ：Course.c
**  概要        ：
**  詳細        ：
*******************************************************************************/

#include "Course.h"
//#define C_TARGET 600
#define C_TARGET 500


/*------------------------------------------------------------------------------
--  関数名      ：Course_init
--  概要        ：コースを初期化する。
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Course_init(Course* this){
	this->orderNum = 0;
	this->mode = 0;
	this->target = C_TARGET;
}

void Course_resetMode(Course* this)
{
	//test
	//this->orderNum = OrderList_setPID(this->orderList,5,7,20);
	//test
	this->mode = 0;
}

/*------------------------------------------------------------------------------
--  関数名      ：Course_strateRunIN
--  概要        ：INスタート～モーグル
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_strateRunIN(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID設定
		this->orderNum = OrderList_setPID(this->orderList,5,7,20);
		this->mode = 1;
		break;
	case 1:
		//ライントレース走行
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
//					100,
					20,
					this->target,
					TURN_DRIVING,
					0,
					1000);
		}
		this->mode = 2;
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  関数名      ：Course_strateRunOUT
--  概要        ：OUTスタート～ジャンプ台
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_strateRunOUT(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID設定
		this->orderNum = OrderList_setPID(this->orderList,5,7,20);
		this->mode = 1;
		break;
	case 1:
		//ライントレース走行
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					100,
					this->target,
					TURN_DRIVING,
					0,
					1100);
		}
		this->mode = 2;
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  関数名      ：Course_stableRunOUT
--  概要        ：OUTジャンプ台～仕様未確定
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_stableRunOUT(Course* this){
	switch(this->mode)
	{
	case 0:
		//PID設定
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//ライントレース走行
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					40,
					this->target,
					TURN_DRIVING,
					0,
					1800);
			this->mode = 2;
		}
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  関数名      ：Course_stableRunO
--  概要        ：
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_stableRunIN(Course* this){
	switch(this->mode)
	{
	case 0:
		//PID設定
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//ライントレース走行
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
//					20,
					0,
					this->target,
					TURN_FRONT,
					0,
					1800);
			this->mode = 2;
		}
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}
