/*******************************************************************************
**  ファイル名  ：Order.h
**  概要        ：
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _Order_H_
#define _Order_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

typedef enum OrderType
{
	ORDER_TYPE_NONE,
	ORDER_TYPE_MANUAL_RUNNING,
	ORDER_TYPE_LINETRACE_RUNNING,
	ORDER_TYPE_STOP
} OrderType;

// 属性を保持するための構造体の定義
typedef struct Order
{
	int type;
	int value1;
	int value2;
	int value3;
	int finishTime;
	int finishValue;
	BOOL isFinished;
} Order;

// 公開操作
void Order_init(Order* this);

#endif /* _Order_H_ */
