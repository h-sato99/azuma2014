/*******************************************************************************
**  �t�@�C����  �FCompetision.c
**  �T�v        �F���Z�N���X
**  �ڍ�        �F
*******************************************************************************/

#include "Competision.h"



void Competision_init(Competision* this)
{
	// �����Ȃ�
}

/*------------------------------------------------------------------------------
--  �֐���      �FCompetision_action
--  �T�v        �F���Z�p�̏��������s����
--              �F
--  ����        �Finfo  �S���
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Competision_action(Competision* this, Info *info)
{
	LineTracer_trace(this->lineTracer, info);

	Strategy_action(this->strategy, info);

	RoboControl_control(this->roboControl);
	//Runner_run(this->runner, info);
}
