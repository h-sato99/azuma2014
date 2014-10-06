/*******************************************************************************
**  �t�@�C����  �FOrderList.c
**  �T�v        �F
**  �ڍ�        �F
*******************************************************************************/
//TODO:�w����0�����̋��������������B��������ԑJ�ڂł��ĂȂ��H

#include "OrderList.h"


/*------------------------------------------------------------------------------
--  �֐���      �FOrderList_init
--  �T�v        �F����������B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void OrderList_init(OrderList* this)
{
	this->orderCount = 0;
	this->orderIndex = 0;
//	ecrobot_sound_tone(800, 200, 95);
	/*
	display_goto_xy(3, 1);
	display_int(this->orderIndex, 14);
	display_update();
	*/

	// �w�����X�g������������
	for(int i=0; i<ORDER_LIST_MAX; i++)
	{
		Order_init(&(this->orderLists[i]));
	}
}

Order* OrderList_getOrder(OrderList* this, int orderIndex)
{
	return &(this->orderLists[orderIndex]);
}

int OrderList_addOrder(OrderList* this, int type, int value1, int value2, int value3, int finishTime, int finishValue)
{
	int orderIndex;

	orderIndex = this->orderIndex;
	/*
	display_goto_xy(1, 5);
	display_int(orderIndex, 14);
	display_update();
	*/

	this->orderLists[this->orderIndex].type = type;
	this->orderLists[this->orderIndex].value1 = value1;
	this->orderLists[this->orderIndex].value2 = value2;
	this->orderLists[this->orderIndex].value3 = value3;
	this->orderLists[this->orderIndex].finishTime = finishTime;
	this->orderLists[this->orderIndex].finishValue = finishValue;
	this->orderLists[this->orderIndex].isFinished = FALSE;

	this->orderCount++;
	this->orderIndex++;
	this->orderIndex = this->orderIndex % ORDER_LIST_MAX;

	return orderIndex;
}

/*------------------------------------------------------------------------------
--  �֐���      �FOrderList_finishOrder
--  �T�v        �F�w�����I��������B
--              �F
--  ����        �ForderIndex  �w���ԍ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void OrderList_finishOrder(OrderList* this, int orderIndex)
{
	/*
	display_goto_xy(1, 2);
	display_int(orderIndex, 14);
	display_update();
	*/
	if(this->orderLists[orderIndex].type != ORDER_TYPE_NONE)
	{
		//ecrobot_sound_tone(800, 200, 95);
		this->orderLists[orderIndex].isFinished = TRUE;
		this->orderCount--;
	}
}

/*------------------------------------------------------------------------------
--  �֐���      �FOrderList_checkFinished
--  �T�v        �F�w�����I�����Ă��邩�m�F����B
--              �F
--  ����        �ForderIndex  �w���ԍ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
BOOL OrderList_checkFinished(OrderList* this, int orderIndex)
{
	if(this->orderLists[orderIndex].type == ORDER_TYPE_NONE)
	{
		return TRUE;
	}
	else
	{
		return this->orderLists[orderIndex].isFinished;
	}
}

/*------------------------------------------------------------------------------
--  �֐���      �FOrderList_manualRunning
--  �T�v        �F�}�j���A�����s���w������B
--              �F
--  ����        �Fforward         �O�i��
--              �Fturn            �����
--              �FturnState       ������
--              �F                  TURN_FRONT   : �O�ւŐ���
--              �F                  TURN_DRIVING : �쓮�ւŐ���
--              �FfinishTime      �I������
--              �FfinishDistance  �I������
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
int OrderList_manualRunning(OrderList* this, int forward, int turn, int turnState, int finishTime, int finishDistance)
{
	return OrderList_addOrder(this, ORDER_TYPE_MANUAL_RUNNING, forward, turn, turnState, finishTime, finishDistance);
}

/*------------------------------------------------------------------------------
--  �֐���      �FOrderList_manualRunning
--  �T�v        �F���C���g���[�X���s���w������B
--              �F
--  ����        �Fforward         �O�i��
--              �Ftarget          �ڕW�l(���Z���T臒l)
--              �FturnState       ������
--              �F                  TURN_FRONT   : �O�ւŐ���
--              �F                  TURN_DRIVING : �쓮�ւŐ���
--              �FfinishTime      �I������
--              �FfinishDistance  �I������
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
int OrderList_lineTraceRunning(OrderList* this, int forward, int target, int turnState, int finishTime, int finishDistance)
{
	return OrderList_addOrder(this, ORDER_TYPE_LINETRACE_RUNNING, forward, target, turnState, finishTime, finishDistance);
}

/*------------------------------------------------------------------------------
--  �֐���      �FOrderList_stop
--  �T�v        �F��~���w������B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
int OrderList_stop(OrderList* this){
	return OrderList_addOrder(this, ORDER_TYPE_STOP, 0, 0, 0, 0, 0);
}

/*------------------------------------------------------------------------------
--  �֐���      �FOrderList_setPID
--  �T�v        �FPID����̒萔�ύX���w������B
--              �F
--  ����        �Fp       P����̒萔
--              �Fi       I����̒萔
--              �Fd       D����̒萔
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
int OrderList_setPID(OrderList* this, int p, int i, int d)
{
	return OrderList_addOrder(this, ORDER_TYPE_SET_PID, p, i, d, 0, 0);
}

/*------------------------------------------------------------------------------
--  �֐���      �FOrderList_turnOnSpotLeft
--  �T�v        �F���͈͍�������w������B
--              �F
--  ����        �Fforward         �O�i��
--              �Fturn            �����
--              �FfinishTime      �I������
--              �FfinishDistance  �I������
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
int OrderList_turnOnSpotLeft(OrderList* this, int forward, int turn, int finishTime, int finishDistance)
{
	return OrderList_addOrder(this, ORDER_TYPE_TURN_SPOT_LEFT, forward, turn, TURN_LEFT, finishTime, finishDistance);
}

/*------------------------------------------------------------------------------
--  �֐���      �FOrderList_turnOnSpotRight
--  �T�v        �F���͈͉E������w������B
--              �F
--  ����        �Fforward         �O�i��
--              �Fturn            �����
--              �FfinishTime      �I������
--              �FfinishDistance  �I������
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
int OrderList_turnOnSpotRight(OrderList* this, int forward, int turn, int finishTime, int finishDistance)
{
	return OrderList_addOrder(this, ORDER_TYPE_TURN_SPOT_RIGHT, forward, turn, TURN_RIGHT, finishTime, finishDistance);
}
