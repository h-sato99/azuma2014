/*******************************************************************************
**  �t�@�C����  �FTrialDecision.c
**  �T�v        �F����m�N���X
**  �ڍ�        �F
*******************************************************************************/

#include "TrialDecision.h"

#define NONE			0		// �����l
#define TARGET			550		// 臒l
#define LOW				25		// �ᑬ
#define NORMAL			50		// �ʏ�
#define HIGH			100		// ����
#define	BACK			-40		// ���
#define BACK_DISTANCE	100		// ���s����(���)
#define DASH_DISTANCE	140		// ���s����(����)
#define STOP_TIME		2000	// ��~����

typedef enum State
{
	START,
	CHECK_BUMP,
	BACK_RUN,
	TAIL_CHANGE,
	FINISHED
} State;

void TrialDecision_init(TrialDecision* this)
{
	this->mode = START;
	this->orderNum = NONE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FTrialDecision_action
--  �T�v        �F����m���������s����
--              �F
--  ����        �F
--  �߂�l      �Ftrue(��������)�Afalse(����������)
------------------------------------------------------------------------------*/
BOOL TrialDecision_action(TrialDecision* this)
{
	switch(this->mode)
	{
	case START:
		// �ᑬ���s�ɐ؂�ւ���
		this->orderNum = OrderList_lineTraceRunning(this->orderList,LOW,TARGET,TURN_FRONT,NONE,NONE);
		this->mode = CHECK_BUMP;
		break;

	case CHECK_BUMP:
		// �Ռ������m���������肷��
		if (BumpDecision_checkBump(this->bumpDecision))
		{
			// �Ռ������m�����ꍇ�A��ޑ��s�ɐ؂�ւ���
			OrderList_finishOrder(this->orderList,this->orderNum);
			this->orderNum = OrderList_manualRunning(this->orderList,BACK,NONE,NONE,NONE,BACK_DISTANCE);
			this->mode = BACK_RUN;
		}
		break;

	case BACK_RUN:
		// ��ޑ��s���������������肷��
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// ��ޑ��s�����������ꍇ�A�������s�ɐ؂�ւ���
			this->orderNum = OrderList_manualRunning(this->orderList,HIGH,NONE,NONE,NONE,DASH_DISTANCE);
			this->mode = TAIL_CHANGE;
		}
		break;

	case TAIL_CHANGE:
		// �������s���������������肷��
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// �������s�����������ꍇ�A�I�����������s����
			this->orderNum = OrderList_manualRunning(this->orderList,NONE,NONE,NONE,STOP_TIME,NONE);
			this->mode = FINISHED;
		}
		break;

	case FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// ��莞�Ԓ�~�����ꍇ�Atrue��Ԃ�
			return TRUE;
		}
		break;
	}
	// false��Ԃ�
	return FALSE;
}
