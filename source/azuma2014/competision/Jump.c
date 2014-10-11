/*******************************************************************************
**  �t�@�C����  �FJump.c
**  �T�v        �F�W�����v��N���X
**  �ڍ�        �F�W�����v��U���Ɋւ��鏈�����`�B
*******************************************************************************/

#include "Jump.h"

#define NONE			0		// �����l
#define TARGET			500		// 臒l
#define LOW				30		// �ᑬ
#define NORMAL			50		// �ʏ�
#define	BACK			-50		// ���
#define HOLE_DISTANCE	100		// ���s����(��)
#define BACK_DISTANCE	50		// ���s����(���)
#define FINISH_DISTANCE	150		// ���s����(�U��)
#define STOP_TIME		2000	// ��~����

void Jump_init(Jump* this)
{
	this->mode = START;
	this->orderNum = NONE;
}


BOOL Jump_action(Jump* this)
{
	switch(this->mode)
	{
	case START:
		// �����m�ɐ؂�ւ���
		this->orderNum = OrderList_lineTraceRunning(this->orderList,LOW,TARGET,NONE,NONE,HOLE_DISTANCE);
		this->mode = CHECK_HOLE;
		break;

	case CHECK_HOLE:
		// �������m���������肷��
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// �������m�����ꍇ�A�K�����s�ɐ؂�ւ���
			this->orderNum = OrderList_manualRunning(this->orderList,BACK,NONE,NONE,NONE,BACK_DISTANCE);
			this->mode = TAIL_CHANGE;
		}
		break;

	case TAIL_CHANGE:
		// �K�����s�ؑւ��������������肷��
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			this->orderNum = OrderList_manualRunning(this->orderList,NORMAL,NONE,NONE,NONE,FINISH_DISTANCE);
			// �K�����s�ؑւ����������ꍇ�A�K�����s�����s����
			this->mode = TAIL_RUN;
		}
		break;

	case TAIL_RUN:
		// �K�����s���������������肷��
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			this->orderNum = OrderList_manualRunning(this->orderList,NONE,NONE,NONE,STOP_TIME,NONE);
			// �K�����s�����������ꍇ�A�I�����������s����
			this->mode = FINISHED;
		}
		break;

	case FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// ��莞�Ԓ�~�����ꍇ�Atrue��Ԃ�
			return TRUE;
		}
	}
	// false��Ԃ�
	return FALSE;
}

