/*******************************************************************************
**  ファイル名  ：FigureL.h
**  概要        ：
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _FigureL_H_
#define _FigureL_H_

#include "competision/OrderList.h"

// 属性を保持するための構造体の定義
typedef struct FigureL{
	OrderList *orderList;
	int orderNum;
	int mode;
} FigureL;

// 公開操作
void FigureL_init(FigureL* this);
BOOL FigureL_action(FigureL* this);

#endif /* _FigureL_H_ */
