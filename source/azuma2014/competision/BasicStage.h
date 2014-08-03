/*******************************************************************************
**  �t�@�C����  �FBasicStage.h
**  �T�v        �F�x�[�V�b�N�X�e�[�W�N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _BasicStage_H_
#define _BasicStage_H_

#include "Info.h"
#include "RunnerInfo.h"
#include "SettingInfo.h"
#include "technique/Distance.h"


// ������ێ����邽�߂̍\���̂̒�`
typedef struct BasicStage
{
	int mode;					// �X�C�b�`�p�J�E���^
	Distance *distance;			// �������i�p
} BasicStage;

// ���J����
void BasicStage_init(BasicStage* this);
void BasicStage_action(BasicStage* this, Info *info);

#endif /* _BasicStage_H_ */
