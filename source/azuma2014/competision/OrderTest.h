/*******************************************************************************
**  ファイル名  ：OrderTest.h
**  概要        ：
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _OrderTest_H_
#define _OrderTest_H_

#include "competision/OrderList.h"
#include "competision/Runner.h"


// 属性を保持するための構造体の定義
typedef struct OrderTest{
	OrderList *orderList;
	int orderNum;				//
	int mode;
} OrderTest;

// 公開操作
void OrderTest_init(OrderTest* this);
BOOL OrderTest_tailRun(OrderTest* this);
BOOL OrderTest_figureL(OrderTest* this);
BOOL OrderTest_strateRun(OrderTest* this);

#endif /* _OrderTest_H_ */
