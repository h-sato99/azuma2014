/*******************************************************************************
**  ファイル名  ：Seesaw.h
**  概要        ：シーソークラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _Seesaw_H_
#define _Seesaw_H_

#include "Info.h"
#include "device/GyroSensor.h"
#include "technique/WheelAverage.h"
// 属性を保持するための構造体の定義
typedef struct Seesaw
{
	//クラス用変数
	GyroSensor *gyroSensor;		//ジャイロセンサークラス
	WheelAverage *wheelAverage; //WheelAverageクラス

	//衝撃検知用変数
	unsigned int ImpactLow;		//衝撃判定下限値
	unsigned int ImpactHight;	//衝撃判定上限値
	int forward;		//前進値
	unsigned int RecieveGyro;	//ジャイロセンサーの値を受け取る用

	//車輪の値取得用変数
	int Average;				//両車輪の取得用
	int StrageAverage;			//保持用両車輪の平均
	int NewAverage;				//最新の平均保持用

	//その他変数
	int SeesawCount;			//状態のカウント
	int WaitCount;				//Wait用カウント
	int TailAngle;				//尻尾の角度
	int LengthTarget;			//距離の目標値
	int TailMode;				//0：Up,2：Down
	int TailTarget;				//尻尾の目標値
	int InfoTail;
	BOOL isFinished;
} Seesaw;

// 公開操作
void Seesaw_init(Seesaw* this);					//初期処理
void Seesaw_action(Seesaw* this, Info *info);	//シーソー攻略
BOOL Seesaw_checkFinish(Seesaw* this);

#endif /* _Seesaw_H_ */
