/*******************************************************************************
**  ファイル名  ：LightSensor.c
**  概要        ：光センサ操作クラス
**  詳細        ：光センサに対する操作を行う
*******************************************************************************/

#include "device/LightSensor.h"


void LightSensor_init(LightSensor* this, SENSOR_PORT_T inputPort)
{
	this->inputPort = inputPort;

}

// 輝度を得る
unsigned int LightSensor_getBrightness(LightSensor* this)
{
	return ecrobot_get_light_sensor(this->inputPort);
}


