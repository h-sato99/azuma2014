/*******************************************************************************
**  ファイル名  ：Distance.h
**  概要        ：距離測定クラス
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _Distance_H_
#define _Distance_H_

#include "CourseInfo.h"

// 属性を保持するための構造体の定義
typedef struct Distance
{
	int initDistance;
} Distance;

// 公開操作
void Distance_init(Distance* this);
void Distance_set(Distance* this, MeasureInfo* measureInfo);
BOOL Distance_check(Distance* this, MeasureInfo* measureInfo, int distance);

#endif /* _Distance_H_ */
