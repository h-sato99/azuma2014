/*******************************************************************************
**  �t�@�C����  �FGarageIn.h
**  �T�v        �F�K���[�W�C���N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _GarageIn_H_
#define _GarageIn_H_

#include "Info.h"
#include "technique/Distance.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct GarageIn
{
	BOOL isInitialized;             		// �������t���O
	int forward; 							// �O�i�l
	int turn;								// ����l
	int tAngle;								// �K���p�x
	Distance *distance;
} GarageIn;

// ���J����
void GarageIn_init(GarageIn* this);
void GarageIn_action(GarageIn* this, Info* info);

#endif /* _GarageIn_H_ */
