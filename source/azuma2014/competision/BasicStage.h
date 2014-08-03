/*******************************************************************************
**  ファイル名  ：BasicStage.h
**  概要        ：ベーシックステージクラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _BasicStage_H_
#define _BasicStage_H_

#include "Info.h"
#include "RunnerInfo.h"
#include "SettingInfo.h"
#include "technique/Distance.h"


// 属性を保持するための構造体の定義
typedef struct BasicStage
{
	int mode;					// スイッチ用カウンタ
	Distance *distance;			// 距離部品用
} BasicStage;

// 公開操作
void BasicStage_init(BasicStage* this);
void BasicStage_action(BasicStage* this, Info *info);

#endif /* _BasicStage_H_ */
