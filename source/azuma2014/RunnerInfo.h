/*******************************************************************************
**  ファイル名  ：RunnerInfo.h
**  概要        ：走行情報クラス定義
**  詳細        ：
*******************************************************************************/

#ifndef _RunnerInfo_H_
#define _RunnerInfo_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// 属性を保持するための構造体の定義
typedef struct RunnerInfo
{
	F32 forward;
	F32 turn;
	BOOL balanceFlag;
	UINT gyroOffset;
	int tail;
	BOOL chengeLineEdgeFlag;
	BOOL dashFlag;
	int dashvol;
	int dashlim;
	BOOL emergencyStopCheckFlag;
	BOOL emergencyStopFlag;
} RunnerInfo;

// 公開操作
// なし

#endif /* _RunnerInfo_H_ */
