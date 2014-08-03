/*******************************************************************************
**  �t�@�C����  �FTouchSensor.h
**  �T�v        �F�^�b�`�Z���T�N���X�i�w�b�_�t�@�C���j
**  �ڍ�        �F�^�b�`�Z���T�Ɋւ��鏈�����s���B
*******************************************************************************/
#ifndef _TouchSensor_H_
#define _TouchSensor_H_


#include "ecrobot_interface.h"
#include "kernel.h"


// ������ێ����邽�߂̍\���̂̒�`
typedef struct TouchSensor
{
	SENSOR_PORT_T inputPort;
} TouchSensor;

// ���J����
void TouchSensor_init(TouchSensor* this, SENSOR_PORT_T inputPort);
BOOL TouchSensor_isPressed(TouchSensor* this);

#endif /* _TouchSensor_H_ */


