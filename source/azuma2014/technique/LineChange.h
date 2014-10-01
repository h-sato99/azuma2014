/*******************************************************************************
**  ファイル名  ：LineChange.h
**  概要        ：ライン切替クラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef LINECHANGE_H_
#define LINECHANGE_H_

#include "competision/OrderList.h"

// 属性を保持するための構造体の定義
typedef struct LineChange
{
	OrderList *orderList;
	int orderNum;
} LineChange;

// 公開操作
void LineChange_init(LineChange* this);
BOOL LineChange_action(LineChange* this);

#endif /* LINECHANGE_H_ */
