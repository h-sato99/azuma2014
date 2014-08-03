/*******************************************************************************
**  �t�@�C����  �FCheckStart.c
**  �T�v        �F�X�^�[�g����N���X
**  �ڍ�        �F�X�^�[�g�̔�����s��
*******************************************************************************/

#include "CheckStart.h"

static void CheckStart_start(CheckStart* this, Info* info);

// ����������
void CheckStart_init(CheckStart* this)
{
	this->started = 0;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCheckStart_isStart
--  �T�v        �F�X�^�[�g�������ǂ�����Ԃ�
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�X�^�[�g��� (TRUE �X�^�[�g / FALSE ���X�^�[�g)
------------------------------------------------------------------------------*/
BOOL CheckStart_isStart(CheckStart* this)
{
	if(this->started == 1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*------------------------------------------------------------------------------
--  �֐���      �FCheckStart_waitStart
--  �T�v        �F�X�^�[�g�̍��}������܂őҋ@����
--              �F
--  ����        �Finfo �S���(�X�^�[�g�t���O���g�p)
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void CheckStart_waitStart(CheckStart* this, Info* info)
{
	if(this->started == 1)
	{
		return;
	}
	// �^�b�`�Z���T���������܂ŁA�҂�������
	// ���S�|����Ԃɂ���
	Tail_setAngle(this->tail, info->runnerInfo->tail);

	if(info->startFlag == TRUE)
	{
		CheckStart_start(this, info);
	}

	if(TouchSensor_isPressed(this->touchSensor))
	{
		CheckStart_start(this, info);
	}
}

/*------------------------------------------------------------------------------
--  �֐���      �FCheckStart_start
--  �T�v        �F�X�^�[�g�̍��}���󂯂��Ƃ��Ɏ��s����
--              �F
--  ����        �Finfo �S���
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void CheckStart_start(CheckStart* this, Info* info)
{
	ecrobot_sound_tone(659, 100, 70);
	this->started = 1;
	info->runnerInfo->tail = 0;
	info->strategyState = 9;
	if(info->autoStrategyFlag == TRUE)
	{
		info->strategyState = 1;
	}
}

