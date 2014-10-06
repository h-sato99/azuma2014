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

	// test
	if(info->autoStrategyFlag == FALSE)
	{
		//OrderTest_tailRun(this->orderTest);
		//OrderTest_figureL(this->orderTest);
		//OrderTest_strateRun(this->orderTest);
		//Course_strateRunIN(this->course);
		//Course_stableRunIN(this->course);
		return;
	}
	// test

	// �C���R�[�X
	if(info->settingInfo->courseType == 1){
		switch(info->strategyState)
		{
			// �R�[�X�N���X������
			case(1):
			{
				Course_resetMode(this->course);
				info->strategyState++;
				break;
			}
			// �X�^�[�g����̒���
			case(2):
			{
				if(Course_strateRunIN(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// ���[�O���܂ł̃J�[�u
			case(3):
			{
				if(Course_stableRunIN(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// �Ռ����m
			case(4):
			{
				if(TrialDecision_action(this->trialDecision))
				{
					info->strategyState++;
				}
				break;
			}
			// ���[�O��
			case(5):
			{
				if(Mogul_main(this->mogul))
				{
					info->strategyState++;
				}
				break;
			}
			case(6):
			{
				if(Course_stableRunIN(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			case(7):
			{
				if(LineChange_action(this->lineChange) == TRUE)
				{
					info->strategyState++;
				}
				break;
			}
			case(8):
			{
				//ecrobot_sound_tone(800, 200, 95);
				if(FigureL_action(this->figureL))
				{
					info->strategyState++;
				}
				break;
			}
			case(9):
			{
				if(Course_strateRunIN(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			case(10):
			{
				if(Course_stableRunIN(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			case(11):
			{
				// stop
				break;
			}
		}
	}
	// �A�E�g�R�[�X
	else
	{
		switch(info->strategyState)
		{
			case(1):
			{
				Course_resetMode(this->course);
				info->strategyState = 2;
				break;
			}
			case(2):
			{
				if(Course_strateRunOUT(this->course))
				{
					info->strategyState = 3;
				}
				break;
			}
			case(3):
			{
				if(Jump_action(this->jump))
				{
					info->strategyState = 4;
				}
				break;
			}
			case(4):
			{
				Course_resetMode(this->course);
				info->strategyState = 5;
				break;
			}
			case(5):
			{
				if(Course_stableRunOUT(this->course))
				{
					info->strategyState = 6;
				}
				break;
			}
			case(6):
			{
				if(PendingArea_action(this->pendingArea))
				{
					info->strategyState = 7;
				}
			}
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
	//BOOL check;

}

