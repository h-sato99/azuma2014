/*******************************************************************************
**  ファイル名  ：Jump.h
**  概要        ：ジャンプ台クラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef JUMP_H_
#define JUMP_H_

#include "competision/OrderList.h"

// 属性を保持するための構造体の定義
typedef struct Jump
{
	OrderList *orderList;
	int mode;
	int orderNum;
} Jump;

typedef enum State
{
	START,
	CHECK_HOLE,
	DASH_RUN,
	FINISHED
} State;

// 公開操作
void Jump_init(Jump* this);
BOOL Jump_action(Jump* this);

#endif /* JUMP_H_ */
