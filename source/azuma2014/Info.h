/*******************************************************************************
**  ファイル名  ：Info.h
**  概要        ：情報クラス定義
**  詳細        ：
*******************************************************************************/

#ifndef _Info_H_
#define _Info_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "CourseInfo.h"
#include "SettingInfo.h"
#include "RunnerInfo.h"

// 属性を保持するための構造体の定義
typedef struct Info
{
	MeasureInfo *measureInfo;
	RunnerInfo *runnerInfo;
	SettingInfo *settingInfo;
	BOOL loggerFlag;
	BOOL autoStrategyFlag;
	S8 strategyState;
	BOOL startFlag;
} Info;

// 公開操作
// なし

#endif /* _Info_H_ */
