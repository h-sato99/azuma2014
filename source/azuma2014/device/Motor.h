/*******************************************************************************
**  ファイル名  ：Motor.h
**  概要        ：モーター基底クラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/
#ifndef _Motor_H_
#define _Motor_H_

#include "ecrobot_interface.h"
#include "kernel.h"

// 属性を保持するための構造体の定義
typedef struct Motor
{
	MOTOR_PORT_T outputPort;
	int mode;
} Motor;

// 公開操作
void Motor_init(Motor* this, MOTOR_PORT_T outputPort);
void Motor_resetAngle(Motor* this);
long Motor_getAngle(Motor* this);
void Motor_rotate(Motor* this, int pwm);
void Motor_setMode(Motor* this, int mode);

#endif /* _Motor_H_ */

