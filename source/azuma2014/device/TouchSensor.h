/*******************************************************************************
**  ファイル名  ：TouchSensor.h
**  概要        ：タッチセンサクラス（ヘッダファイル）
**  詳細        ：タッチセンサに関する処理を行う。
*******************************************************************************/
#ifndef _TouchSensor_H_
#define _TouchSensor_H_


#include "ecrobot_interface.h"
#include "kernel.h"


// 属性を保持するための構造体の定義
typedef struct TouchSensor
{
	SENSOR_PORT_T inputPort;
} TouchSensor;

// 公開操作
void TouchSensor_init(TouchSensor* this, SENSOR_PORT_T inputPort);
BOOL TouchSensor_isPressed(TouchSensor* this);

#endif /* _TouchSensor_H_ */


