/*******************************************************************************
**  ファイル名  ：WheelAverage.h
**  概要        ：両車輪の値を取得し、平均を返す。
**  詳細        ：両車輪の値を取得し、平均を返す。
*******************************************************************************/

#ifndef _WheelAverage_H_
#define _WheelAverage_H_

#include "technique/Wheel.h"

// 属性を保持するための構造体の定義
typedef struct WheelAverage
{
	Wheel *wheel;				//ホイールクラス
	int LeftWheel;				//左車輪の値
	int RightWheel;				//右車輪の値
	int Average;				//両車輪の取得用
}WheelAverage;

// 公開操作
void WheelAverage_init(WheelAverage* this);
int WheelAverage_action(WheelAverage* this);

#endif /* _WheelAverage_H_ */
