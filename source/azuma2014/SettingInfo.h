/*******************************************************************************
**  ファイル名  ：SettingInfo.h
**  概要        ：設定情報クラス定義
**  詳細        ：
*******************************************************************************/

#ifndef _SettingInfo_H_
#define _SettingInfo_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// 属性を保持するための構造体の定義
typedef struct SettingInfo
{
	// コースタイプ
	// 0:アウトコース
	// 1:インコース
	int courseType;
	F32 pidP;
	F32 pidI;
	F32 pidD;
	float target;
	float targetwait;
	float targetbas;
	BOOL lineTraceFlg;
} SettingInfo;

// 公開操作
void SettingInfo_init(SettingInfo* this);

#endif /* _SettingInfo_H_ */
