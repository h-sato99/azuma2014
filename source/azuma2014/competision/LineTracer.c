/*******************************************************************************
**  ファイル名  ：LineTracer.c
**  概要        ：ライントレースクラス
**  詳細        ：ラインに関連する処理を定義。
*******************************************************************************/

#include "LineTracer.h"

//static void LineTracer_checDerailment(LineTracer* this, Info* info);

// 初期化する
void LineTracer_init(LineTracer* this)
{
	this->brightness = 0;
	this->turnDeff1 = 0;
	this->turnDeff2 = 0;
	this->count = 0;
}


/*------------------------------------------------------------------------------
--  関数名      ：LineTracer_trace
--  概要        ：ライントレースを行う
--              ：
--  引数        ：info 全情報(コース情報、ライントレースフラグを使用)
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void LineTracer_trace(LineTracer* this, Info* info)
{
	int calcTurn;

	this->brightness = LightSensor_getBrightness(this->lightSensor);

	// 旋回量を取得する
	info->settingInfo->target = this->target;
	calcTurn = PidControl_calcTurn(this->pidControl, info->settingInfo, this->brightness);
	if(this->lineEge == LINE_EGE_LEFT)
	{
		// 左エッジの場合、旋回量を反転させる
		calcTurn *= -1;
	}
	this->turn = calcTurn;

	/*
	display_goto_xy(2, 4);
	display_int(calcTurn, 14);
	display_goto_xy(2, 5);
	display_int(this->target, 14);
	display_update();
	*/
	/*
	if(info->settingInfo->lineTraceFlg == TRUE)
	{
		info->runnerInfo->turn = calcTurn;
	}
	*/

	//LineTracer_checDerailment(this, info);
}

F32 LineTracer_getTurn(LineTracer* this)
{
	return this->turn;
}

void LineTracer_setTarget(LineTracer* this, float target)
{
	this->target = target;
	//ecrobot_sound_tone(659, 100, 95);
}

void LineTracer_setRightEdge(LineTracer* this)
{
	this->lineEge = LINE_EGE_RIGHT;
}

void LineTracer_setLeftEdge(LineTracer* this)
{
	this->lineEge = LINE_EGE_LEFT;
}

int LineTracer_getEdge(LineTracer* this)
{
	return this->lineEge;
}

/*------------------------------------------------------------------------------
--  関数名      ：LineTracer_checDerailment
--  概要        ：コースから脱線しているかを判断する
--              ：
--  引数        ：info 情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
/*
static void LineTracer_checDerailment(LineTracer* this, Info* info)
{
	BOOL check;

	check = FALSE;

	this->turnDeff1 = this->turnDeff2;
	this->turnDeff2 = info->runnerInfo->turn;

	if(this->turnDeff1 * this->turnDeff2 < 0)
	{
		this->count = 0;
	}
	else
	{
		this->count++;
		if(this->count > 250)
		{
			check = TRUE;
		}
	}

	// ＰＩＤ制御部品でのチェックを優先する
	check = PidControl_checDerailment(this->pidControl);

	info->measureInfo->derailmentFlag = check;
}
*/
