/*******************************************************************************
**  ファイル名  ：Command.h
**  概要        ：コマンドクラス定義
**  詳細        ：
*******************************************************************************/

#ifndef _Command_H_
#define _Command_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// 属性を保持するための構造体の定義
typedef struct Command
{
	int command;
	int value1;
	int value2;
	int value3;
	int value4;
	int value5;
	int value6;
} Command;

// 公開操作
// なし

#endif /* _Command_H_ */
