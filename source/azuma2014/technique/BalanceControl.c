/*******************************************************************************
**  �t�@�C����  �FBalanceControl.c
**  �T�v        �F�|������N���X
**  �ڍ�        �F
*******************************************************************************/

#include "BalanceControl.h"

#define C_MOTOR_PWM 60;
#define C_MOTOR_DISTANCE 100;

// �o�b�e���[�d��
#define C_BATT  8000

void BalanceControl_checkBalanceFlag(BalanceControl* this, RunnerInfo* runnerInfo);
void BalanceControl_chengeBalanceRun(BalanceControl* this, RunnerInfo* runnerInfo, MeasureInfo* measuerInfo);
void BalanceControl_chengeTailRun(BalanceControl* this, RunnerInfo* runnerInfo, MeasureInfo* measuerInfo);
static void BalanceControl_calcMotor(BalanceControl* this, F32 forward, F32 turn);

// ����������
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
--  �֐���      �FBalanceControl_BalanceRun
--  �T�v        �F�|�����s���s���B
--              �F
--  ����        �Fforward   �O�i�l
--              �Fturn      ����l
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void BalanceControl_BalanceRun(BalanceControl* this, RunnerInfo* runnerInfo)
{
	unsigned int gyro;		// �W���C���Z���T�l
	unsigned int gyro_offset;	// �W���C���Z���T�I�t�Z�b�g�l
	long motor_ang_l;		// �����[�^��]�p�x
	long motor_ang_r;		// �E���[�^��]�p�x
	signed char pwm_l;		// �����[�^PWM�o�͒l
	signed char pwm_r;		// �E���[�^PWM�o�͒l

	// �ŏ������A�|���U�q������������ƃ��[�^�G���R�[�_�̃��Z�b�g���s��
	if(! this->isInitialized)
	{
		balance_init();		// �|���U�q���䏉����

		// ���[�^�G���R�[�_�����Z�b�g����
		nxt_motor_set_count(NXT_PORT_C, 0);
		nxt_motor_set_count(NXT_PORT_B, 0);

		// �������ςɂ���
		this->isInitialized = TRUE;
	}

	// �|���U�q����API �ɓn���p�����[�^���擾����
	gyro_offset = runnerInfo->gyroOffset;
	gyro = GyroSensor_getAngularVelocity(this->gyroSensor);
	motor_ang_l = Wheel_getLeftAngle(this->wheel);
	motor_ang_r = Wheel_getRightAngle(this->wheel);

	// �ً}��~
	if(gyro > 800 || gyro < 300)
	{
		this->emergencyStopFlag = TRUE;
	}
	else
	{
		// �|���U�q����API���Ăяo���A�|�����s���邽�߂�
		// ���E���[�^�o�͒l�𓾂�
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
--  �֐���      �FBalanceControl_calcMotor
--  �T�v        �F�O�i�l�Ɛ���l���獶�E���[�^�̏o�͂��v�Z����
--              �F���i2012�N�x�̐K�����s���Q�l�j
--              �F
--  ����        �FrunnerInfo  ���s���
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
static void BalanceControl_calcMotor(BalanceControl* this, F32 forward, F32 turn)
{
	int leftPwm;
	int rightPwm;

	// �O��i���߂Ɛ���ʂ��烂�[�^PWM�o�͒l���Z�o
	leftPwm = (int)(forward + turn);
	rightPwm = (int)(forward - turn);

	/*
	* PWM�o�͒l��MAX�l���ɂȂ�悤�ɒ���
	* �O�i����ꍇ�̂݁APWM�o�͒l��MAX�l�𒴂���ꍇ��
	* �����Е���PWM�o�͒l���璴�ߕ������Z
	*/
	// �����[�^PWM�o�͒l����
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
	// �E���[�^PWM�o�͒l����
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

	// �O�i���߂̏ꍇ�A���[�^�[�͋t��]�����Ȃ�
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

