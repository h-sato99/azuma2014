/*******************************************************************************
**  ファイル名  ：PidControl.c
**  概要        ：PID制御クラス
**  詳細        ：PID制御を用いて旋回量を計算をする。
*******************************************************************************/

#include "PidControl.h"

#define C_DELTA_T 0.004
#define C_LIMIT 100.0
#define C_MATH -100.0

#define C_CHEK_DERAILMENT -40

/*------------------------------------------------------------------------------
--  関数名      ：PidControl_Init
--  概要        ：PID制御の計算に使用する変数を初期化する。
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void PidControl_init(PidControl* this)
{
	this->deff1 = 0.0;
	this->deff2 = 0.0;
	this->integral = 0.0;
}

F32 PidControl_MathLimit(float pid)
{
	float ret = pid;

	if (ret > C_LIMIT)
	{
		ret = C_LIMIT;

	}
	else if (ret < C_MATH)
	{
		ret = C_MATH;
	}

	return ret;
}

/*------------------------------------------------------------------------------
--  関数名      ：PidControl_CalTurn
--  概要        ：旋回量を計算をする。
--              ：
--  引数        ：settingInfo  設定情報（P・I・Dの定数、目標値を利用）
--              ：brightness   光センサーで観測した値
--  戻り値      ：なし
------------------------------------------------------------------------------*/
F32 PidControl_calcTurn(PidControl* this, SettingInfo* settingInfo, int brightness)
{
	float f_p;
	float f_i;
	float f_d;
	float f_turn;

	this->deff1 = this->deff2;
	this->deff2 = (float)(brightness - settingInfo->target);

	// 積分の近似
	this->integral += (this->deff2 + this->deff1) / 2.0 * C_DELTA_T;

	// Ｐ制御
	f_p = settingInfo->pidP * this->deff2;
	// Ｉ制御
	f_i = settingInfo->pidI * this->integral;
	// Ｄ制御
	f_d = settingInfo->pidD * (this->deff2 - this->deff1) / C_DELTA_T;

	// 旋回量の計算
	f_turn = f_p + f_i + f_d;
	return PidControl_MathLimit(f_turn);
}

/*------------------------------------------------------------------------------
--  関数名      ：PidControl_checDerailment
--  概要        ：脱線したかどうかを判定する。
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
BOOL PidControl_checDerailment(PidControl* this)
{
	if(this->deff2 < -30)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
