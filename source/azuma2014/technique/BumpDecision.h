/*******************************************************************************
**  ファイル名  ：BumpDecision.h
**  概要        ：衝突検知クラス定義
**  詳細        ：
*******************************************************************************/

#ifndef BUMPDECISION_H_
#define BUMPDECISION_H_

#include "device/GyroSensor.h"

// 属性を保持するための構造体の定義
typedef struct BumpDecision
{
	GyroSensor *gyroSensor;
} BumpDecision;

void BumpDecision_init(BumpDecision* this);
BOOL BumpDecision_checkBump(BumpDecision* this);

#endif /* BUMPDECISION_H_ */
