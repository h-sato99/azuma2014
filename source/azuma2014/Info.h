/*******************************************************************************
**  �t�@�C����  �FInfo.h
**  �T�v        �F���N���X��`
**  �ڍ�        �F
*******************************************************************************/

#ifndef _Info_H_
#define _Info_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "CourseInfo.h"
#include "SettingInfo.h"
#include "RunnerInfo.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct Info
{
	MeasureInfo *measureInfo;
	RunnerInfo *runnerInfo;
	SettingInfo *settingInfo;
	BOOL loggerFlag;
	BOOL autoStrategyFlag;
	S8 strategyState;
	BOOL startFlag;
} Info;

// ���J����
// �Ȃ�

#endif /* _Info_H_ */
