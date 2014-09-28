/*******************************************************************************
**  �t�@�C����  �FMotor.h
**  �T�v        �F���[�^�[���N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/
#ifndef _Motor_H_
#define _Motor_H_

#include "ecrobot_interface.h"
#include "kernel.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct Motor
{
	MOTOR_PORT_T outputPort;
	int mode;
} Motor;

// ���J����
void Motor_init(Motor* this, MOTOR_PORT_T outputPort);
void Motor_resetAngle(Motor* this);
long Motor_getAngle(Motor* this);
void Motor_rotate(Motor* this, int pwm);
void Motor_setMode(Motor* this, int mode);

#endif /* _Motor_H_ */

