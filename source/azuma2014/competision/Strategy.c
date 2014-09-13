/*******************************************************************************
**  �t�@�C����  �FStrategy.c
**  �T�v        �F�헪�N���X
**  �ڍ�        �F
*******************************************************************************/

#include "Strategy.h"

#define BASIC_DISTANCE_OUT 25500
#define BASIC_DISTANCE_IN 23500

static void Strategy_checkState(Strategy* this, Info* info);

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
			// ��p
			break;
		}
		case(3):
		{
			// ��p
			break;
		}
		case(4):
		{
			// ��p
			break;
		}
		case(10):
		{
			if(TrialDecision_action(this->trialDecision))
			{
				Jump_action(this->jump);
			}
			break;
		}
		case(11):
		{
			if(TrialDecision_action(this->trialDecision))
			{
				Mogul_main(this->mogul);
			}
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

}

