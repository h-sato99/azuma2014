/*******************************************************************************
**  ファイル名  ：RoboControl.h
**  概要        ：
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _RoboControl_H_
#define _RoboControl_H_

//#include "kernel.h"
//#include "kernel_id.h"
//#include "ecrobot_interface.h"
#include "competision/OrderList.h"
#include "competision/Runner.h"

#include "Info.h"

// 属性を保持するための構造体の定義
typedef struct RoboControl
{
	BOOL isInitialized;
	int currentOrderIndex;
//	int finishTime;
//	int finishValue;
	int time;
	int value;
	OrderList *orderList;
	Runner *runner;
} RoboControl;

// 公開操作
void RoboControl_init(RoboControl* this);
void RoboControl_control(RoboControl* this, Info* info);

#endif /* _RoboControl_H_ */
