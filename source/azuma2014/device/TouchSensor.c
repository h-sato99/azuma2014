/*******************************************************************************
**  �t�@�C����  �FTouchSensor.c
**  �T�v        �F�^�b�`�Z���T�N���X
**  �ڍ�        �F�^�b�`�Z���T�Ɋւ��鏈�����s���B
*******************************************************************************/

#include "device/TouchSensor.h"


// ����������
void TouchSensor_init(TouchSensor* this, SENSOR_PORT_T inputPort)
{
	this->inputPort = inputPort;
}

// ������Ԃ𓾂�
BOOL TouchSensor_isPressed(TouchSensor* this)
{
	return ecrobot_get_touch_sensor(this->inputPort);
}

