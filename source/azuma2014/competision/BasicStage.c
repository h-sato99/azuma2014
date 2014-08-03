/*******************************************************************************
**  �t�@�C����  �FBasicStage.c
**  �T�v        �F�x�[�V�b�N�X�e�[�W�N���X
**  �ڍ�        �F
*******************************************************************************/

#include "BasicStage.h"



void BasicStage_init(BasicStage* this)
{
	this->mode = 0;					// �X�C�b�`�p�J�E���^
}

/*------------------------------------------------------------------------------
--  �֐���      �FBasicStage_action
--  �T�v        �F�x�[�V�b�N�X�e�[�W�p�̏��������s����
--              �F
--  ����        �Finfo  �S���
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void BasicStage_action(BasicStage* this, Info *info)
{
	if(info->settingInfo->courseType == 1){
		// �C���R�[�X�p
		switch(this->mode){

			// �ycase0�z�O�i�l��40�ɐݒ�
			case 0:
				Distance_set(this->distance, info->measureInfo);
				info->runnerInfo->forward = 40;
				info->runnerInfo->dashFlag = FALSE;
				info->runnerInfo->dashvol = 0;
				info->runnerInfo->dashlim = 0;
				this->mode++;
			break;

			// �ycase1�z�O�i�l��60�ɐݒ�
			case 1:
				if(Distance_check(this->distance, info->measureInfo, 200)){
					info->runnerInfo->forward = 60;
					info->runnerInfo->dashFlag = FALSE;
					info->runnerInfo->dashvol = 0;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;

			// �ycase2�z�O�i�l��80�ɐݒ�
			case 2:
				if(Distance_check(this->distance, info->measureInfo, 400)){
					info->runnerInfo->forward = 80;
					info->runnerInfo->dashFlag = FALSE;
					info->runnerInfo->dashvol = 0;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;

			// �ycase3�z�I�t�Z�b�g�l��5�グ�ă_�b�V��
			case 3:
				if(Distance_check(this->distance, info->measureInfo, 600)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// �_�b�V���t���O�I�t
			case 4:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// �ycase4�z�I�t�Z�b�g�l��5�グ�ă_�b�V��
			case 5:
				if(Distance_check(this->distance, info->measureInfo, 6800)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// �_�b�V���t���O�I�t
			case 6:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// �ycase5�z�I�t�Z�b�g�l��5�グ�ă_�b�V��
			case 7:
				if(Distance_check(this->distance, info->measureInfo, 10600)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// �_�b�V���t���O�I�t
			case 8:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// �ycase6�z�I�t�Z�b�g�l��5�グ�ă_�b�V��
			case 9:
				if(Distance_check(this->distance, info->measureInfo, 14700)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// �_�b�V���t���O�I�t
			case 10:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// �ycase7�z�I�t�Z�b�g�l��5�グ�ă_�b�V��
			case 11:
				if(Distance_check(this->distance, info->measureInfo, 18500)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// �_�b�V���t���O�I�t
			case 12:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

		}
	}
	else{
		// �A�E�g�R�[�X�p
		switch(this->mode){

			// �ycase0�z�O�i�l��40�ɐݒ�
			case 0:
				Distance_set(this->distance, info->measureInfo);
				info->runnerInfo->forward = 40;
				info->runnerInfo->dashFlag = FALSE;
				info->runnerInfo->dashvol = 0;
				info->runnerInfo->dashlim = 0;
				this->mode++;
			break;

			// �ycase1�z�O�i�l��60�ɐݒ�
			case 1:
				if(Distance_check(this->distance, info->measureInfo, 200)){
					info->runnerInfo->forward = 60;
					info->runnerInfo->dashFlag = FALSE;
					info->runnerInfo->dashvol = 0;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;

			// �ycase2�z�O�i�l��80�ɐݒ�
			case 2:
				if(Distance_check(this->distance, info->measureInfo, 400)){
					info->runnerInfo->forward = 80;
					info->runnerInfo->dashFlag = FALSE;
					info->runnerInfo->dashvol = 0;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;

			// �ycase3�z�I�t�Z�b�g�l��5�グ�ă_�b�V��
			case 3:
				if(Distance_check(this->distance, info->measureInfo, 5700)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// �_�b�V���t���O�I�t
			case 4:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// �ycase4�z�I�t�Z�b�g�l��5�グ�ă_�b�V��
			case 5:
				if(Distance_check(this->distance, info->measureInfo, 10500)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// �_�b�V���t���O�I�t
			case 6:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// �ycase5�z�I�t�Z�b�g�l��5�グ�ă_�b�V��
			case 7:
				if(Distance_check(this->distance, info->measureInfo, 15000)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// �_�b�V���t���O�I�t
			case 8:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// �ycase6�z�I�t�Z�b�g�l��5�グ�ă_�b�V��
			case 9:
				if(Distance_check(this->distance, info->measureInfo, 18000)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
				this->mode++;
			break;
			// �_�b�V���t���O�I�t
			case 10:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// �ycase7�z�I�t�Z�b�g�l��5�グ�ă_�b�V��
			case 11:
				if(Distance_check(this->distance, info->measureInfo, 21500)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
				this->mode++;
			break;
			// �_�b�V���t���O�I�t
			case 12:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// �ycase8�z�����P
			case 13:
				if(Distance_check(this->distance, info->measureInfo, 25000)){
					info->runnerInfo->forward = 50;
					info->runnerInfo->dashFlag = FALSE;
					info->runnerInfo->dashvol = 0;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// �_�b�V���t���O�I�t
			case 14:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// �ycase9�z�����Q
			case 15:
				if(Distance_check(this->distance, info->measureInfo, 25300)){
					info->runnerInfo->forward = 20;
					info->runnerInfo->dashFlag = FALSE;
					info->runnerInfo->dashvol = 0;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// �_�b�V���t���O�I�t
			case 16:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;
		}
	}
}
