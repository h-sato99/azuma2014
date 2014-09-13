/*******************************************************************************
**  ファイル名  ：DrivingWheel.c
**  概要        ：左右モータ制御クラス
**  詳細        ：
*******************************************************************************/

#include "DrivingWheel.h"

#define CONST -1


void DrivingWheel_init(DrivingWheel* this)
{
	// 処理なし
}

/*------------------------------------------------------------------------------
--  関数名      ：DrivingWheel_setPwm
--  概要        ：左右モータの出力を設定する。
--              ：
--  引数        ：leftPwm   左モータの出力
--              ：rightPwm  右モータの出力
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void DrivingWheel_setPwm(DrivingWheel* this, int leftPwm, int rightPwm)
{
	Motor_rotate(this->leftMotor, leftPwm * CONST);
	Motor_rotate(this->rightMotor, rightPwm * CONST);
}

/*------------------------------------------------------------------------------
--  関数名      ：DrivingWheel_getLeftAngle
--  概要        ：左モータの回転角度を得る。
--              ：
--  引数        ：なし
--  戻り値      ：左モータ回転角度
------------------------------------------------------------------------------*/
int DrivingWheel_getLeftAngle(DrivingWheel* this)
{
	return Motor_getAngle(this->leftMotor);
}

/*------------------------------------------------------------------------------
--  関数名      ：DrivingWheel_getRightAngle
--  概要        ：右モータの回転角度を得る。
--              ：
--  引数        ：なし
--  戻り値      ：右モータ回転角度
------------------------------------------------------------------------------*/
int DrivingWheel_getRightAngle(DrivingWheel* this)
{
	return Motor_getAngle(this->rightMotor);
}
