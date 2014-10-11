/*******************************************************************************
**  �t�@�C����  �FCommander.c
**  �T�v        �F�R�}���h���s�N���X
**  �ڍ�        �F
*******************************************************************************/

#include "Commander.h"

static void Commander_runComand(Commander* this, Info *info);
static void Commander_setCommandResult(Commander* this, BOOL isSuccess);

void Commander_init(Commander* this)
{
	// �����Ȃ�
}

/*------------------------------------------------------------------------------
--  �֐���      �FCommander_action
--  �T�v        �F�R�}���h�����s���A���ʂ��o�͂���
--              �F
--  ����        �Finfo �S���
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Commander_action(Commander* this, Info *info)
{
	Communication_getCommand(this->communication);
	if(this->command->command > 0)
	{
		Commander_runComand(this, info);
		Commander_setCommandResult(this, TRUE);
	}
	else
	{
		Commander_setCommandResult(this, FALSE);
	}
}

/*------------------------------------------------------------------------------
--  �֐���      �FCommander_runComand
--  �T�v        �F�R�}���h�����s����
--              �F
--  ����        �Finfo �S���
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Commander_runComand(Commander* this, Info *info)
{
	// �R�}���h�̏���
	switch(this->command->command){
		// �ً}��~
		case(99):
			info->runnerInfo->emergencyStopFlag = TRUE;
			break;
		// �����[�g�X�^�[�g
		case(1):
			info->startFlag = TRUE;
			break;

		// �K���p�x�ύX
		case(5):
		{
			info->runnerInfo->tail = this->command->value1;
			break;
		}
		// �O�i�l�ύX
		case(10):
		{
			info->runnerInfo->forward = this->command->value1;
			break;
		}
		// ����ʕύX
		case(11):
		{
			info->runnerInfo->turn = this->command->value1;
			break;
		}
		// ���C���g���[�X���s�t���O�ύX
		case(12):
		{
			if(this->command->value1 == 0)
			{
				info->settingInfo->lineTraceFlg = FALSE;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->lineTraceFlg = TRUE;
			}
			break;
		}
		// ���b�N�A�b�v�Q�[�g���s�t���O�ύX
		case(13):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->strategyState = 3;
			}
			break;
		}
		// �|��������s�t���O�ύX
		case(14):
		{
			if(this->command->value1 == 0)
			{
				info->runnerInfo->balanceFlag = FALSE;
			}
			else
			{
				info->runnerInfo->balanceFlag = TRUE;
			}
			break;
		}
		// �헪�t���O�ύX
		case(15):
		{
			info->strategyState = this->command->value1;
			break;
		}
		// ���C���G�b�W�ؑփt���O�ύX
		case(16):
		{
			if(this->command->value1 == 0)
			{
				info->runnerInfo->chengeLineEdgeFlag = FALSE;
			}
			else
			{
				info->runnerInfo->chengeLineEdgeFlag = TRUE;
			}
			break;
		}
		// �W���C���Z���T�̃I�t�Z�b�g�l�ύX
		case(21):
		{
			info->runnerInfo->gyroOffset = this->command->value1;
			break;
		}

		// 臒l�ύX
		case(22):
		{
			info->settingInfo->target = this->command->value1;
			break;
		}

		// �_�b�V���@�\�I���I�t�A�I�t�Z�b�g�l����C�ɏグ���
		case(23):
		{
			if(info->runnerInfo->dashFlag == FALSE)
			{
				info->runnerInfo->dashvol = this->command->value1;
				info->runnerInfo->dashFlag = TRUE;
				break;
			}
			else
			{
				info->runnerInfo->dashFlag = FALSE;
				break;
			}
		}
		// �_�b�V���@�\�Ŏg���A�I�t�Z�b�g�l���グ��Ԋu�i�b�j
		case(24):
		{
			info->runnerInfo->dashlim = this->command->value1;
			info->runnerInfo->dashlim = info->runnerInfo->dashlim * 250;
			break;
		}

		// P����l�ύX
		case(31):
		{
			info->settingInfo->pidP = this->command->value1 / 100;
			break;
		}
		// I����l�ύX
		case(32):
		{
			info->settingInfo->pidI = this->command->value1 / 100;
			break;
		}
		// D����l�ύX
		case(33):
		{
			info->settingInfo->pidD = this->command->value1 / 100;
			break;
		}
		// �����헪�ؑփt���O
		case(50):
		{
			if(this->command->value1 == 0)
			{
				info->autoStrategyFlag = FALSE;
			}
			else
			{
				info->autoStrategyFlag = TRUE;
			}
			break;
		}
		// �R�[�X�ؑ�
		case(51):
		{
			info->settingInfo->courseType = this->command->value1;
			break;
		}

		// �W�����v��
		case(60):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 0;
				info->strategyState = 50;
			}
			break;
		}
		// �d�l���m��
		case(61):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 0;
				info->strategyState = 51;
			}
			break;
		}
		// ���[�O��
		case(62):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 1;
				info->strategyState = 50;
			}
			break;
		}
		// �t�B�M���AL
		case(63):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 1;
				info->strategyState = 51;
			}
			break;
		}
		// ���C�����A(������)
		case(64):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 1;
				info->strategyState = 52;
			}
			break;
		}
		// ���C�����A(�E����)
		case(65):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 1;
				info->strategyState = 53;
			}
			break;
		}
		// ���C���ؑ�
		case(66):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 1;
				info->strategyState = 54;
			}
			break;
		}
		// �Ռ����m
		case(67):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 1;
				info->strategyState = 55;
			}
			break;
		}

		// �헪�ؑ�
		case(69):
		{
			info->settingInfo->courseType = this->command->value1;
			info->strategyState = this->command->value2;
			break;
		}
		// �w�����X�g�ǉ�
		case(70):
		{
			switch(this->command->value1)
			{
				case(0):
				{
					// �}�j���A�����s
					OrderList_manualRunning(this->orderList, this->command->value2, this->command->value3, this->command->value4, this->command->value5, this->command->value6);
					break;
				}
				case(1):
				{
					// ���C���g���[�X���s
					OrderList_lineTraceRunning(this->orderList, this->command->value2, this->command->value3, this->command->value4, this->command->value5, this->command->value6);
					break;
				}
				case(2):
				{
					// ��~
					OrderList_stop(this->orderList);
					break;
				}
				case(3):
				{
					// PID����萔�ݒ�
					OrderList_setPID(this->orderList, this->command->value2, this->command->value3, this->command->value4);
					break;
				}
				case(4):
				{
					// ���͈͍�����
					OrderList_turnOnSpotLeft(this->orderList, this->command->value2, this->command->value3, this->command->value4, this->command->value5);
					break;
				}
				case(5):
				{
					// ���͈͉E����
					OrderList_turnOnSpotRight(this->orderList, this->command->value2, this->command->value3, this->command->value4, this->command->value5);
					break;
				}
			}
			break;
		}
	}
}


/*------------------------------------------------------------------------------
--  �֐���      �FCommander_setCommandResult
--  �T�v        �F�R�}���h�̎��s���ʂ��o�͂���
--              �F
--  ����        �FisSuccess �����t���O
--              �F  TRUE ���� / FALSE ���s
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Commander_setCommandResult(Commander* this, BOOL isSuccess)
{
	if(isSuccess == TRUE)
	{
		ecrobot_sound_tone(659, 100, 95);
		Communication_setLogData1(this->communication, 1);
	}
	else
	{
		Communication_setLogData1(this->communication, 0);
	}
}
