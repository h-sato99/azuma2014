/*******************************************************************************
**  ファイル名  ：LineTracer.c
**  概要        ：ライントレースクラス
**  詳細        ：ラインに関連する処理を定義。
*******************************************************************************/

#include "LineTracer.h"

static void LineTracer_checDerailment(LineTracer* this, Info* info);

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
	calcTurn = PidControl_calcTurn(this->pidControl, info->settingInfo, this->brightness);
	if(info->settingInfo->lineTraceFlg == TRUE)
	{
		info->runnerInfo->turn = calcTurn;
	}

	LineTracer_checDerailment(this, info);
}

/*------------------------------------------------------------------------------
--  関数名      ：LineTracer_checDerailment
--  概要        ：コースから脱線しているかを判断する
--              ：
--  引数        ：info 情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
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

