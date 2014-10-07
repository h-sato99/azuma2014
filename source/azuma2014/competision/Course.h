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
BOOL Course_IN_StartToCurve(Course* this);
BOOL Course_IN_CurveToLineChange(Course* this);
BOOL Course_IN_LineChangeToReStart(Course* this);
BOOL Course_IN_CurveToMogul(Course* this);
BOOL Course_IN_MogulToManual(Course* this);
BOOL Course_IN_ManualToFigureL(Course* this);
BOOL Course_IN_FigureLToStop(Course* this);
BOOL Course_OUT_StartToCurve(Course* this);
BOOL Course_OUT_CurveToJump(Course* this);
BOOL Course_OUT_JumpToDashStart(Course* this);
BOOL Course_OUT_DashStartToDashEnd(Course* this);
BOOL Course_OUT_DashEndToPending(Course* this);
BOOL Course_OUT_PendingToCurve(Course* this);
BOOL Course_OUT_CurveToGoal(Course* this);

#endif /* _Course_H_ */
