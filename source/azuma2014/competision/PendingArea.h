/*******************************************************************************
**  ファイル名  ：PendingArea.h
**  概要        ：
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef PENDINGAREA_H_
#define PENDINGAREA_H_

#include "competision/OrderList.h"

// 属性を保持するための構造体の定義
typedef struct PendingArea{
	OrderList *orderList;
	int orderNum;
	int mode;
	int privateMode;
} PendingArea;

typedef enum PendingAreaState
{
	PENDINGAREA_START,
	PENDINGAREA_CHECK_POINT1,
	PENDINGAREA_CHECK_POINT2,
	PENDINGAREA_CHECK_POINT3,
	PENDINGAREA_CHECK_POINT4,
	PENDINGAREA_CHECK_POINT5,
	PENINGAREA_FINISHED
} PendingAreaState;

// 公開操作
void PendingArea_init(PendingArea* this);
BOOL PendingArea_main(PendingArea* this);


#endif /* PENDINGAREA_H_ */
