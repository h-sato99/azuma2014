/*******************************************************************************
**  �t�@�C����  �FPidControl.h
**  �T�v        �FPID����N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _PidControl_H_
#define _PidControl_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "Info.h"



// ������ێ����邽�߂̍\���̂̒�`
typedef struct PidControl
{
	float deff1;
	float deff2;
	float integral;
	float f_p;
	float f_i;
	float f_d;
} PidControl;


void PidControl_init(PidControl* this);
F32 PidControl_calcTurn(PidControl* this, SettingInfo* settingInfo, int brightness);
BOOL PidControl_checDerailment(PidControl* this);

#endif /* _PidControl_H_ */

