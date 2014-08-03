/*******************************************************************************
**  ファイル名  ：CourseInfo.h
**  概要        ：コース情報クラス定義
**  詳細        ：
*******************************************************************************/

#ifndef _CourseInfo_H_
#define _CourseInfo_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// 属性を保持するための構造体の定義
typedef struct MeasureInfo
{
	int countGrayMarker;
	int leftMotorAngle;
	int rightMotorAngle;
	int tailAngle;
	BOOL derailmentFlag;
} MeasureInfo;

// 公開操作
// なし

#endif /* _CourseInfo_H_ */
