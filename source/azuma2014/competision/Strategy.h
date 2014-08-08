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
//#include "Seesaw.h"
//#include "LookUpGate.h"
//#include "GarageIn.h"
#include "technique/Distance.h"
#include "technique/GrayDecision.h"

#include "technique/LineChange.h"
#include "technique/BumpDecision.h"
#include "technique/TrialDecision.h"
#include "Jump.h"


// ������ێ����邽�߂̍\���̂̒�`
typedef struct Strategy
{
	BasicStage *basicStage;
//	Seesaw *seesaw;
//	LookUpGate *lookUpGate;
//	GarageIn *garageIn;
	Distance *distance;
	BOOL initBasicStageFlag;
	GrayDecision *grayDecision;
	BOOL startGrayDecision;

	LineChange *lineChange;
	BumpDecision *bumpDecision;
	TrialDecision *trialDecision;
	Jump *jump;
} Strategy;

// ���J����
void Strategy_init(Strategy* this);
void Strategy_action(Strategy* this, Info* info);

#endif /* _Strategy_H_ */
