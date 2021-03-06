/*******************************************************************************
**  ファイル名  ：LineTracer.h
**  概要        ：ライントレースクラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/
#ifndef _LineTracer_H_
#define _LineTracer_H_

#include "Info.h"
#include "device/LightSensor.h"
#include "technique/PidControl.h"

typedef enum LineEge
{
	LINE_EGE_RIGHT,
	LINE_EGE_LEFT
}LineEge;

// 属性を保持するための構造体の定義
typedef struct LineTracer
{
	LightSensor *lightSensor;
	PidControl *pidControl;
	int brightness;
	int turnDeff1;
	int turnDeff2;
	int count;
	F32 turn;
	float target;
	int lineEge;
} LineTracer;


// 公開操作
void LineTracer_init(LineTracer* this);
void LineTracer_trace(LineTracer* this, Info* info);
F32 LineTracer_getTurn(LineTracer* this);
void LineTracer_setTarget(LineTracer* this, float target);
void LineTracer_setRightEdge(LineTracer* this);
void LineTracer_setLeftEdge(LineTracer* this);
int LineTracer_getEdge(LineTracer* this);
#endif /* _LineTracer_H_ */

