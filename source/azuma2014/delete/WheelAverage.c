/*******************************************************************************
**  ファイル名  ：Class.c
**  概要        ：両車輪の値を取得し、平均を返す。
**  詳細        ：両車輪の値を取得し、平均を返す。
*******************************************************************************/

#include "technique/WheelAverage.h"
#define ConstNumberZero 0;

void WheelAverage_init(WheelAverage* this)
{
	this->LeftWheel = ConstNumberZero;
	this->RightWheel = ConstNumberZero;
	this->Average = ConstNumberZero;
}
int WheelAverage_action(WheelAverage* this)
{
	//ホイールの値取得、平均値の計算
	this->LeftWheel = Wheel_getLeftAngle(this->wheel);
	this->RightWheel = Wheel_getRightAngle(this->wheel);
	this->Average = (this->LeftWheel + this->RightWheel)/2;
	return this->Average;
}
