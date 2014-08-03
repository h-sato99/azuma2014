/*******************************************************************************
**  �t�@�C����  �FBalanceControl.h
**  �T�v        �F�|������N���X��`
**  �ڍ�        �F
*******************************************************************************/

#ifndef _BalanceControl_H_
#define _BalanceControl_H_


#include "balancer.h" // �|���U�q����p�w�b�_�t�@�C��

#include "RunnerInfo.h"
#include "CourseInfo.h"
#include "device/GyroSensor.h"
#include "technique/Wheel.h"
#include "technique/Distance.h"


// ������ێ����邽�߂̍\���̂̒�`
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

// ���J����
void BalanceControl_init(BalanceControl* this);
void BalanceControl_BalanceRun(BalanceControl* this, RunnerInfo* runnerInfo);
int BalanceControl_getLeftMotorPwm(BalanceControl* this);
int BalanceControl_getRightMotorPwm(BalanceControl* this);
void BalanceControl_run(BalanceControl* this, RunnerInfo* runnerInfo, MeasureInfo* measuerInfo);
void BalanceControl_chengeBalance(BalanceControl* this);
BOOL BalanceControl_checkEmergencyStop(BalanceControl* this);

#endif /* _BalanceControl_H_ */

