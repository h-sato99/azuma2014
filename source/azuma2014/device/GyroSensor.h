/*******************************************************************************
**  ファイル名  ：GyroSensor.h
**  概要        ：ジャイロセンサクラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _GyroSensor_H_
#define _GyroSensor_H_


#include "ecrobot_interface.h"
#include "kernel.h"


// 属性を保持するための構造体の定義
typedef struct GyroSensor
{
	unsigned int offset;
	SENSOR_PORT_T inputPort;
} GyroSensor;

// 公開操作
void GyroSensor_init(GyroSensor* this, SENSOR_PORT_T inputPort);
unsigned int GyroSensor_getAngularVelocity(GyroSensor* this);
unsigned int GyroSensor_getOffset(GyroSensor* this);

#endif /* _GyroSensor_H_ */

