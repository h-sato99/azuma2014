/*******************************************************************************
**  �t�@�C����  �FTimer.h
**  �T�v        �F�^�C�}�[�N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _Timer_H_
#define _Timer_H_

#include "kernel.h"
#include "ecrobot_interface.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct Timer
{
	U32 initTime;
} Timer;

// ���J����
void Timer_init(Timer* this);
void Timer_set(Timer* this);
BOOL Timer_check(Timer* this, int timer);

#endif /* _Timer_H_ */
