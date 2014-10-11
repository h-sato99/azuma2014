/*******************************************************************************
**  ファイル名  ：ColorJudgement.h
**  概要        ：
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _ColorJudgement_H_
#define _ColorJudgement_H_


#include "device/LightSensor.h"


// 属性を保持するための構造体の定義
typedef struct ColorJudgement{
	unsigned int threshold;
	LightSensor *lightSensor;
} ColorJudgement;

typedef enum Color{
	BLACK,
	NON_BLACK,
} COLOR;

// 公開操作
void ColorJudgement_init(ColorJudgement* this);
COLOR ColorJudgement_judgeColor(ColorJudgement* this);

#endif /* _ColorJudgement_H_ */

