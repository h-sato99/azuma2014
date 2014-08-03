/*******************************************************************************
**  ファイル名  ：SonarSensor.h
**  概要        ：超音波センサクラス（ヘッダファイル）
**  詳細        ：超音波センサに関する処理を定義。
*******************************************************************************/

#ifndef _SonarSensor_H_
#define _SonarSensor_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// 属性を保持するための構造体の定義
typedef struct SonarSensor
{
	SENSOR_PORT_T inputPort;
} SonarSensor;

// 公開操作
void SonarSensor_init(SonarSensor* this, SENSOR_PORT_T inputPort);
S32 SonarSensor_get(SonarSensor* this);
void SonarSensor_term(SonarSensor* this);

#endif /* _SonarSensor_H_ */
