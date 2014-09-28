/*******************************************************************************
**  ファイル名  ：OrderList.c
**  概要        ：
**  詳細        ：
*******************************************************************************/
//TODO:指示が0件時の挙動がおかしい。正しく状態遷移できてない？

#include "OrderList.h"


/*------------------------------------------------------------------------------
--  関数名      ：OrderList_init
--  概要        ：初期化する。
--              ：
--  引数        ：なし
--  戻り値      ：なし
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

int OrderList_manualRunning(OrderList* this, int forward, int turn, int turnState, int finishTime, int finishDistance)
{
	return OrderList_addOrder(this, ORDER_TYPE_MANUAL_RUNNING, forward, turn, turnState, finishTime, finishDistance);
}

int OrderList_lineTraceRunning(OrderList* this, int forward, int target, int turnState, int finishTime, int finishDistance)
{
	return OrderList_addOrder(this, ORDER_TYPE_LINETRACE_RUNNING, forward, target, turnState, finishTime, finishDistance);
}

int OrderList_stop(OrderList* this){
	return OrderList_addOrder(this, ORDER_TYPE_STOP, 0, 0, 0, 0, 0);
}

int OrderList_setPID(OrderList* this, int p, int i, int d)
{
	return OrderList_addOrder(this, ORDER_TYPE_SET_PID, p, i, d, 0, 0);
}
