/*******************************************************************************
**  ファイル名  ：Calibration.h
**  概要        ：キャリブレーションクラス（ヘッダファイル）
**  詳細        ：キャリブレーションに関する処理を定義。
*******************************************************************************/

#ifndef _Calibration_H_
#define _Calibration_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "device/LCD.h"
#include "device/TouchSensor.h"
#include "device/LightSensor.h"

// 色取得用構造体定義
typedef struct Calibration 
{
	int black; //黒色
	int white; //白色
	int gray;  //灰色
	LCD *lcd;
	TouchSensor *touchSensor;
	LightSensor *lightSensor;
} Calibration;

// 公開操作
void Calibration_MeasureLight(Calibration* this);

#endif /* _Calibration_H_ */
