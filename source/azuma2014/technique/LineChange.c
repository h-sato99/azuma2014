/*******************************************************************************
**  �t�@�C����  �FLineChange.c
**  �T�v        �F���C���ؑփN���X
**  �ڍ�        �F
*******************************************************************************/

#include "LineChange.h"

#define NONE			0		// �����l
#define NORMAL			50		// �ʏ�
#define TURN			30		// ����l
#define DISTANCE		100	// ���s����

void LineChange_init(LineChange* this)
{
	this->orderNum = NONE;
	this->mode = 0;
}

/*------------------------------------------------------------------------------
--  �֐���      �FLineChange_action
--  �T�v        �F���C���ؑ֏��������s����
--              �F
--  ����        �F
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
BOOL LineChange_action(LineChange* this)
{
	int edge;
	int turn;
	//ecrobot_sound_tone(659, 70, 95);
	edge = LineTracer_getEdge(this->lineTracer);
	switch(this->mode)
	{
	case 0:
		// ���C���̋t���֑��s����
		ecrobot_sound_tone(659, 70, 95);
		//edge = LineTracer_getEdge(this->lineTracer);
		if(edge == LINE_EGE_LEFT)
		{
			turn = TURN;
		}
		else
		{
			turn = TURN * -1;
		}
		OrderList_manualRunning(this->orderList,NORMAL,turn,TURN_FRONT,NONE,DISTANCE);
		this->mode = 1;
		break;
	case 1:
		// �G�b�W��ؑւ���
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			if(edge == LINE_EGE_LEFT)
			{
				LineTracer_setRightEdge(this->lineTracer);
			}
			else
			{
				LineTracer_setLeftEdge(this->lineTracer);
			}
			return TRUE;
		}
		break;
	}
	/*
	// ���C���̋t���֑��s����
	this->orderNum = OrderList_manualRunning(this->orderList,NORMAL,TURN,TURN_FRONT,NONE,DISTANCE);

	if(OrderList_checkFinished(this->orderList,this->orderNum))
	{
		// ���C���̋t���֑��s�����������ꍇ�A�G�b�W�ؑ֏������s���Atrue��Ԃ�
		// TODO �G�b�W�ؑ֏������K�v
		return TRUE;
	}
	*/

	// false��Ԃ�
	return FALSE;
}
