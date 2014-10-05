/*******************************************************************************
**  ファイル名  ：RoboControl.c
**  概要        ：
**  詳細        ：
*******************************************************************************/

#include "RoboControl.h"

static BOOL RoboControl_checkFinishTime(RoboControl* this, Order* order);
static BOOL RoboControl_checkFinishValue(RoboControl* this, Order* order);
static void RoboControl_startOrder(RoboControl* this);
static void RoboControl_finishOrder(RoboControl* this);
static void RoboControl_setPID(RoboControl* this, Order* order, Info* info);

/*------------------------------------------------------------------------------
--  関数名      ：RoboControl_init
--  概要        ：初期化する。
--              ：
--  引数        ：なし
--  戻り値      ：なし
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

/*------------------------------------------------------------------------------
--  関数名      ：RoboControl_control
--  概要        ：指示リストに従い、指示を実行する。
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void RoboControl_control(RoboControl* this, Info* info)
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


	/*
	display_goto_xy(1, 1);
	display_int(this->currentOrderIndex, 14);
	display_update();
	*/


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
		case ORDER_TYPE_SET_PID:
			RoboControl_setPID(this, order, info);
			OrderList_finishOrder(this->orderList, this->currentOrderIndex);
			break;
		case ORDER_TYPE_TURN_SPOT_LEFT:
			Runner_run(this->runner, order->value1, order->value2, 0, MUNUAL, TURN_LEFT);
			break;
		case ORDER_TYPE_TURN_SPOT_RIGHT:
			Runner_run(this->runner, order->value1, order->value2, 0, MUNUAL, TURN_RIGHT);
			break;
	}

	// 指示で定義されている終了条件の確認
	if(RoboControl_checkFinishTime(this, order) || RoboControl_checkFinishValue(this, order))
	{
		OrderList_finishOrder(this->orderList, this->currentOrderIndex);
	}
	// 指示が終了したか確認
	if(OrderList_checkFinished(this->orderList, this->currentOrderIndex))
	{
		// 指示を終了する
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
			case ORDER_TYPE_TURN_SPOT_LEFT:
				diffValue = Runner_getDistance(this->runner) - this->value;
				break;
			case ORDER_TYPE_TURN_SPOT_RIGHT:
				diffValue = Runner_getDistance(this->runner) - this->value;
				break;
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
	//ecrobot_sound_tone(659, 100, 90);
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

static void RoboControl_setPID(RoboControl* this, Order* order, Info* info)
{
	info->settingInfo->pidP = (F32)order->value1 / 100;
	info->settingInfo->pidI = (F32)order->value2 / 100;
	info->settingInfo->pidD = (F32)order->value3 / 100;
}
