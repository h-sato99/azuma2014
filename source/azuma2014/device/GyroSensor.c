/*******************************************************************************
**  �t�@�C����  �FGyroSensor.c
**  �T�v        �F�W���C���Z���T�N���X
**  �ڍ�        �F
*******************************************************************************/

#include "device/GyroSensor.h"
#define GYRO_OFFSET  607



// ����������
void GyroSensor_init(GyroSensor* this, SENSOR_PORT_T inputPort)
{
	this->inputPort = inputPort;
	this->offset = GYRO_OFFSET;
}

unsigned int GyroSensor_getAngularVelocity(GyroSensor* this)
{
	return ecrobot_get_gyro_sensor(this->inputPort);
}

unsigned int GyroSensor_getOffset(GyroSensor* this)
{
	return this->offset;
}




