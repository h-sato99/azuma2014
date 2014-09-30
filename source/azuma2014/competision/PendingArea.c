/*******************************************************************************
**  �t�@�C����  �FPendingArea.c
**  �T�v        �F�d�l���m��G���A�U���N���X
**  �ڍ�        �F�d�l���m��G���A�U���Ɋւ��鏈�����`�B
*******************************************************************************/
#include "PendingArea.h"

#define NONE				0		// �����l
#define NORMAL				40		// �ʏ�
#define TURN_LEFT			90		// ������
#define TURN_RIGHT			-90		// �E����
#define STRAIGHT_DISTANCE	3000	// ���s����(���i)
#define OBLIQUE_DISTANCE	5000	// ���s����(�΂�)

/*------------------------------------------------------------------------------
--  �֐���      �FPendingArea_init
--  �T�v        �F������
--              �F
--  ����        �F
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void PendingArea_init(PendingArea* this)
{
	this->orderNum = NONE;
	this->mode = PENDINGAREA_START;
	this->privateMode = PENDINGAREA_START;
}

/*------------------------------------------------------------------------------
--  �֐���      �FPendingArea_action
--  �T�v        �F�d�l���m��G���A�U��
--              �F
--  ����        �F
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
BOOL PendingArea_action(PendingArea* this)
{
	switch(this->mode)
	{
	case PENDINGAREA_START:
		this->mode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		this->mode = PENINGAREA_FINISHED;
		break;

	case PENINGAREA_FINISHED:
		// true��Ԃ�
		return TRUE;
	}
	// false��Ԃ�
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FPendingArea_privateModeInit
--  �T�v        �F�v���C�x�[�g���[�h������
--              �F
--  ����        �F
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void PendingArea_privateModeInit(PendingArea* this)
{
	this->privateMode = PENDINGAREA_START;
}

/*------------------------------------------------------------------------------
--  �֐���      �FPendingArea_straight
--  �T�v        �F���i
--              �F
--  ����        �F
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
BOOL PendingArea_straight(PendingArea* this)
{
	switch(this->privateMode)
	{
	case PENDINGAREA_START:
		this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, NONE, NONE, NONE, STRAIGHT_DISTANCE);
		this->mode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			this->mode = PENINGAREA_FINISHED;
		}
		break;

	case PENINGAREA_FINISHED:
		// true��Ԃ�
		return TRUE;
	}
	// false��Ԃ�
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FPendingArea_left
--  �T�v        �F�������ɒ��i
--              �F
--  ����        �F
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
BOOL PendingArea_left(PendingArea* this)
{
	switch(this->privateMode)
	{
	case PENDINGAREA_START:
//		this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, NONE, NONE, STRAIGHT_DISTANCE);
		this->mode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		this->mode = PENINGAREA_FINISHED;
		break;

	case PENINGAREA_FINISHED:
		// true��Ԃ�
		return TRUE;
	}
	// false��Ԃ�
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FPendingArea_right
--  �T�v        �F�E�����ɒ��i
--              �F
--  ����        �F
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
BOOL PendingArea_right(PendingArea* this)
{
	switch(this->privateMode)
	{
	case PENDINGAREA_START:
//		this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, NONE, NONE, STRAIGHT_DISTANCE);
		this->mode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		this->mode = PENINGAREA_FINISHED;
		break;

	case PENINGAREA_FINISHED:
		// true��Ԃ�
		return TRUE;
	}
	// false��Ԃ�
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FPendingArea_leftOblique
--  �T�v        �F���΂ߕ����ɒ��i
--              �F
--  ����        �F
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
BOOL PendingArea_leftOblique(PendingArea* this)
{
	switch(this->privateMode)
	{
	case PENDINGAREA_START:
//		this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, NONE, NONE, STRAIGHT_DISTANCE);
		this->mode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		this->mode = PENINGAREA_FINISHED;
		break;

	case PENINGAREA_FINISHED:
		// true��Ԃ�
		return TRUE;
	}
	// false��Ԃ�
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FPendingArea_rightOblique
--  �T�v        �F�E�΂ߕ����ɒ��i
--              �F
--  ����        �F
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
BOOL PendingArea_rightOblique(PendingArea* this)
{
	switch(this->privateMode)
	{
	case PENDINGAREA_START:
//		this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, NONE, NONE, STRAIGHT_DISTANCE);
		this->mode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		this->mode = PENINGAREA_FINISHED;
		break;

	case PENINGAREA_FINISHED:
		// true��Ԃ�
		return TRUE;
	}
	// false��Ԃ�
	return FALSE;
}
