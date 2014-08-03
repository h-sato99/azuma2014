/*******************************************************************************
**  ファイル名  ：Tail.h
**  概要        ：尻尾モータ制御クラス定義
**  詳細        ：
*******************************************************************************/

#ifndef _Tail_H_
#define _Tail_H_

#include "device/Motor.h"

// 属性を保持するための構造体の定義
typedef struct Tail
{
	Motor *tailMotor;
} Tail;

// 公開操作
void Tail_init(Tail* this);
void Tail_setAngle(Tail* this, int angle);
//
int Tail_getAngle(Tail* this);
//

#endif /* _Tail_H_ */
