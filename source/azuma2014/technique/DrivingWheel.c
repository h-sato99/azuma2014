/*******************************************************************************
**  �t�@�C����  �FDrivingWheel.c
**  �T�v        �F���E���[�^����N���X
**  �ڍ�        �F
*******************************************************************************/

#include "DrivingWheel.h"

#define CONST -1


void DrivingWheel_init(DrivingWheel* this)
{
	// �����Ȃ�
}

/*------------------------------------------------------------------------------
--  �֐���      �FDrivingWheel_setPwm
--  �T�v        �F���E���[�^�̏o�͂�ݒ肷��B
--              �F
--  ����        �FleftPwm   �����[�^�̏o��
--              �FrightPwm  �E���[�^�̏o��
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void DrivingWheel_setPwm(DrivingWheel* this, int leftPwm, int rightPwm)
{
	Motor_rotate(this->leftMotor, leftPwm * CONST);
	Motor_rotate(this->rightMotor, rightPwm * CONST);
}

/*------------------------------------------------------------------------------
--  �֐���      �FDrivingWheel_getLeftAngle
--  �T�v        �F�����[�^�̉�]�p�x�𓾂�B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�����[�^��]�p�x
------------------------------------------------------------------------------*/
int DrivingWheel_getLeftAngle(DrivingWheel* this)
{
	return Motor_getAngle(this->leftMotor);
}

/*------------------------------------------------------------------------------
--  �֐���      �FDrivingWheel_getRightAngle
--  �T�v        �F�E���[�^�̉�]�p�x�𓾂�B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�E���[�^��]�p�x
------------------------------------------------------------------------------*/
int DrivingWheel_getRightAngle(DrivingWheel* this)
{
	return Motor_getAngle(this->rightMotor);
}
