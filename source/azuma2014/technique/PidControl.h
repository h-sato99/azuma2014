/*******************************************************************************
**  ファイル名  ：PidControl.h
**  概要        ：PID制御クラス定義
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _PidControl_H_
#define _PidControl_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "Info.h"



// 属性を保持するための構造体の定義
typedef struct PidControl
{
	float deff1;
	float deff2;
	float integral;
	float f_p;
	float f_i;
	float f_d;
} PidControl;


void PidControl_init(PidControl* this);
F32 PidControl_calcTurn(PidControl* this, SettingInfo* settingInfo, int brightness);
BOOL PidControl_checDerailment(PidControl* this);

#endif /* _PidControl_H_ */

