/*******************************************************************************
**  ファイル名  ：LightSensor.h
**  概要        ：光センサ操作クラス（ヘッダファイル）
**  詳細        ：光センサに対する操作を行う
*******************************************************************************/
#ifndef _LightSensor_H_
#define _LightSensor_H_

#include "ecrobot_interface.h"
#include "kernel.h"


// 属性を保持するための構造体の定義
typedef struct LightSensor
{
	SENSOR_PORT_T inputPort;
} LightSensor;

// 公開操作
void LightSensor_init(LightSensor* this, SENSOR_PORT_T inputPort);
unsigned int LightSensor_getBrightness(LightSensor* this);

#endif /* _LightSensor_H_ */

