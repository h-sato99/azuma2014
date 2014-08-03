/*******************************************************************************
**  �t�@�C����  �FWheel.h
**  �T�v        �F���E���[�^����N���X��`
**  �ڍ�        �F
*******************************************************************************/

#ifndef _Wheel_H_
#define _Wheel_H_

#include "device/Motor.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct Wheel
{
	Motor *leftMotor;
	Motor *rightMotor;
} Wheel;

// ���J����
void Wheel_init(Wheel* this);
void Wheel_setPwm(Wheel* this, int leftPwm, int rightPwm);
int Wheel_getLeftAngle(Wheel* this);
int Wheel_getRightAngle(Wheel* this);

#endif /* _Wheel_H_ */
