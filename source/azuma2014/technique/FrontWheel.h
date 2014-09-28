/*******************************************************************************
**  ファイル名  ：FrontWheel.h
**  概要        ：尻尾モータ制御クラス定義
**  詳細        ：
*******************************************************************************/

#ifndef _FrontWheel_H_
#define _FrontWheel_H_

#include "device/Motor.h"

// 属性を保持するための構造体の定義
typedef struct FrontWheel
{
	Motor *frontMotor;
	int pwm;
} FrontWheel;

// 公開操作
void FrontWheel_init(FrontWheel* this);
void FrontWheel_setAngle(FrontWheel* this, int angle);
//
int FrontWheel_getAngle(FrontWheel* this);
//

#endif /* _FrontWheel_H_ */
