/*******************************************************************************
**  �t�@�C����  �FFrontWheel.c
**  �T�v        �F�K�����[�^����N���X
**  �ڍ�        �F
*******************************************************************************/

#include "FrontWheel.h"

#define P_GAIN             10.0F // ���S��~�p���[�^������W��
//#define PWM_ABS_MAX          900 // ���S��~�p���[�^����PWM��΍ő�l
#define PWM_ABS_MAX          100 // ���S��~�p���[�^����PWM��΍ő�l
#define C_ANGLE              3.5
#define C_PWM                3.5
//#define C_PWM                10

void FrontWheel_init(FrontWheel* this)
{
	// �����Ȃ�
}

/*------------------------------------------------------------------------------
--  �֐���      �FFrontWheel_setAngle
--  �T�v        �F�K�����[�^�̊p�x��ݒ肷��B
--              �F
--  ����        �Fangle   �K�����[�^�̊p�x
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void FrontWheel_setAngle(FrontWheel* this, int angle)
{
	int pwm;

	pwm = angle;

	// ��ᐧ��
//	pwm = (angle * 10 - Motor_getAngle(this->frontMotor)) * P_GAIN;
//	pwm = (angle * 3 - Motor_getAngle(this->frontMotor)) / 3;
//	pwm = (angle * 3 - Motor_getAngle(this->frontMotor)) / 2;
//	pwm = (angle * 3 - Motor_getAngle(this->frontMotor));
//	pwm = (angle * 3 - Motor_getAngle(this->frontMotor)) * 3;
//	pwm = (angle * 3.3 - Motor_getAngle(this->frontMotor)) * 3;
	pwm = (angle * C_ANGLE - Motor_getAngle(this->frontMotor)) * C_PWM;

	/*
	display_goto_xy(2, 1);
	display_int(angle, 14);
	display_goto_xy(2, 2);
	display_int(pwm, 14);
	display_update();
	*/

	// PWM�o�͖O�a����
	if (pwm > PWM_ABS_MAX)
	{
		pwm = PWM_ABS_MAX;
	}
	else if (pwm < -PWM_ABS_MAX)
	{
		pwm = -PWM_ABS_MAX;
	}

	this->pwm = pwm;

	Motor_rotate(this->frontMotor, pwm);
}

int FrontWheel_getAngle(FrontWheel* this)
{
	return Motor_getAngle(this->frontMotor);
}
