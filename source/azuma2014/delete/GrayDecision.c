/*******************************************************************************
**  �t�@�C����  �FGrayDecision.c
**  �T�v        �F�D�F���m�N���X
**  �ڍ�        �F�D�F���m�̔���p�������s���B
*******************************************************************************/

#include "GrayDecision.h"

#define C_WHITE_CAL    50   // ���F�̊�l�v�Z�p
#define C_GETCOUNT     15   // �擾�񐔂�����ȏォ�̊�l


/*------------------------------------------------------------------------------
--  �֐���      �FGrayDecision_init
--  �T�v        �F�D�F���m�Ŏg�p����S�ϐ����������B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void GrayDecision_init(GrayDecision* this)
{
	this->GrayPassCnt = 0;

	this->lightget = 0;
	this->light_target = 0;
	this->getcount = 0;

	this->isInitialized = FALSE;
	this->forward = 0;
	this->turn = -1;
	this->mode = 0;
}


/*------------------------------------------------------------------------------
--  �֐���      �FGrayDecision_setTarget
--  �T�v        �F���F��l����B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void GrayDecision_setTarget(GrayDecision* this, int target)
{
	// ���F��l���L�����u���[�V�����̔��{��v�Z�l�ɐݒ�
	this->light_target = target + C_WHITE_CAL;
}

/*------------------------------------------------------------------------------
--  �֐���      �FGrayDecision_main
--  �T�v        �F�D�F���m�̃��C�������B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void GrayDecision_main(GrayDecision* this, Info *info)
{
	this->forward = 0;
	this->turn = 0;
}
void GrayDecision_main_bk(GrayDecision* this, Info *info)
{
	// ���Z���T�̒l���擾����
	this->lightget = (int)LightSensor_getBrightness(this->lightSensor);

	// �擾�����l�����F��l�ȉ��ł��邩����
	if (this->lightget <= this->light_target)
	{
		// �擾�񐔃J�E���^��1�����Z����
		this->getcount = this->getcount + 1;

	}
	else
	{
		// �擾�񐔏�����
		this->getcount = 0;

		// ���C���g���[�X�ɖ߂�
		return;

	}

	// �擾�񐔂���l�ȏォ�i�E���������j�𔻒�
	if (this->getcount >= C_GETCOUNT)
	{
		// �X�^�[�g���Ԃ̎擾�i���߂̈�x�����s���j
		if(! this->isInitialized)
		{
			// �E�������X�^�[�g���Ԏ擾
			Timer_set(this->timer);
			// �������[�h���Q�ɐݒ�
			this->mode = 1;
			// �X�^�[�g���Ԏ擾�ςɂ���
			this->isInitialized = TRUE;
		}

		switch(this->mode)
		{
			case 1:
				// ���[�^�[���~�߂�
				this->forward = 0;
				this->turn = 0;
				// �������[�h�ɂQ��ݒ�
				this->mode = 2;
				break;

			case 2:
				// �O�D�T�b�E�F�C�g�����烉�C���֕��A�̏���
				if(Timer_check(this->timer, 500))
				{
					this->forward = 0;
					this->turn = 50;
					this->mode = 3;

				}
				break;

			case 3:
				// �P�b�E�F�C�g�����烉�C���֕��A�̏���
				if(Timer_check(this->timer, 1000))
				{
					this->forward = 30;
					this->turn = 0;

					// �e�ϐ�������
					this->mode = 0;
					this->getcount = 0;
					this->isInitialized = FALSE;

					//
					this->GrayPassCnt = this->GrayPassCnt + 1;

				}
				break;

			default:
				// ���C���g���[�X�ɖ߂�
				return;
		}

	// �l��ݒ肵�ă��C���g���[�X�ɖ߂�
	info->runnerInfo->forward = this->forward;
	info->runnerInfo->turn = this->turn;
	return;

	}
}
