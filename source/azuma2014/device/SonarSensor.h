/*******************************************************************************
**  �t�@�C����  �FSonarSensor.h
**  �T�v        �F�����g�Z���T�N���X�i�w�b�_�t�@�C���j
**  �ڍ�        �F�����g�Z���T�Ɋւ��鏈�����`�B
*******************************************************************************/

#ifndef _SonarSensor_H_
#define _SonarSensor_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct SonarSensor
{
	SENSOR_PORT_T inputPort;
} SonarSensor;

// ���J����
void SonarSensor_init(SonarSensor* this, SENSOR_PORT_T inputPort);
S32 SonarSensor_get(SonarSensor* this);
void SonarSensor_term(SonarSensor* this);

#endif /* _SonarSensor_H_ */
