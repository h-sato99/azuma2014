/*******************************************************************************
**  �t�@�C����  �FRunner.h
**  �T�v        �F���s�N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
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

// ���s���
typedef enum RunningState
{
	MUNUAL,
	LINETRACE
} RunningState;

// ������
typedef enum TurnState
{
	TURN_INIT,
	TURN_FRONT,
	TURN_DRIVING,
	TURN_LEFT,
	TURN_RIGHT
} TurnState;

// ������ێ����邽�߂̍\���̂̒�`
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

// ���J����
void Runner_init(Runner* this);
void Runner_run(Runner* this, float target, F32 forward, F32 turn, int runningState, int turnState);
int Runner_getDistance(Runner* this);

#endif /* _Runner_H_ */
