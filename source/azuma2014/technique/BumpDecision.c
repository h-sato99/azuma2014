/*******************************************************************************
**  ファイル名  ：BumpDecision.c
**  概要        ：衝突検知クラス
**  詳細        ：
*******************************************************************************/

#include "BumpDecision.h"

#define TARGET_LOW		300		//閾値
#define TARGET_HIGH		800		//閾値

// 初期化する
void BumpDecision_init(BumpDecision* this)
{
	this->gyroValue = 600;
}

//
BOOL BumpDecision_checkBump(BumpDecision* this)
{

	this->gyroValue = GyroSensor_getAngularVelocity(this->gyroSensor);
	// ジャイロセンサの値を判定する
	if(this->gyroValue < TARGET_LOW || this->gyroValue > TARGET_HIGH )
	{
		// ジャイロセンサが閾値を超えた場合、trueを返す
		return true;
	}

	// falseを返す
	return false;
}
