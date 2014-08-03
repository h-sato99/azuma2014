/*******************************************************************************
**  ファイル名  ：Wheel.c
**  概要        ：左右モータ制御クラス
**  詳細        ：
*******************************************************************************/

#include "Wheel.h"



void Wheel_init(Wheel* this)
{
	// 処理なし
}

/*------------------------------------------------------------------------------
--  関数名      ：Wheel_setPwm
--  概要        ：左右モータの出力を設定する。
--              ：
--  引数        ：leftPwm   左モータの出力
--              ：rightPwm  右モータの出力
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Wheel_setPwm(Wheel* this, int leftPwm, int rightPwm)
{
	Motor_rotate(this->leftMotor, leftPwm);
	Motor_rotate(this->rightMotor, rightPwm);
}

/*------------------------------------------------------------------------------
--  関数名      ：Wheel_getLeftAngle
--  概要        ：左モータの回転角度を得る。
--              ：
--  引数        ：なし
--  戻り値      ：左モータ回転角度
------------------------------------------------------------------------------*/
int Wheel_getLeftAngle(Wheel* this)
{
	return Motor_getAngle(this->leftMotor);
}

/*------------------------------------------------------------------------------
--  関数名      ：Wheel_getRightAngle
--  概要        ：右モータの回転角度を得る。
--              ：
--  引数        ：なし
--  戻り値      ：右モータ回転角度
------------------------------------------------------------------------------*/
int Wheel_getRightAngle(Wheel* this)
{
	return Motor_getAngle(this->rightMotor);
}
