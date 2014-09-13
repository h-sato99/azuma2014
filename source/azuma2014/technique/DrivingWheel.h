/*******************************************************************************
**  ファイル名  ：DrivingWheel.h
**  概要        ：左右モータ制御クラス定義
**  詳細        ：
*******************************************************************************/

#ifndef _DrivingWheel_H_
#define _DrivingWheel_H_

#include "device/Motor.h"

// 属性を保持するための構造体の定義
typedef struct DrivingWheel
{
	Motor *leftMotor;
	Motor *rightMotor;
} DrivingWheel;

// 公開操作
void DrivingWheel_init(DrivingWheel* this);
void DrivingWheel_setPwm(DrivingWheel* this, int leftPwm, int rightPwm);
int DrivingWheel_getLeftAngle(DrivingWheel* this);
int DrivingWheel_getRightAngle(DrivingWheel* this);

#endif /* _DrivingWheel_H_ */
