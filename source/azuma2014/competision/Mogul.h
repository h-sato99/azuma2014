/*******************************************************************************
**  ファイル名  ：Mogul.h
**  概要        ：
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _Mogul_H_
#define _Mogul_H_

#include "competision/OrderList.h"

// 属性を保持するための構造体の定義
typedef struct Mogul{
	OrderList *orderList;
	int orderNum;				//
} Mogul;

// 公開操作
void Mogul_init(Mogul* this);
BOOL Mogul_main(Mogul* this);

#endif /* _Mogul_H_ */
