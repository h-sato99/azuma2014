/*******************************************************************************
**  ファイル名  ：OrderList.h
**  概要        ：指示リストクラス定義
**  詳細        ：走行体を動かすための指示を保持するクラス。
*******************************************************************************/

#ifndef _OrderList_H_
#define _OrderList_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "competision/Order.h"

#define ORDER_LIST_MAX 20

// 属性を保持するための構造体の定義
typedef struct OrderList
{
	int orderCount;
	int orderIndex;
	Order orderLists[20];
} OrderList;

// 公開操作
void OrderList_init(OrderList* this);
Order* OrderList_getOrder(OrderList* this, int orderIndex);
int OrderList_addOrder(OrderList* this, int type, int value1, int value2, int value3, int finishTime, int finishValue);
void OrderList_finishOrder(OrderList* this, int orderIndex);
BOOL OrderList_checkFinished(OrderList* this, int orderIndex);
int OrderList_manualRunning(OrderList* this, int forward, int turn, int turnState, int finishTime, int finishDistance);
int OrderList_lineTraceRunning(OrderList* this, int forward, int target, int turnState, int finishTime, int finishDistance);
int OrderList_stop(OrderList* this);

#endif /* _OrderList_H_ */
