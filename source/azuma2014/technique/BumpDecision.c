/*******************************************************************************
**  ファイル名  ：BumpDecision.c
**  概要        ：衝突検知クラス
**  詳細        ：
*******************************************************************************/

#include "BumpDecision.h"

#define TARGET	500		//閾値

// 初期化する
void BumpDecision_init(BumpDecision* this)
{

}

//
BOOL BumpDecision_checkBump(BumpDecision* this)
{

	// ジャイロセンサの値を判定する
	if(GyroSensor_getAngularVelocity(this) > TARGET)
	{
		// ジャイロセンサが閾値を超えた場合、trueを返す
		return true;
	}

	// falseを返す
	return false;
}
