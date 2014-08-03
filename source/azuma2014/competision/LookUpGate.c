/*******************************************************************************
**  �t�@�C����  �FLookUpGate.c
**  �T�v        �F���b�N�A�b�v�Q�[�g�N���X
**  �ڍ�        �F���b�N�A�b�v�Q�[�g���s�Ɋւ��鏈�����`�B
*******************************************************************************/

#include "LookUpGate.h"

#define STOP     		0 	// ��~
#define LOW     		30 	// �ᑬ
#define NORMAL  		80 	// �ʏ�
#define HIGH    		100 // ����
#define TAIL_ANGL		95	// �K���̊p�x(100�}5�Ƃ���)
#define STAIRS_ANGL1	80	// �K���̊p�x(�P�i�K�X��)
#define STAIRS_ANGL2	65	// �K���̊p�x(�Q�i�K�X��)
#define STAIRS_ANGL3	60	// �K���̊p�x
#define LOOKUP_FORWORD_STOP		0
#define LOOKUP_FORWORD_RUN		20
#define LOOKUP_BACK				-30
#define LOOKUP_FORWORD_WAKEUP	-40
#define LOOKUP_FORWORD_DISTANCE 30

int throwGateFlg;			// �Q�[�g�ʉ߃t���O

// ����������
void LookUpGate_init(LookUpGate* this)
{
	this->isInitialized	= FALSE; 					// �������t���O
	this->forward		= LOW;   					// �O�i�l
	this->turn			= -1;						// ����l
	this->tAngle		= TAIL_ANGL;				// �K���p�x
	this->sonar			= 255;						// ��Q���Ƃ̋���
	this->mode			= 0;						// ���s���[�h
	throwGateFlg        = 0;						// �Q�[�g�ʉ߃t���O
	this->isFinished =FALSE;
}


// ���b�N�A�b�v�Q�[�g�𑖍s����
void LookUpGate_action(LookUpGate* this, Info *info)
{
	// ������(�X�^�[�g���Ԃ̎擾)
	if(! this->isInitialized)
	{
		info->runnerInfo->forward = 20;

		// 40msec���Ƃɒ����g�Z���T�̒l���擾����
		if(0 <= systick_get_ms() % 40 && systick_get_ms() % 40 <= 5)
		{
			this->sonar = SonarSensor_get(this->sonarSensor);
		}


		// �����g�Z���T�̒l�𔻒�
		// ecrobot_get_sonar_sensor�����s���n�߂�����A�Z���T�l��0��Ԃ��B
		// ���̂��߁A0�ȉ��̏ꍇ�����b�N�A�b�v�Q�[�g�������J�n���Ȃ�
		// �悤�ɂ���K�v������B
		if(this->sonar <= 0 || this->sonar > 10)
		{
			// 0�ȉ��܂���30���傫���ꍇ�A�����𒆒f����
			return;
		}
		else
		{
			// �������ςɂ���
			this->isInitialized = TRUE;
		}
	}


	switch(this->mode)
	{
		case 0:
			// ��Q���𔭌�������A���[�^���~�߂�
			// ���{���X����i�P�i�K�ځj
			Timer_set(this->timer);
			this->forward = 0;
			this->turn = 0;
			this->tAngle = STAIRS_ANGL1;
			this->mode++;
			info->runnerInfo->balanceFlag = FALSE;
			info->settingInfo->target += 50;
			info->settingInfo->lineTraceFlg = FALSE;
			ecrobot_sound_tone(500, 200, 100);
			break;

		case 1:
			// ���{���X����i�Q�i�K�ځj
			if(Timer_check(this->timer, 700))
			{
				Timer_set(this->timer);
				this->forward = LOW;
				this->turn = 0;
				this->tAngle = STAIRS_ANGL3;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 2:
			// ���i�i�Q�[�g��������j
			if(Distance_check(this->distance, info->measureInfo, 60))
			{
				Distance_set(this->distance, info->measureInfo);
				this->forward = LOW;
				this->turn = 0;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 3:
			// �E�F�C�g����
			if(Distance_check(this->distance, info->measureInfo, 380))
			{
				Timer_set(this->timer);
				this->forward = 0;
				this->turn = 0;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 4:
			// �o�b�N����i�Q�[�g��������j
			if(Timer_check(this->timer, 500))
			{
				Distance_set(this->distance, info->measureInfo);
				this->forward = LOOKUP_BACK;
				this->turn = 0;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 5:
			// �E�F�C�g����
			if(Distance_check(this->distance, info->measureInfo, 420))
			{
				Timer_set(this->timer);
				this->forward = 0;
				this->turn = 0;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 6:
			// �P�b�E�F�C�g������ᑬ�Œ��i�i�Q�[�g��������j
			if(Timer_check(this->timer, 500))
			{
				Distance_set(this->distance, info->measureInfo);
				this->forward = LOW;
				this->turn = 0;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 7:
			// �E�F�C�g����
			if(Distance_check(this->distance, info->measureInfo, 440))
			{
				Timer_set(this->timer);
				this->forward = 0;
				this->turn = 0;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 8:
			// ���{���X����i�P�i�K�ځj
			if(Timer_check(this->timer, 500))
			{
				Distance_set(this->distance, info->measureInfo);
				this->forward = LOOKUP_FORWORD_WAKEUP;
				this->turn = 0;
				this->tAngle = STAIRS_ANGL1;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 9:
			// ���{���X����i�P�i�K�ځj
			if(Distance_check(this->distance, info->measureInfo, 60))
			{
				Distance_set(this->distance, info->measureInfo);
				this->forward = LOOKUP_FORWORD_WAKEUP;
				this->turn = 0;
				this->tAngle = TAIL_ANGL;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 10:
			// ���{���X����i�P�i�K�ځj
			if(Distance_check(this->distance, info->measureInfo, 60))
			{
				Timer_set(this->timer);
				this->forward = 20;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
				info->settingInfo->target = 520;
				info->settingInfo->lineTraceFlg = TRUE;
			}
			break;
		default:
			this->isFinished =TRUE;
			return;
	}
	info->runnerInfo->forward = this->forward;
	info->runnerInfo->turn = this->turn;
	info->runnerInfo->tail = this->tAngle;
}

BOOL LookUpGate_checkFinish(LookUpGate* this)
{
	return this->isFinished;
}

