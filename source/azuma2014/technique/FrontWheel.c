/*******************************************************************************
**  ファイル名  ：FrontWheel.c
**  概要        ：尻尾モータ制御クラス
**  詳細        ：
*******************************************************************************/

#include "FrontWheel.h"

#define P_GAIN             10.0F // 完全停止用モータ制御比例係数
//#define PWM_ABS_MAX          900 // 完全停止用モータ制御PWM絶対最大値
#define PWM_ABS_MAX          100 // 完全停止用モータ制御PWM絶対最大値
#define C_ANGLE              3.5
#define C_PWM                3.5
//#define C_PWM                10

void FrontWheel_init(FrontWheel* this)
{
	// 処理なし
}

/*------------------------------------------------------------------------------
--  関数名      ：FrontWheel_setAngle
--  概要        ：尻尾モータの角度を設定する。
--              ：
--  引数        ：angle   尻尾モータの角度
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void FrontWheel_setAngle(FrontWheel* this, int angle)
{
	int pwm;

	pwm = angle;

	// 比例制御
//	pwm = (angle * 10 - Motor_getAngle(this->frontMotor)) * P_GAIN;
//	pwm = (angle * 3 - Motor_getAngle(this->frontMotor)) / 3;
//	pwm = (angle * 3 - Motor_getAngle(this->frontMotor)) / 2;
//	pwm = (angle * 3 - Motor_getAngle(this->frontMotor));
//	pwm = (angle * 3 - Motor_getAngle(this->frontMotor)) * 3;
//	pwm = (angle * 3.3 - Motor_getAngle(this->frontMotor)) * 3;
	pwm = (angle * C_ANGLE - Motor_getAngle(this->frontMotor)) * C_PWM;

	/*
	display_goto_xy(2, 1);
	display_int(angle, 14);
	display_goto_xy(2, 2);
	display_int(pwm, 14);
	display_update();
	*/

	// PWM出力飽和処理
	if (pwm > PWM_ABS_MAX)
	{
		pwm = PWM_ABS_MAX;
	}
	else if (pwm < -PWM_ABS_MAX)
	{
		pwm = -PWM_ABS_MAX;
	}

	this->pwm = pwm;

	Motor_rotate(this->frontMotor, pwm);
}

int FrontWheel_getAngle(FrontWheel* this)
{
	return Motor_getAngle(this->frontMotor);
}
