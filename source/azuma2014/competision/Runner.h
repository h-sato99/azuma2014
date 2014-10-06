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
#include "technique/DrivingWheel.h"
#include "technique/FrontWheel.h"
#include "LineTracer.h"

// 走行状態
typedef enum RunningState
{
	MUNUAL,
	LINETRACE
} RunningState;

// 旋回状態
typedef enum TurnState
{
	TURN_INIT,
	TURN_FRONT,
	TURN_DRIVING,
	TURN_LEFT,
	TURN_RIGHT
} TurnState;

// 属性を保持するための構造体の定義
typedef struct Runner
{
	int runningState;
	int turnState;
	F32 forward;
	F32 turn;
	DrivingWheel *drivingWheel;
	FrontWheel *frontWheel;
	LineTracer *lineTracer;
} Runner;

// 公開操作
void Runner_init(Runner* this);
void Runner_run(Runner* this, float target, F32 forward, F32 turn, int runningState, int turnState);
int Runner_getDistance(Runner* this);

#endif /* _Runner_H_ */
