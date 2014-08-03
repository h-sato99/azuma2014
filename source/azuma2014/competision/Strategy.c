/*******************************************************************************
**  �t�@�C����  �FStrategy.c
**  �T�v        �F�헪�N���X
**  �ڍ�        �F
*******************************************************************************/

#include "Strategy.h"

#define BASIC_DISTANCE_OUT 25500
#define BASIC_DISTANCE_IN 23500

static void Strategy_checkState(Strategy* this, Info* info);
static BOOL Strategy_checkBasicStage(Strategy* this, Info* info);
static BOOL Strategy_checkLookUpGate(Strategy* this, Info* info);
static BOOL Strategy_checkSeesaw(Strategy* this, Info* info);

void Strategy_init(Strategy* this)
{
	this->initBasicStageFlag = FALSE;
	this->startGrayDecision = FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FStrategy_action
--  �T�v        �F�헪�����s����
--              �F
--  ����        �Finfo  �S���
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Strategy_action(Strategy* this, Info* info)
{
	Strategy_checkState(this, info);

	switch(info->strategyState)
	{
		case(1):
		{
			// �x�[�V�b�N�X�e�[�W
			BasicStage_action(this->basicStage, info);
			break;
		}
		case(2):
		{
			// �V�[�\�[
			Seesaw_action(this->seesaw, info);
			break;
		}
		case(3):
		{
			// ���b�N�A�b�v�Q�[�g
			LookUpGate_action(this->lookUpGate, info);
			break;
		}
		case(4):
		{
			// �K���[�W�C��
			GarageIn_action(this->garageIn, info);
			break;
		}
	}
}

/*------------------------------------------------------------------------------
--  �֐���      �FStrategy_checkState
--  �T�v        �F�헪�̐؂�ւ����s��
--              �F
--  ����        �Finfo  �S���
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
static void Strategy_checkState(Strategy* this, Info* info)
{
	BOOL check;

	if(info->autoStrategyFlag == FALSE)
	{
		return;
	}

	// �헪�̐؂�ւ����s��
	switch(info->strategyState)
	{
		case(1):
		{
			// �x�[�V�b�N�X�e�[�W
			check = Strategy_checkBasicStage(this, info);
			if(check == TRUE)
			{
				ecrobot_sound_tone(659, 100, 95);
				info->strategyState = 10;

				// ��p��臒l��ݒ肷��
				info->settingInfo->target = info->settingInfo->target - 50;
			}
			break;
		}
		case(2):
		{
			// �V�[�\�[
			check = Strategy_checkSeesaw(this, info);
			if(check == TRUE)
			{
				// �K���[�W�C���֐ؑ�
				info->strategyState = 4;
			}
			break;
		}
		case(3):
		{
			// ���b�N�A�b�v�Q�[�g
			check = Strategy_checkLookUpGate(this, info);
			if(check == TRUE)
			{
				// �K���[�W�C���֐ؑ�
				info->strategyState = 4;
			}
			break;
		}
		case(10):
		{
			// �P��ڂ̊D�F���m����
			if(info->settingInfo->courseType == 0)
			{
				// �V�[�\�[�֐ؑ�
				info->strategyState = 2;
			}
			else
			{
				// ���b�N�A�b�v�Q�[�g�֐ؑ�
				info->strategyState = 3;
			}
		}
	}
}

/*------------------------------------------------------------------------------
--  �֐���      �FStrategy_checkBasicStage
--  �T�v        �F�x�[�V�b�N�X�e�[�W�̏I���𔻒肷��
--              �F
--  ����        �Finfo  �S���
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
static BOOL Strategy_checkBasicStage(Strategy* this, Info* info)
{
	int checkDistance;
	if(this->initBasicStageFlag == FALSE)
	{
		Distance_set(this->distance, info->measureInfo);
		this->initBasicStageFlag = TRUE;
		return FALSE;
	}
	else
	{
		if(info->settingInfo->courseType == 0)
		{
			checkDistance = BASIC_DISTANCE_OUT;
		}
		else
		{
			checkDistance = BASIC_DISTANCE_IN;
		}
		if(Distance_check(this->distance, info->measureInfo, checkDistance))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

/*------------------------------------------------------------------------------
--  �֐���      �FStrategy_checkLookUpGate
--  �T�v        �F���b�N�A�b�v�Q�[�g�̏I���𔻒肷��
--              �F
--  ����        �Finfo  �S���
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
static BOOL Strategy_checkLookUpGate(Strategy* this, Info* info)
{
	if(LookUpGate_checkFinish(this->lookUpGate) == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*------------------------------------------------------------------------------
--  �֐���      �FStrategy_checkSeesaw
--  �T�v        �F�V�[�\�[�̏I���𔻒肷��
--              �F
--  ����        �Finfo  �S���
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
static BOOL Strategy_checkSeesaw(Strategy* this, Info* info)
{
	if(Seesaw_checkFinish(this->seesaw) == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
