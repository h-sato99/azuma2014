/*******************************************************************************
**  ファイル名  ：Runner.c
**  概要        ：走行クラス
**  詳細        ：
*******************************************************************************/

#include "Runner.h"

static void Runner_setLineEge(Runner* this, RunnerInfo* runnerInfo);
static void Runner_setMeasureInfo(Runner* this, MeasureInfo* measureInfo);

void Runner_init(Runner* this)
{
	// 処理なし
}

/*------------------------------------------------------------------------------
--  関数名      ：Runner_run
--  概要        ：モータに走行指示を与える
--              ：  ○turn(旋回値)の動きは下記の通り
--              ：    旋回値＞０の場合：右向きに旋回する
--              ：    旋回値＝０の場合：旋回しない
--              ：    旋回値＜０の場合：左向きに旋回する
--              ：
--  引数        ：runnerInfo  走行情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Runner_run(Runner* this, Info* info)
{
	int leftMotor;
	int rightMotor;
	int tail;

	Runner_setMeasureInfo(this, info->measureInfo);
	Runner_setLineEge(this, info->runnerInfo);

	if(info->runnerInfo->dashFlag == TRUE)
	{
		Dash_action(this->dash, info ,info->runnerInfo->dashvol ,info->runnerInfo->dashlim );
	}
	else
	{
		Dash_init(this->dash);
	}

	if(info->runnerInfo->emergencyStopCheckFlag == TRUE)
	{
		info->runnerInfo->emergencyStopFlag = BalanceControl_checkEmergencyStop(this->balanceControl);
	}

	if(info->runnerInfo->emergencyStopFlag == FALSE)
	{
		// 通常の走行
		BalanceControl_run(this->balanceControl, info->runnerInfo, info->measureInfo);
		leftMotor = BalanceControl_getLeftMotorPwm(this->balanceControl);
		rightMotor = BalanceControl_getRightMotorPwm(this->balanceControl);
		tail = info->runnerInfo->tail;
	}
	else
	{
		// 緊急停止
		leftMotor = 0;
		rightMotor = 0;
		tail = 0;
	}

	Wheel_setPwm(this->wheel, leftMotor, rightMotor);

	Tail_setAngle(this->tail, tail);
}

static void Runner_setMeasureInfo(Runner* this, MeasureInfo* measureInfo)
{
	measureInfo->leftMotorAngle = Wheel_getLeftAngle(this->wheel);
	measureInfo->rightMotorAngle = Wheel_getRightAngle(this->wheel);
	measureInfo->tailAngle = Tail_getAngle(this->tail);
}

/*------------------------------------------------------------------------------
--  関数名      ：Runner_calcMotor
--  概要        ：トレースするラインエッジを設定する
--              ：通常は右エッジ（ラインの右側）をラインレースする
--              ：
--  引数        ：runnerInfo  走行情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
static void Runner_setLineEge(Runner* this, RunnerInfo* runnerInfo)
{
	if(runnerInfo->chengeLineEdgeFlag == TRUE)
	{
		runnerInfo->turn *= -1;
	}
}

