/*******************************************************************************
**  ファイル名  ：Wheel.h
**  概要        ：左右モータ制御クラス定義
**  詳細        ：
*******************************************************************************/

#ifndef _Wheel_H_
#define _Wheel_H_

#include "device/Motor.h"

// 属性を保持するための構造体の定義
typedef struct Wheel
{
	Motor *leftMotor;
	Motor *rightMotor;
} Wheel;

// 公開操作
void Wheel_init(Wheel* this);
void Wheel_setPwm(Wheel* this, int leftPwm, int rightPwm);
int Wheel_getLeftAngle(Wheel* this);
int Wheel_getRightAngle(Wheel* this);

#endif /* _Wheel_H_ */
