/*******************************************************************************
**  ファイル名  ：CheckStart.h
**  概要        ：スタート判定クラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef CHECK_START_H_
#define CHECK_START_H_

#include "Info.h"
#include "technique/Tail.h"
#include "device/TouchSensor.h"
#include "device/Bluetooth.h"
#include "technique/Communication.h"

// 属性を保持するための構造体の定義
typedef struct CheckStart
{
	TouchSensor *touchSensor;
	Communication *communication;
	Tail *tail;
	int tailAngl;
	int started;
} CheckStart;


// 公開操作
void CheckStart_init(CheckStart* this);
void CheckStart_waitStart(CheckStart* this, Info* info);
BOOL CheckStart_isStart(CheckStart* this);

#endif
