/*******************************************************************************
**  ファイル名  ：TrialDicision.h
**  概要        ：難所検知クラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef TRIALDICISION_H_
#define TRIALDICISION_H_

#include "OrderList.h"
#include "technique/BumpDecision.h"

// 属性を保持するための構造体の定義
typedef struct TrialDicision
{
	OrderList *orderList;
	BumpDecision *bumpDecision;
	int mode;
	int orderNum;
} TrialDicision;

// 公開操作
void TrialDicision_init(TrialDicision* this);
BOOL TrialDicision_action(TrialDicision* this);

#endif /* TRIALDICISION_H_ */
