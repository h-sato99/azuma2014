///*******************************************************************************
//**  ファイル名  ：LookUpGate.h
//**  概要        ：ルックアップゲートクラス定義
//**  詳細        ：クラスの公開情報を定義する。
//*******************************************************************************/
//#ifndef _LookUpGate_H_
//#define _LookUpGate_H_
//
//#include "Info.h"
//#include "device/SonarSensor.h"
//#include "device/Timer.h"
//#include "technique/Distance.h"
//
//// 属性を保持するための構造体の定義
//typedef struct LookUpGate
//{
//	BOOL isInitialized;             		// 初期化フラグ
//	int forward; 							// 前進値
//	int turn;								// 旋回値
//	int tAngle;								// 尻尾角度
//	S32 sonar;								// 超音波測定値
//	int mode;								// 走行モード
//	Timer *timer;
//	Distance *distance;
//	int initTurn;
//	SonarSensor *sonarSensor;
//	BOOL isFinished;
//} LookUpGate;
//
//
//// 公開操作
//void LookUpGate_init(LookUpGate* this);
//void LookUpGate_action(LookUpGate* this, Info *info);
//BOOL LookUpGate_checkFinish(LookUpGate* this);
//
//#endif /* _SectionBasic_H_ */
//
