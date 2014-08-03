/*******************************************************************************
**  �t�@�C����  �FPidControl.c
**  �T�v        �FPID����N���X
**  �ڍ�        �FPID�����p���Đ���ʂ��v�Z������B
*******************************************************************************/

#include "PidControl.h"

#define C_DELTA_T 0.004
#define C_LIMIT 100.0
#define C_MATH -100.0

#define C_CHEK_DERAILMENT -40

/*------------------------------------------------------------------------------
--  �֐���      �FPidControl_Init
--  �T�v        �FPID����̌v�Z�Ɏg�p����ϐ�������������B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void PidControl_init(PidControl* this)
{
	this->deff1 = 0.0;
	this->deff2 = 0.0;
	this->integral = 0.0;
}

F32 PidControl_MathLimit(float pid)
{
	float ret = pid;

	if (ret > C_LIMIT)
	{
		ret = C_LIMIT;

	}
	else if (ret < C_MATH)
	{
		ret = C_MATH;
	}

	return ret;
}

/*------------------------------------------------------------------------------
--  �֐���      �FPidControl_CalTurn
--  �T�v        �F����ʂ��v�Z������B
--              �F
--  ����        �FsettingInfo  �ݒ���iP�EI�ED�̒萔�A�ڕW�l�𗘗p�j
--              �Fbrightness   ���Z���T�[�Ŋϑ������l
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
F32 PidControl_calcTurn(PidControl* this, SettingInfo* settingInfo, int brightness)
{
	float f_p;
	float f_i;
	float f_d;
	float f_turn;

	this->deff1 = this->deff2;
	this->deff2 = (float)(brightness - settingInfo->target);

	// �ϕ��̋ߎ�
	this->integral += (this->deff2 + this->deff1) / 2.0 * C_DELTA_T;

	// �o����
	f_p = settingInfo->pidP * this->deff2;
	// �h����
	f_i = settingInfo->pidI * this->integral;
	// �c����
	f_d = settingInfo->pidD * (this->deff2 - this->deff1) / C_DELTA_T;

	// ����ʂ̌v�Z
	f_turn = f_p + f_i + f_d;
	return PidControl_MathLimit(f_turn);
}

/*------------------------------------------------------------------------------
--  �֐���      �FPidControl_checDerailment
--  �T�v        �F�E���������ǂ����𔻒肷��B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
BOOL PidControl_checDerailment(PidControl* this)
{
	if(this->deff2 < -30)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
