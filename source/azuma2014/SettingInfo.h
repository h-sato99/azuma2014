/*******************************************************************************
**  �t�@�C����  �FSettingInfo.h
**  �T�v        �F�ݒ���N���X��`
**  �ڍ�        �F
*******************************************************************************/

#ifndef _SettingInfo_H_
#define _SettingInfo_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct SettingInfo
{
	// �R�[�X�^�C�v
	// 0:�A�E�g�R�[�X
	// 1:�C���R�[�X
	int courseType;
	F32 pidP;
	F32 pidI;
	F32 pidD;
	float target;
	float targetwait;
	float targetbas;
	BOOL lineTraceFlg;
} SettingInfo;

// ���J����
void SettingInfo_init(SettingInfo* this);

#endif /* _SettingInfo_H_ */
