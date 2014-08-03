/*******************************************************************************
**  �t�@�C����  �FTimer.c
**  �T�v        �F�^�C�}�[�N���X
**  �ڍ�        �F
*******************************************************************************/

#include "Timer.h"



void Timer_init(Timer* this)
{
	this->initTime = 0;
}

// �^�C�}�[���Z�b�g
void Timer_set(Timer* this)
{
	this->initTime = systick_get_ms();
}


// �Z�b�g�������Ԃ��o�߂������ǂ����𔻒�
BOOL Timer_check(Timer* this, int timer)
{
	U32 nowTime;

	nowTime = systick_get_ms();

	if(nowTime - this->initTime >= timer)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
