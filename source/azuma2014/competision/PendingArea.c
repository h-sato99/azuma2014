/*******************************************************************************
**  �t�@�C����  �FPendingArea.c
**  �T�v        �F�d�l���m��G���A�U���N���X
**  �ڍ�        �F�d�l���m��G���A�U���Ɋւ��鏈�����`�B
*******************************************************************************/
#include "PendingArea.h"

#define NONE						0		// �����l
#define NORMAL						40		// �ʏ�
#define TURN_LEFT_ANGLE				100		// ������
#define TURN_RIGHT_ANGLE			-10		// �E����
#define TURN_LEFT_OBLIQUE_ANGLE		50		// ���΂ߐ���
#define TURN_RIGHT_OBLIQUE_ANGLE	-50		// �E�΂ߐ���
#define STRAIGHT_DISTANCE			30		// ���s����(���i)
#define OBLIQUE_DISTANCE			50		// ���s����(�΂�)
#define TURN_DISTANCE 				60		// ���s����(���̏����)
#define STOP_TIME 					3000	// ��~����

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
		PendingArea_privateModeInit(this);
		this->mode = PENDINGAREA_CHECK_POINT1;
		break;
	case PENDINGAREA_CHECK_POINT1:
		if(PendingArea_leftOblique(this))
		{
			ecrobot_sound_tone(800, 200, 95);
			this->mode = PENDINGAREA_CHECK_POINT1;
		}
		break;
	case PENDINGAREA_CHECK_POINT2:
		if(PendingArea_rightOblique(this))
		{
			ecrobot_sound_tone(800, 200, 95);
			this->orderNum = OrderList_manualRunning(this->orderList,NONE,NONE,NONE,STOP_TIME,NONE);
			this->mode = PENINGAREA_FINISHED;
		}
		break;
	case PENINGAREA_FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			ecrobot_sound_tone(800, 200, 95);
			return TRUE;
		}
	}
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
		// ���i����
		this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, NONE, NONE, NONE, STRAIGHT_DISTANCE);
		this->privateMode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// ���i�����������ꍇ�A�I�����������s����
			this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, TURN_INIT, STOP_TIME, NONE);
			this->privateMode = PENINGAREA_FINISHED;
		}
		break;

	case PENINGAREA_FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// true��Ԃ�
			return TRUE;
		}
		break;
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
		// �����񂷂�
		this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_LEFT_ANGLE, TURN_LEFT, NONE, TURN_DISTANCE);
		this->privateMode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// �����񂪊��������ꍇ�A���i����
			this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, NONE, NONE, NONE, STRAIGHT_DISTANCE);
			this->privateMode = PENDINGAREA_CHECK_POINT2;
		}
		break;

	case PENDINGAREA_CHECK_POINT2:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// ���i�����������ꍇ�A�E���񂷂�
			this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_RIGHT_ANGLE, TURN_RIGHT, NONE, TURN_DISTANCE);
			this->privateMode = PENINGAREA_FINISHED;
		}
		break;

	case PENDINGAREA_CHECK_POINT3:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// �E���񂪊��������ꍇ�A�I�����������s����
			this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, TURN_INIT, STOP_TIME, NONE);
			this->privateMode = PENINGAREA_FINISHED;
		}
		break;

	case PENINGAREA_FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// true��Ԃ�
			return TRUE;
		}
		break;
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
		// �E���񂷂�
		this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_RIGHT_ANGLE, TURN_RIGHT, NONE, TURN_DISTANCE);
		this->privateMode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// �E���񂪊��������ꍇ�A���i����
			this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, NONE, NONE, NONE, STRAIGHT_DISTANCE);
			this->privateMode = PENDINGAREA_CHECK_POINT2;
		}
		break;

	case PENDINGAREA_CHECK_POINT2:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// ���i�����������ꍇ�A�����񂷂�
			this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_LEFT_ANGLE, TURN_LEFT, NONE, TURN_DISTANCE);
			this->privateMode = PENINGAREA_FINISHED;
		}
		break;

	case PENDINGAREA_CHECK_POINT3:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// �����񂪊��������ꍇ�A�I�����������s����
			this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, TURN_INIT, STOP_TIME, NONE);
			this->privateMode = PENINGAREA_FINISHED;
		}
		break;

	case PENINGAREA_FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// true��Ԃ�
			return TRUE;
		}
		break;
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
		// ���΂߂ɐ��񂵂O�i����
		this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_LEFT_OBLIQUE_ANGLE, TURN_FRONT, NONE, STRAIGHT_DISTANCE);
		this->privateMode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// ���΂ߐ��񂪊��������ꍇ�A�E�΂߂ɐ��񂵂��i����
			this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_RIGHT_OBLIQUE_ANGLE, TURN_FRONT, NONE, STRAIGHT_DISTANCE);
			this->privateMode = PENDINGAREA_CHECK_POINT2;
		}
		break;

	case PENDINGAREA_CHECK_POINT2:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// �E�΂ߐ��񂪊��������ꍇ�A�I�����������s����
			this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, TURN_INIT, STOP_TIME, NONE);
			this->privateMode = PENINGAREA_FINISHED;
		}
		break;

	case PENINGAREA_FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// true��Ԃ�
			return TRUE;
		}
		break;
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
		// �E�΂߂ɐ��񂵂O�i����
		this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_RIGHT_OBLIQUE_ANGLE, TURN_FRONT, NONE, STRAIGHT_DISTANCE);
		this->privateMode = PENDINGAREA_CHECK_POINT1;
		break;

	case PENDINGAREA_CHECK_POINT1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// �E�΂ߐ��񂪊��������ꍇ�A���΂߂ɐ��񂵂��i����
			this->orderNum = OrderList_manualRunning(this->orderList, NORMAL, TURN_LEFT_OBLIQUE_ANGLE, TURN_FRONT, NONE, STRAIGHT_DISTANCE);
			this->privateMode = PENDINGAREA_CHECK_POINT2;
		}
		break;

	case PENDINGAREA_CHECK_POINT2:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// ���΂ߐ��񂪊��������ꍇ�A�I�����������s����
			this->orderNum = OrderList_manualRunning(this->orderList, NONE, NONE, TURN_INIT, STOP_TIME, NONE);
			this->privateMode = PENINGAREA_FINISHED;
		}
		break;

	case PENINGAREA_FINISHED:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// true��Ԃ�
			return TRUE;
		}
		break;
	}
	// false��Ԃ�
	return FALSE;
}
