/*******************************************************************************
**  �t�@�C����  �FRoboControl.c
**  �T�v        �F
**  �ڍ�        �F
*******************************************************************************/
//TODO:currentOrderIndex��OrderList�ֈړ��B
//TODO:OrderList�̓��X�g�\���������ł���悤�ARoboControl�Ɩ������S�𖾊m�ɂ���B
#include "RoboControl.h"

static BOOL RoboControl_checkFinishTime(RoboControl* this, Order* order);
static BOOL RoboControl_checkFinishValue(RoboControl* this, Order* order);
static void RoboControl_startOrder(RoboControl* this);
static void RoboControl_finishOrder(RoboControl* this);

/*------------------------------------------------------------------------------
--  �֐���      �FRoboControl_init
--  �T�v        �F����������B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void RoboControl_init(RoboControl* this)
{
	this->isInitialized = FALSE;
	this->currentOrderIndex = 0;
//	this->finishTime = 0;
//	this->finishValue = 0;
	this->time = 0;
	this->value = 0;
}

void RoboControl_control(RoboControl* this)
{
	Order *order;

	order = OrderList_getOrder(this->orderList, this->currentOrderIndex);

	if(order->type == ORDER_TYPE_NONE)
	{
		return;
	}

	if(this->isInitialized == FALSE)
	{
		RoboControl_startOrder(this);
	}

	display_goto_xy(1, 1);
	display_int(this->currentOrderIndex, 14);
	display_update();


	switch(order->type)
	{
//		case ORDER_TYPE_NONE:
//			ecrobot_sound_tone(659, 70, 95);
//			RoboControl_chengeOrder(this);
//			break;
		case ORDER_TYPE_MANUAL_RUNNING:
			//ecrobot_sound_tone(659, 100, 95);
			Runner_run(this->runner, order->value1, order->value2, 0, MUNUAL, order->value3);
			break;
		case ORDER_TYPE_LINETRACE_RUNNING:
			Runner_run(this->runner, order->value1, 0, order->value2, LINETRACE, order->value3);
			break;
		case ORDER_TYPE_STOP:
			Runner_run(this->runner, 0, 0, 0, MUNUAL, TURN_INIT);
			break;
	}

	if(RoboControl_checkFinishTime(this, order) || RoboControl_checkFinishValue(this, order))
	{
		OrderList_finishOrder(this->orderList, this->currentOrderIndex);
	}
	if(OrderList_checkFinished(this->orderList, this->currentOrderIndex))
	{
		RoboControl_finishOrder(this);
	}
}

static BOOL RoboControl_checkFinishTime(RoboControl* this, Order* order)
{
	if(order->finishTime > 0)
	{
		if(order->finishTime < this->time)
		{
			return TRUE;
		}
		else
		{
			this->time += 4;
			return FALSE;
		}
	}
	return FALSE;
}

static BOOL RoboControl_checkFinishValue(RoboControl* this, Order* order)
{
	int diffValue = 0;
	int checkValue;

	checkValue = order->finishValue;
	if(checkValue < 0)
	{
		checkValue *= -1;
	}

	if(order->finishValue > 0)
	{
		switch(order->type)
		{
			case ORDER_TYPE_NONE:
				return FALSE;
			case ORDER_TYPE_MANUAL_RUNNING:
				diffValue = Runner_getDistance(this->runner) - this->value;
				break;
			case ORDER_TYPE_LINETRACE_RUNNING:
				diffValue = Runner_getDistance(this->runner) - this->value;
				break;
			case ORDER_TYPE_STOP:
				return FALSE;
		}

		if(diffValue < 0)
		{
			diffValue *= -1;
		}

		if(order->finishValue < diffValue)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	return FALSE;
}

static void RoboControl_startOrder(RoboControl* this)
{
	ecrobot_sound_tone(659, 100, 90);
	this->time = 0;
	this->value = Runner_getDistance(this->runner);
	this->isInitialized = TRUE;
}

static void RoboControl_finishOrder(RoboControl* this)
{
	//Order *order;

	this->currentOrderIndex++;

	this->isInitialized = FALSE;

	//order = OrderList_getOrder(this->orderList, this->currentOrderIndex);

	//this->time = 0;
	//this->value = 0;
	//this->value = Runner_getDistance(this->runner);
//	this->finishTime = order->finishTime;
//	this->finishValue = order->finishValue;

	/*
	display_goto_xy(2, 4);
	display_int(order->value1, 14);
	display_goto_xy(2, 5);
	display_int(order->value2, 14);
	display_update();
	*/
}
