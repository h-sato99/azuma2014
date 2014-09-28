/*******************************************************************************
**  ファイル名  ：Course.h
**  概要        ：
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _Course_H_
#define _Course_H_

#include "competision/OrderList.h"
#include "competision/Runner.h"


// 属性を保持するための構造体の定義
typedef struct Course{
	OrderList *orderList;
	int orderNum;
	int mode;
	int target;
} Course;

// 公開操作
void Course_init(Course* this);
void Course_resetMode(Course* this);
BOOL Course_strateRunIN(Course* this);
BOOL Course_strateRunOUT(Course* this);
BOOL Course_stableRunOUT(Course* this);
BOOL Course_stableRunIN(Course* this);
BOOL Course_figureL(Course* this);

#endif /* _Course_H_ */
