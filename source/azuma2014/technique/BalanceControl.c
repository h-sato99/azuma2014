/*******************************************************************************
**  ファイル名  ：BalanceControl.c
**  概要        ：倒立制御クラス
**  詳細        ：
*******************************************************************************/

#include "BalanceControl.h"

#define C_MOTOR_PWM 60;
#define C_MOTOR_DISTANCE 100;

// バッテリー電圧
#define C_BATT  8000

void BalanceControl_checkBalanceFlag(BalanceControl* this, RunnerInfo* runnerInfo);
void BalanceControl_chengeBalanceRun(BalanceControl* this, RunnerInfo* runnerInfo, MeasureInfo* measuerInfo);
void BalanceControl_chengeTailRun(BalanceControl* this, RunnerInfo* runnerInfo, MeasureInfo* measuerInfo);
static void BalanceControl_calcMotor(BalanceControl* this, F32 forward, F32 turn);

// 初期化する
void BalanceControl_init(BalanceControl* this)
{
	this->isInitialized = FALSE;
	this->leftMotorPwm = 0;
	this->rightMotorPwm = 0;
	this->balanceMode = 0;
	this->lastBalanceFlag = TRUE;
	this->emergencyStopFlag = FALSE;
}

void BalanceControl_run(BalanceControl* this, RunnerInfo* runnerInfo, MeasureInfo* measuerInfo)
{
	BalanceControl_checkBalanceFlag(this, runnerInfo);

	switch(this->balanceMode)
	{
		case(1):
			BalanceControl_chengeBalanceRun(this, runnerInfo, measuerInfo);
			break;

		case(2):
			BalanceControl_chengeTailRun(this, runnerInfo, measuerInfo);
			break;

		default:
			if(runnerInfo->balanceFlag == FALSE)
			{
				BalanceControl_calcMotor(this, runnerInfo->forward, runnerInfo->turn);
			}
			else
			{
				BalanceControl_BalanceRun(this, runnerInfo);
			}
	}
}

void BalanceControl_checkBalanceFlag(BalanceControl* this, RunnerInfo* runnerInfo)
{
	if(this->balanceMode == 0)
	{
		if(runnerInfo->balanceFlag != this->lastBalanceFlag)
		{
			if(runnerInfo->balanceFlag == TRUE)
			{

			}
			else
			{
				this->chengeMode = 0;
				this->balanceMode = 2;
			}
		}
		this->lastBalanceFlag = runnerInfo->balanceFlag;
	}
}

void BalanceControl_chengeBalanceRun(BalanceControl* this, RunnerInfo* runnerInfo, MeasureInfo* measuerInfo)
{
	int diffTail;

	diffTail = runnerInfo->tail - measuerInfo->tailAngle;
	if(diffTail > -5 && diffTail < 5)
	{
		this->balanceMode = 0;
	}
	else
	{
		this->leftMotorPwm = -C_MOTOR_PWM;
		this->rightMotorPwm = -C_MOTOR_PWM;
	}
}

void BalanceControl_chengeTailRun(BalanceControl* this, RunnerInfo* runnerInfo, MeasureInfo* measuerInfo)
{
	int distance;

	switch(this->chengeMode)
	{
		case(0):
			Distance_set(this->distance, measuerInfo);
			this->chengeMode = 1;
			this->leftMotorPwm = C_MOTOR_PWM;
			this->rightMotorPwm = C_MOTOR_PWM;
			break;
		case(1):
			distance = C_MOTOR_DISTANCE;
			if(Distance_check(this->distance, measuerInfo, 100))
			{
				this->chengeMode = 0;
				this->balanceMode = 0;
				this->leftMotorPwm = 0;
				this->rightMotorPwm = 0;
			}
			else
			{
				this->leftMotorPwm = C_MOTOR_PWM;
				this->rightMotorPwm = C_MOTOR_PWM;
			}
	}
}

int BalanceControl_getLeftMotorPwm(BalanceControl* this)
{
	return this->leftMotorPwm;
}
int BalanceControl_getRightMotorPwm(BalanceControl* this)
{
	return this->rightMotorPwm;
}

