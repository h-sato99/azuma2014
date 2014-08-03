/*******************************************************************************
**  ファイル名  ：Distance.c
**  概要        ：距離測定クラス
**  詳細        ：走行体が移動した距離を測る
*******************************************************************************/

#include "Distance.h"

static int Distance_calc(Distance* this, MeasureInfo* measureInfo);

/*------------------------------------------------------------------------------
--  関数名      ：Distance_init
--  概要        ：初期化する。
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Distance_init(Distance* this)
{
	this->initDistance = 0;
}

/*------------------------------------------------------------------------------
--  関数名      ：Distance_set
--  概要        ：基準とする距離を設定する。
--              ：
--  引数        ：measureInfo 測定情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Distance_set(Distance* this, MeasureInfo* measureInfo)
{
	this->initDistance = Distance_calc(this, measureInfo);
}

/*------------------------------------------------------------------------------
--  関数名      ：Distance_check
--  概要        ：指定した距離を移動したかどうかを確認する。
--              ：
--  引数        ：measureInfo 測定情報
--              ：distance    距離
--  戻り値      ：確認結果
------------------------------------------------------------------------------*/
BOOL Distance_check(Distance* this, MeasureInfo* measureInfo, int distance)
{
	int calcWork;

	calcWork = this->initDistance - Distance_calc(this, measureInfo);

	// 絶対値にする
	if(calcWork < 0)
	{
		calcWork *= -1;
	}

	if(calcWork >= distance)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*------------------------------------------------------------------------------
--  関数名      ：Distance_calc
--  概要        ：左右モータの出力値から距離を算出する。
--              ：
--  引数        ：なし
--  戻り値      ：距離
------------------------------------------------------------------------------*/
static int Distance_calc(Distance* this, MeasureInfo* measureInfo)
{
	int calcWork;

	calcWork = (measureInfo->leftMotorAngle + measureInfo->rightMotorAngle) / 2;

	return calcWork;
}
