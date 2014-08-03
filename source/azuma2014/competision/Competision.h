/*******************************************************************************
**  ファイル名  ：Competision.h
**  概要        ：競技クラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _Competision_H_
#define _Competision_H_

#include "Info.h"
#include "LineTracer.h"
#include "Strategy.h"
#include "Runner.h"

// 属性を保持するための構造体の定義
typedef struct Competision
{
	LineTracer *lineTracer;
	Strategy *strategy;
	Runner *runner;
} Competision;

// 公開操作
void Competision_init(Competision* this);
void Competision_action(Competision* this, Info* info);

#endif /* _Competision_H_ */
