/*******************************************************************************
**  ファイル名  ：BalanceControl.h
**  概要        ：倒立制御クラス定義
**  詳細        ：
*******************************************************************************/

#ifndef _BalanceControl_H_
#define _BalanceControl_H_


#include "balancer.h" // 倒立振子制御用ヘッダファイル

#include "RunnerInfo.h"
#include "CourseInfo.h"
#include "device/GyroSensor.h"
#include "technique/Wheel.h"
#include "technique/Distance.h"


// 属性を保持するための構造体の定義
typedef struct BalanceControl
{
	BOOL isInitialized;
	GyroSensor *gyroSensor;
	Wheel *wheel;
	int leftMotorPwm;
	int rightMotorPwm;
	int balanceMode;
	BOOL lastBalanceFlag;
	BOOL chengeBalanceFlag;
	int chengeMode;
	int motorDistance;
	Distance *distance;
	BOOL emergencyStopFlag;
} BalanceControl;

// 公開操作
void BalanceControl_init(BalanceControl* this);
void BalanceControl_BalanceRun(BalanceControl* this, RunnerInfo* runnerInfo);
int BalanceControl_getLeftMotorPwm(BalanceControl* this);
int BalanceControl_getRightMotorPwm(BalanceControl* this);
void BalanceControl_run(BalanceControl* this, RunnerInfo* runnerInfo, MeasureInfo* measuerInfo);
void BalanceControl_chengeBalance(BalanceControl* this);
BOOL BalanceControl_checkEmergencyStop(BalanceControl* this);

#endif /* _BalanceControl_H_ */

