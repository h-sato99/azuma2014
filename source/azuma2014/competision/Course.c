/*******************************************************************************
**  �t�@�C����  �FCourse.c
**  �T�v        �F
**  �ڍ�        �F
*******************************************************************************/

#include "Course.h"
//#define C_TARGET 600
#define C_TARGET 500


/*------------------------------------------------------------------------------
--  �֐���      �FCourse_init
--  �T�v        �F�R�[�X������������B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Course_init(Course* this){
	this->orderNum = 0;
	this->mode = 0;
	this->target = C_TARGET;
}

void Course_resetMode(Course* this)
{
	//test
	//this->orderNum = OrderList_setPID(this->orderList,5,7,20);
	//test
	this->mode = 0;
}

// IN�R�[�X���i
/*------------------------------------------------------------------------------
--  �֐���      �FCourse_IN_StartToCurve
--  �T�v        �FIN�X�^�[�g�`��1�J�[�u
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_IN_StartToCurve(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,7,20);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					100,
					this->target,
					TURN_DRIVING,
					0,
					1000);
		}
		this->mode = 2;
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_IN_CurveToLineChange
--  �T�v        �FIN��1�J�[�u�`���C���ؑ�
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_IN_CurveToLineChange(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					20,
					this->target,
					TURN_FRONT,
					0,
					1800);
			this->mode = 2;
		}
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_IN_LineChangeToReStart
--  �T�v        �FIN���C���ؑց`�X�^�[�g(2����)
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_IN_LineChangeToReStart(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					20,
					this->target,
					TURN_FRONT,
					0,
					1800);
			this->mode = 2;
		}
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_IN_CurveToMogul
--  �T�v        �FIN��1�J�[�u(2����)�`���[�O��
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_IN_CurveToMogul(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					20,
					this->target,
					TURN_FRONT,
					0,
					1400);
			this->mode = 2;
		}
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_IN_MogulToManual
--  �T�v        �FIN���[�O���`�}�j���A�����s
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_IN_MogulToManual(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					20,
					this->target,
					TURN_FRONT,
					0,
					1800);
			this->mode = 2;
		}
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_IN_ManualToFigureL
--  �T�v        �FIN�}�j���A�����s�`�t�B�M���AL
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_IN_ManualToFigureL(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//�}�j���A�����s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_manualRunning(
					this->orderList,
					60,
					0,
					TURN_FRONT,
					0,
					800);
			this->mode = 2;
		}
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_IN_ManualToFigureL
--  �T�v        �FIN�t�B�M���AL�`��~
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_IN_FigureLToStop(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					20,
					this->target,
					TURN_FRONT,
					0,
					600);
			this->mode = 2;
		}
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

// OUT�R�[�X���i
/*------------------------------------------------------------------------------
--  �֐���      �FCourse_OUT_StartToCurve
--  �T�v        �FOUT�X�^�[�g�`��1�J�[�u
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_OUT_StartToCurve(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,7,20);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					100,
					this->target,
					TURN_DRIVING,
					0,
					1100);
		}
		this->mode = 2;
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_OUT_CurveToJump
--  �T�v        �FOUT��1�J�[�u�`�W�����v��
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_OUT_CurveToJump(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					40,
					this->target,
					TURN_DRIVING,
					0,
					600);
		}
		this->mode = 2;
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_OUT_JumpToDashStart
--  �T�v        �FOUT�W�����v��`�_�b�V���J�n
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_OUT_JumpToDashStart(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					40,
					this->target,
					TURN_DRIVING,
					0,
					600);
		}
		this->mode = 2;
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_OUT_DashStartToDashEnd
--  �T�v        �FOUT�_�b�V���J�n�`�_�b�V���I��
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_OUT_DashStartToDashEnd(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,7,20);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					100,
					this->target,
					TURN_DRIVING,
					0,
					800);
		}
		this->mode = 2;
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_OUT_DashToPending
--  �T�v        �FOUT�_�b�V���I���`�d�l���m��
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_OUT_DashEndToPending(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					40,
					this->target,
					TURN_DRIVING,
					0,
					800);
		}
		this->mode = 2;
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_OUT_PendingToCurve
--  �T�v        �FOUT�d�l���m��`��4�J�[�u
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_OUT_PendingToCurve(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					40,
					this->target,
					TURN_DRIVING,
					0,
					800);
		}
		this->mode = 2;
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_OUT_DashStartToDashEnd
--  �T�v        �FOUT��4�J�[�u�`�S�[��
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_OUT_CurveToGoal(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,7,20);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					100,
					this->target,
					TURN_DRIVING,
					0,
					800);
		}
		this->mode = 2;
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}