/*------------------------------------------------------------------------------
--  関数名      ：BalanceControl_BalanceRun
--  概要        ：倒立走行を行う。
--              ：
--  引数        ：forward   前進値
--              ：turn      旋回値
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void BalanceControl_BalanceRun(BalanceControl* this, RunnerInfo* runnerInfo)
{
	unsigned int gyro;		// ジャイロセンサ値
	unsigned int gyro_offset;	// ジャイロセンサオフセット値
	long motor_ang_l;		// 左モータ回転角度
	long motor_ang_r;		// 右モータ回転角度
	signed char pwm_l;		// 左モータPWM出力値
	signed char pwm_r;		// 右モータPWM出力値

	// 最初だけ、倒立振子制御を初期化とモータエンコーダのリセットを行う
	if(! this->isInitialized)
	{
		balance_init();		// 倒立振子制御初期化

		// モータエンコーダをリセットする
		nxt_motor_set_count(NXT_PORT_C, 0);
		nxt_motor_set_count(NXT_PORT_B, 0);

		// 初期化済にする
		this->isInitialized = TRUE;
	}

	// 倒立振子制御API に渡すパラメータを取得する
	gyro_offset = runnerInfo->gyroOffset;
	gyro = GyroSensor_getAngularVelocity(this->gyroSensor);
	motor_ang_l = Wheel_getLeftAngle(this->wheel);
	motor_ang_r = Wheel_getRightAngle(this->wheel);

	// 緊急停止
	if(gyro > 800 || gyro < 300)
	{
		this->emergencyStopFlag = TRUE;
	}
	else
	{
		// 倒立振子制御APIを呼び出し、倒立走行するための
		// 左右モータ出力値を得る
		balance_control(
			runnerInfo->forward,
			runnerInfo->turn,
			(float)gyro, (float)gyro_offset,
			(float)motor_ang_l, (float)motor_ang_r,
			C_BATT,
			(signed char*)&pwm_l, (signed char*)&pwm_r
		);

		this->leftMotorPwm = pwm_l;
		this->rightMotorPwm = pwm_r;
	}
}

/*------------------------------------------------------------------------------
--  関数名      ：BalanceControl_calcMotor
--  概要        ：前進値と旋回値から左右モータの出力を計算する
--              ：※（2012年度の尻尾走行を参考）
--              ：
--  引数        ：runnerInfo  走行情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
static void BalanceControl_calcMotor(BalanceControl* this, F32 forward, F32 turn)
{
	int leftPwm;
	int rightPwm;

	// 前後進命令と旋回量からモータPWM出力値を算出
	leftPwm = (int)(forward + turn);
	rightPwm = (int)(forward - turn);

	/*
	* PWM出力値がMAX値内になるように調整
	* 前進する場合のみ、PWM出力値がMAX値を超える場合は
	* もう片方のPWM出力値から超過分を減算
	*/
	// 左モータPWM出力値調整
	if(leftPwm > 100)
	{
		if(forward > 0)
		{
			rightPwm = rightPwm - (leftPwm - 100);
		}
		leftPwm = 100;
	}
	else if(leftPwm < -100)
	{
		leftPwm = -100;
	}
	// 右モータPWM出力値調整
	if(rightPwm > 100)
	{
		if(forward > 0)
		{
			leftPwm = leftPwm - (rightPwm - 100);
		}
		rightPwm = 100;
	}
	else if(rightPwm <-100)
	{
		rightPwm = -100;
	}

	// 前進命令の場合、モーターは逆回転させない
	if(forward > 0)
	{
		if(leftPwm < 0)
		{
			leftPwm = 0;
		}
		if(rightPwm < 0)
		{
			rightPwm = 0;
		}
	}

	this->leftMotorPwm = leftPwm;
	this->rightMotorPwm = rightPwm;
}

BOOL BalanceControl_checkEmergencyStop(BalanceControl* this)
{
	return this->emergencyStopFlag;
}

