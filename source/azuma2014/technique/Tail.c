/*******************************************************************************
**  ファイル名  ：Tail.c
**  概要        ：尻尾モータ制御クラス
**  詳細        ：
*******************************************************************************/

#include "Tail.h"

#define P_GAIN             2.5F // 完全停止用モータ制御比例係数
#define PWM_ABS_MAX          60 // 完全停止用モータ制御PWM絶対最大値


void Tail_init(Tail* this)
{
	// 処理なし
}

/*------------------------------------------------------------------------------
--  関数名      ：Tail_setAngle
--  概要        ：尻尾モータの角度を設定する。
--              ：
--  引数        ：angle   尻尾モータの角度
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Tail_setAngle(Tail* this, int angle)
{
	int pwm;

	// 比例制御
	pwm = (angle - Motor_getAngle(this->tailMotor)) * P_GAIN;

	// PWM出力飽和処理
	if (pwm > PWM_ABS_MAX)
	{
		pwm = PWM_ABS_MAX;
	}
	else if (pwm < -PWM_ABS_MAX)
	{
		pwm = -PWM_ABS_MAX;
	}

	Motor_rotate(this->tailMotor, pwm);
}

int Tail_getAngle(Tail* this)
{
	return Motor_getAngle(this->tailMotor);
}
