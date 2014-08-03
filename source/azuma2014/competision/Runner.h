/*******************************************************************************
**  ファイル名  ：Runner.h
**  概要        ：走行クラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _Runner_H_
#define _Runner_H_

#include "Info.h"
#include "RunnerInfo.h"
#include "CourseInfo.h"
#include "technique/Tail.h"
#include "technique/Wheel.h"
#include "technique/BalanceControl.h"
#include "technique/Dash.h"

// 属性を保持するための構造体の定義
typedef struct Runner
{
	Tail *tail;
	Wheel *wheel;
	BalanceControl *balanceControl;
	Dash *dash;
} Runner;

// 公開操作
void Runner_init(Runner* this);
void Runner_run(Runner* this, Info* info);

#endif /* _Runner_H_ */
