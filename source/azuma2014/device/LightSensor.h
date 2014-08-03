/*******************************************************************************
**  �t�@�C����  �FLightSensor.h
**  �T�v        �F���Z���T����N���X�i�w�b�_�t�@�C���j
**  �ڍ�        �F���Z���T�ɑ΂��鑀����s��
*******************************************************************************/
#ifndef _LightSensor_H_
#define _LightSensor_H_

#include "ecrobot_interface.h"
#include "kernel.h"


// ������ێ����邽�߂̍\���̂̒�`
typedef struct LightSensor
{
	SENSOR_PORT_T inputPort;
} LightSensor;

// ���J����
void LightSensor_init(LightSensor* this, SENSOR_PORT_T inputPort);
unsigned int LightSensor_getBrightness(LightSensor* this);

#endif /* _LightSensor_H_ */

