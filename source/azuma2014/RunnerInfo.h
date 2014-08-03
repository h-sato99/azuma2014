/*******************************************************************************
**  �t�@�C����  �FRunnerInfo.h
**  �T�v        �F���s���N���X��`
**  �ڍ�        �F
*******************************************************************************/

#ifndef _RunnerInfo_H_
#define _RunnerInfo_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct RunnerInfo
{
	F32 forward;
	F32 turn;
	BOOL balanceFlag;
	UINT gyroOffset;
	int tail;
	BOOL chengeLineEdgeFlag;
	BOOL dashFlag;
	int dashvol;
	int dashlim;
	BOOL emergencyStopCheckFlag;
	BOOL emergencyStopFlag;
} RunnerInfo;

// ���J����
// �Ȃ�

#endif /* _RunnerInfo_H_ */
