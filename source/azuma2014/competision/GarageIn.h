/*******************************************************************************
**  ファイル名  ：GarageIn.h
**  概要        ：ガレージインクラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _GarageIn_H_
#define _GarageIn_H_

#include "Info.h"
#include "technique/Distance.h"

// 属性を保持するための構造体の定義
typedef struct GarageIn
{
	BOOL isInitialized;             		// 初期化フラグ
	int forward; 							// 前進値
	int turn;								// 旋回値
	int tAngle;								// 尻尾角度
	Distance *distance;
} GarageIn;

// 公開操作
void GarageIn_init(GarageIn* this);
void GarageIn_action(GarageIn* this, Info* info);

#endif /* _GarageIn_H_ */
