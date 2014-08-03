/*******************************************************************************
**  �t�@�C����  �FCalibration.h
**  �T�v        �F�L�����u���[�V�����N���X�i�w�b�_�t�@�C���j
**  �ڍ�        �F�L�����u���[�V�����Ɋւ��鏈�����`�B
*******************************************************************************/

#ifndef _Calibration_H_
#define _Calibration_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "device/LCD.h"
#include "device/TouchSensor.h"
#include "device/LightSensor.h"

// �F�擾�p�\���̒�`
typedef struct Calibration 
{
	int black; //���F
	int white; //���F
	int gray;  //�D�F
	LCD *lcd;
	TouchSensor *touchSensor;
	LightSensor *lightSensor;
} Calibration;

// ���J����
void Calibration_MeasureLight(Calibration* this);

#endif /* _Calibration_H_ */
