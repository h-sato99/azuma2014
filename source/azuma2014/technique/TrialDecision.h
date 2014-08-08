/*******************************************************************************
**  ファイル名  ：TrialDecision.h
**  概要        ：難所検知クラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef TRIALDECISION_H_
#define TRIALDECISION_H_

#include "OrderList.h"
#include "technique/BumpDecision.h"

// 属性を保持するための構造体の定義
typedef struct TrialDecision
{
	OrderList *orderList;
	BumpDecision *bumpDecision;
	int mode;
	int orderNum;
} TrialDecision;

// 公開操作
void TrialDecision_init(TrialDecision* this);
BOOL TrialDecision_action(TrialDecision* this);

#endif /* TRIALDICISION_H_ */
