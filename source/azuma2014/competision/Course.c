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

// INコース部品
/*------------------------------------------------------------------------------
--  関数名      ：Course_IN_StartToCurve
--  概要        ：INスタート～第1カーブ
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_IN_StartToCurve(Course* this)
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
--  関数名      ：Course_IN_CurveToLineChange
--  概要        ：IN第1カーブ～ライン切替
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_IN_CurveToLineChange(Course* this)
{
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
					20,
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

/*------------------------------------------------------------------------------
--  関数名      ：Course_IN_LineChangeToReStart
--  概要        ：INライン切替～スタート(2周目)
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_IN_LineChangeToReStart(Course* this)
{
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
					20,
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

/*------------------------------------------------------------------------------
--  関数名      ：Course_IN_CurveToMogul
--  概要        ：IN第1カーブ(2周目)～モーグル
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_IN_CurveToMogul(Course* this)
{
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
					20,
					this->target,
					TURN_FRONT,
					0,
					1400);
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
--  関数名      ：Course_IN_MogulToManual
--  概要        ：INモーグル～マニュアル走行
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_IN_MogulToManual(Course* this)
{
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
					20,
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

/*------------------------------------------------------------------------------
--  関数名      ：Course_IN_ManualToFigureL
--  概要        ：INマニュアル走行～フィギュアL
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_IN_ManualToFigureL(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID設定
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//マニュアル走行
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_manualRunning(
					this->orderList,
					60,
					0,
					TURN_FRONT,
					0,
					800);
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
--  関数名      ：Course_IN_ManualToFigureL
--  概要        ：INフィギュアL～停止
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_IN_FigureLToStop(Course* this)
{
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
					20,
					this->target,
					TURN_FRONT,
					0,
					600);
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

// OUTコース部品
/*------------------------------------------------------------------------------
--  関数名      ：Course_OUT_StartToCurve
--  概要        ：OUTスタート～第1カーブ
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_OUT_StartToCurve(Course* this)
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
--  関数名      ：Course_OUT_CurveToJump
--  概要        ：OUT第1カーブ～ジャンプ台
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_OUT_CurveToJump(Course* this)
{
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
					600);
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
--  関数名      ：Course_OUT_JumpToDashStart
--  概要        ：OUTジャンプ台～ダッシュ開始
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_OUT_JumpToDashStart(Course* this)
{
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
					600);
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
--  関数名      ：Course_OUT_DashStartToDashEnd
--  概要        ：OUTダッシュ開始～ダッシュ終了
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_OUT_DashStartToDashEnd(Course* this)
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
					800);
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
--  関数名      ：Course_OUT_DashToPending
--  概要        ：OUTダッシュ終了～仕様未確定
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_OUT_DashEndToPending(Course* this)
{
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
					800);
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
--  関数名      ：Course_OUT_PendingToCurve
--  概要        ：OUT仕様未確定～第4カーブ
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_OUT_PendingToCurve(Course* this)
{
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
					800);
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
--  関数名      ：Course_OUT_DashStartToDashEnd
--  概要        ：OUT第4カーブ～ゴール
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Course_OUT_CurveToGoal(Course* this)
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
					800);
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
