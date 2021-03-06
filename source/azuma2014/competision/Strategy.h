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
#include "technique/Distance.h"

#include "technique/LineChange.h"
#include "technique/LineComeBack.h"
#include "technique/BumpDecision.h"
#include "technique/TrialDecision.h"
#include "competision/Jump.h"
#include "competision/Mogul.h"
#include "competision/Course.h"
#include "competision/PendingArea.h"
#include "competision/FigureL.h"

#include "competision/OrderTest.h"


// 属性を保持するための構造体の定義
typedef struct Strategy
{
	BasicStage *basicStage;
	Distance *distance;
	BOOL initBasicStageFlag;
	BOOL startGrayDecision;

	Course *course;
	LineChange *lineChange;
	LineComeback *lineComeback;
	BumpDecision *bumpDecision;
	TrialDecision *trialDecision;
	Jump *jump;
	Mogul *mogul;
	PendingArea *pendingArea;
	FigureL *figureL;

	OrderTest *orderTest;
} Strategy;

// 公開操作
void Strategy_init(Strategy* this);
void Strategy_action(Strategy* this, Info* info);

#endif /* _Strategy_H_ */
