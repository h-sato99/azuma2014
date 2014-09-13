/*******************************************************************************
**  �t�@�C����  �FStrategy.h
**  �T�v        �F�헪�N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _Strategy_H_
#define _Strategy_H_

#include "Info.h"
#include "SettingInfo.h"
#include "BasicStage.h"
#include "technique/Distance.h"

#include "technique/LineChange.h"
#include "technique/BumpDecision.h"
#include "technique/TrialDecision.h"
#include "competision/Jump.h"
#include "competision/Mogul.h"


// ������ێ����邽�߂̍\���̂̒�`
typedef struct Strategy
{
	BasicStage *basicStage;
	Distance *distance;
	BOOL initBasicStageFlag;
	BOOL startGrayDecision;

	LineChange *lineChange;
	BumpDecision *bumpDecision;
	TrialDecision *trialDecision;
	Jump *jump;
	Mogul *mogul;
} Strategy;

// ���J����
void Strategy_init(Strategy* this);
void Strategy_action(Strategy* this, Info* info);

#endif /* _Strategy_H_ */
