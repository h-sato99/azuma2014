/*******************************************************************************
**  �t�@�C����  �FTrialDecision.c
**  �T�v        �F����m�N���X
**  �ڍ�        �F
*******************************************************************************/

#include "TrialDecision.h"

#define NONE			0		// �����l
#define TARGET			500		// 臒l
#define LOW				40		// �ᑬ
#define NORMAL			80		// �ʏ�
#define HIGH			120		// ����
#define	BACK			-40		// ���
#define BACK_DISTANCE	2000		// ���s����(���)
#define DASH_DISTANCE	3000		// ���s����(����)

typedef enum State
{
	START,
	CHECK_BUMP,
	BACK_RUN,
	DASH_RUN,
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
//		this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,LOW,NONE,NONE,NONE);
//		this->orderNum = OrderList_manualRunning(this->orderList,LOW,NONE,NONE,NONE,NONE);
//		this->mode = CHECK_BUMP;
		OrderList_manualRunning(this->orderList,LOW,NONE,TURN_DRIVING,BACK_DISTANCE,NONE);
		OrderList_manualRunning(this->orderList,BACK,NONE,TURN_DRIVING,BACK_DISTANCE,NONE);
		this->orderNum = OrderList_manualRunning(this->orderList,HIGH,TURN_DRIVING,NONE,DASH_DISTANCE,NONE);
		this->mode = DASH_RUN;
		break;

	case CHECK_BUMP:
		// �Ռ������m���������肷��
//		if (BumpDecision_checkBump(this->bumpDecision))
//		{
			// �Ռ������m�����ꍇ�A��ޑ��s�ɐ؂�ւ���
			OrderList_finishOrder(this->orderList,this->orderNum);
//			this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,BACK,NONE,NONE,BACK_DISTANCE);
			this->orderNum = OrderList_manualRunning(this->orderList,BACK,NONE,NONE,BACK_DISTANCE,NONE);
			this->mode = BACK_RUN;
//		}
		break;

	case BACK_RUN:
		// ��ޑ��s���������������肷��
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// ��ޑ��s�����������ꍇ�A�������s�ɐ؂�ւ���
//			this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,HIGH,NONE,NONE,DASH_DISTANCE);
			this->orderNum = OrderList_manualRunning(this->orderList,HIGH,NONE,NONE,DASH_DISTANCE,NONE);
			this->mode = DASH_RUN;
		}
		break;

	case DASH_RUN:
		// �������s���������������肷��
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// �������s�����������ꍇ�A�I�����������s����
			this->mode = FINISHED;
		}
		break;

	case FINISHED:
		// true��Ԃ�
		return true;
	}
	// false��Ԃ�
	return false;
}

// �݌v�Ɋ�Â��������̏ꍇ
//BOOL TrialDecision_action2(TrialDecision* this)
//{
//	// �ᑬ���s�ɐ؂�ւ���
//	this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,LOW,NONE,NONE,NONE);
//
//	while(1)
//	{
//		if(BumpDecision_checkBump(this->bumpDecision))
//		{
//			break;
//		}
//	}
//
//	// ��ޑ��s�ɐ؂�ւ���
//	this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,BACK,NONE,NONE,BACK_DISTANCE);
//
//	while(1)
//	{
//		if(OrderList_checkFinished(this->orderList, this->orderNum))
//		{
//			break;
//		}
//	}
//
//	// �������s�ɐ؂�ւ���
//	this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,HIGH,NONE,NONE,DASH_DISTANCE);
//
//	while(1)
//	{
//		if(OrderList_checkFinished(this->orderList, this->orderNum))
//		{
//			break;
//		}
//	}
//
//	return true;
//}
