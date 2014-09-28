/*******************************************************************************
**  ファイル名  ：Motor.c
**  概要        ：モーター基底クラス
**  詳細        ：モーターに関する処理を行う。
*******************************************************************************/

#include "device/Motor.h"

#define P_GAIN             2.5F // 完全停止用モータ制御比例係数
#define PWM_ABS_MAX          60 // 完全停止用モータ制御PWM絶対最大値

// 初期化する
void Motor_init(Motor* this, MOTOR_PORT_T outputPort)
{
	this->outputPort = outputPort;
	this->mode = 1;
}

// 回転角度をリセットする
void Motor_resetAngle(Motor* this)
{
	return nxt_motor_set_count(this->outputPort, 0);
}

// 回転角度を得る
long Motor_getAngle(Motor* this)
{
	return nxt_motor_get_count(this->outputPort);
}

// 回転させる
void Motor_rotate(Motor* this, int pwm)
{
	// 3番目の引数は0(フロートモード), 1(ブレーキモード)を表す。
	nxt_motor_set_speed(this->outputPort, pwm, this->mode);
}

void Motor_setMode(Motor* this, int mode)
{
	this->mode = mode;
}
