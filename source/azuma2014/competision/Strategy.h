/*******************************************************************************
**  ファイル名  ：Strategy.h
**  概要        ：戦略クラス定義
**  詳細        ：クラスの公開情報を定義する。
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


// 属性を保持するための構造体の定義
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

// 公開操作
void Strategy_init(Strategy* this);
void Strategy_action(Strategy* this, Info* info);

#endif /* _Strategy_H_ */
