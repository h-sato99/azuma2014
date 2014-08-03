/*******************************************************************************
**  ファイル名  ：GrayDecision.h
**  概要        ：灰色検知クラス定義
**  詳細        ：灰色検知の判定用処理を行う。
*******************************************************************************/

#ifndef _GrayDecision_H_
#define _GrayDecision_H_

#include "Info.h"
#include "ecrobot_interface.h"
#include "device/Timer.h"
#include "device/LightSensor.h"


// 構造体の定義
typedef struct GrayDecision
{
	int GrayPassCnt;				// 灰色検知処理を最後まで実行した回数

	LightSensor *lightSensor;		// 光センサの静的リンク
	int lightget;					// 光センサの値
	int light_target;				// 白色の基準値
	int getcount;					// 白色の基準値以下の取得回数カウンタ

	BOOL isInitialized;             // 初期化フラグ
	int forward; 					// 前進値
	int turn;						// 旋回値
	int mode;						// 走行モード
	Timer *timer;					// タイマー

} GrayDecision;


// 公開操作
void GrayDecision_init(GrayDecision* this);
void GrayDecision_setTarget(GrayDecision* this, int target);
void GrayDecision_main(GrayDecision* this, Info *info);

#endif /* _GrayDecision_H_ */

