/*******************************************************************************
**  �t�@�C����  �FDrivingWheel.h
**  �T�v        �F���E���[�^����N���X��`
**  �ڍ�        �F
*******************************************************************************/

#ifndef _DrivingWheel_H_
#define _DrivingWheel_H_

#include "device/Motor.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct DrivingWheel
{
	Motor *leftMotor;
	Motor *rightMotor;
} DrivingWheel;

// ���J����
void DrivingWheel_init(DrivingWheel* this);
void DrivingWheel_setPwm(DrivingWheel* this, int leftPwm, int rightPwm);
int DrivingWheel_getLeftAngle(DrivingWheel* this);
int DrivingWheel_getRightAngle(DrivingWheel* this);

#endif /* _DrivingWheel_H_ */
