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
				if(Course_IN_StartToCurve(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// �J�[�u
			case(3):
			{
				if(Course_IN_CurveToLineChange(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// ���C���ؑ�
			case(4):
			{
				if(LineChange_action(this->lineChange) == TRUE)
				{
					info->strategyState++;
				}
				break;
			}
			// 2���ڃX�^�[�g�n�_
			case(5):
			{
				if(Course_IN_LineChangeToReStart(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// �X�^�[�g����̒���
			case(6):
			{
				if(Course_IN_StartToCurve(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// 2���ڃJ�[�u
			case(7):
			{
				if(Course_IN_CurveToMogul(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// ����m
			case(8):
			{
				if(TrialDecision_action(this->trialDecision))
				{
					info->strategyState++;
				}
				break;
			}
			// ���[�O��
			case(9):
			{
				if(Mogul_main(this->mogul))
				{
					info->strategyState++;
				}
				break;
			}
			// �}�j���A�����s�ؑ�
			case(10):
			{
				if(Course_IN_MogulToManual(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// �}�j���A�����s
			case(11):
			{
				if(Course_IN_ManualToFigureL(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// ����m
			case(12):
			{
				if(TrialDecision_action(this->trialDecision))
				{
					info->strategyState++;
				}
				break;
			}
			// �t�B�M���AL
			case(13):
			{
				//ecrobot_sound_tone(800, 200, 95);
				if(FigureL_action(this->figureL))
				{
					info->strategyState++;
				}
				break;
			}
			// ��~�ʒu�܂ő��s
			case(14):
			{
				if(Course_IN_FigureLToStop(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// ��~
			case(15):
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
			// �R�[�X�N���X������
			case(1):
			{
				Course_resetMode(this->course);
				info->strategyState++;
				break;
			}
			// �X�^�[�g
			case(2):
			{
				if(Course_OUT_StartToCurve(this->course))
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// ��1�J�[�u
			case(3):
			{
				if(Course_OUT_CurveToJump(this->course))
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// ����m
			case(4):
			{
				if(TrialDecision_action(this->trialDecision))
				{
					info->strategyState++;
				}
				break;
			}
			// �W�����v��
			case(5):
			{
				if(Jump_action(this->jump))
				{
					info->strategyState++;
				}
				break;
			}
			// �_�b�V���J�n
			case(6):
			{
				if(Course_OUT_JumpToDashStart(this->course))
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// �_�b�V��
			case(7):
			{
				if(Course_OUT_DashStartToDashEnd(this->course))
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// �_�b�V���I��
			case(8):
			{
				if(Course_OUT_DashEndToPending(this->course))
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// ����m
			case(9):
			{
				if(TrialDecision_action(this->trialDecision))
				{
					info->strategyState++;
				}
				break;
			}
			// �d�l���m��G���A
			case(10):
			{
				if(PendingArea_action(this->pendingArea))
				{
					info->strategyState++;
				}
				break;
			}
			// ��4�J�[�u
			case(11):
			{
				if(Course_OUT_PendingToCurve(this->course))
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// �S�[��
			case(12):
			{
				if(Course_OUT_CurveToGoal(this->course))
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// ��~
			case(13):
			{
				// stop
				break;
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

