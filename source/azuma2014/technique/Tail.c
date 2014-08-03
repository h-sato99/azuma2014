/*******************************************************************************
**  �t�@�C����  �FTail.c
**  �T�v        �F�K�����[�^����N���X
**  �ڍ�        �F
*******************************************************************************/

#include "Tail.h"

#define P_GAIN             2.5F // ���S��~�p���[�^������W��
#define PWM_ABS_MAX          60 // ���S��~�p���[�^����PWM��΍ő�l


void Tail_init(Tail* this)
{
	// �����Ȃ�
}

/*------------------------------------------------------------------------------
--  �֐���      �FTail_setAngle
--  �T�v        �F�K�����[�^�̊p�x��ݒ肷��B
--              �F
--  ����        �Fangle   �K�����[�^�̊p�x
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Tail_setAngle(Tail* this, int angle)
{
	int pwm;

	// ��ᐧ��
	pwm = (angle - Motor_getAngle(this->tailMotor)) * P_GAIN;

	// PWM�o�͖O�a����
	if (pwm > PWM_ABS_MAX)
	{
		pwm = PWM_ABS_MAX;
	}
	else if (pwm < -PWM_ABS_MAX)
	{
		pwm = -PWM_ABS_MAX;
	}

	Motor_rotate(this->tailMotor, pwm);
}

int Tail_getAngle(Tail* this)
{
	return Motor_getAngle(this->tailMotor);
}
