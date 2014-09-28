/*******************************************************************************
**  �t�@�C����  �FMotor.c
**  �T�v        �F���[�^�[���N���X
**  �ڍ�        �F���[�^�[�Ɋւ��鏈�����s���B
*******************************************************************************/

#include "device/Motor.h"

#define P_GAIN             2.5F // ���S��~�p���[�^������W��
#define PWM_ABS_MAX          60 // ���S��~�p���[�^����PWM��΍ő�l

// ����������
void Motor_init(Motor* this, MOTOR_PORT_T outputPort)
{
	this->outputPort = outputPort;
	this->mode = 1;
}

// ��]�p�x�����Z�b�g����
void Motor_resetAngle(Motor* this)
{
	return nxt_motor_set_count(this->outputPort, 0);
}

// ��]�p�x�𓾂�
long Motor_getAngle(Motor* this)
{
	return nxt_motor_get_count(this->outputPort);
}

// ��]������
void Motor_rotate(Motor* this, int pwm)
{
	// 3�Ԗڂ̈�����0(�t���[�g���[�h), 1(�u���[�L���[�h)��\���B
	nxt_motor_set_speed(this->outputPort, pwm, this->mode);
}

void Motor_setMode(Motor* this, int mode)
{
	this->mode = mode;
}
