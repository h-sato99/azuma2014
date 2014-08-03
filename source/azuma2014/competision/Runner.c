/*******************************************************************************
**  �t�@�C����  �FRunner.c
**  �T�v        �F���s�N���X
**  �ڍ�        �F
*******************************************************************************/

#include "Runner.h"

static void Runner_setLineEge(Runner* this, RunnerInfo* runnerInfo);
static void Runner_setMeasureInfo(Runner* this, MeasureInfo* measureInfo);

void Runner_init(Runner* this)
{
	// �����Ȃ�
}

/*------------------------------------------------------------------------------
--  �֐���      �FRunner_run
--  �T�v        �F���[�^�ɑ��s�w����^����
--              �F  ��turn(����l)�̓����͉��L�̒ʂ�
--              �F    ����l���O�̏ꍇ�F�E�����ɐ��񂷂�
--              �F    ����l���O�̏ꍇ�F���񂵂Ȃ�
--              �F    ����l���O�̏ꍇ�F�������ɐ��񂷂�
--              �F
--  ����        �FrunnerInfo  ���s���
--  �߂�l      �F�Ȃ�
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
		// �ʏ�̑��s
		BalanceControl_run(this->balanceControl, info->runnerInfo, info->measureInfo);
		leftMotor = BalanceControl_getLeftMotorPwm(this->balanceControl);
		rightMotor = BalanceControl_getRightMotorPwm(this->balanceControl);
		tail = info->runnerInfo->tail;
	}
	else
	{
		// �ً}��~
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
--  �֐���      �FRunner_calcMotor
--  �T�v        �F�g���[�X���郉�C���G�b�W��ݒ肷��
--              �F�ʏ�͉E�G�b�W�i���C���̉E���j�����C�����[�X����
--              �F
--  ����        �FrunnerInfo  ���s���
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
static void Runner_setLineEge(Runner* this, RunnerInfo* runnerInfo)
{
	if(runnerInfo->chengeLineEdgeFlag == TRUE)
	{
		runnerInfo->turn *= -1;
	}
}

