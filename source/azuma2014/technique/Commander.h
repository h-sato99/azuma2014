/*******************************************************************************
**  ファイル名  ：Commander.h
**  概要        ：コマンド実行クラス定義
**  詳細        ：
*******************************************************************************/

#ifndef _Commander_H_
#define _Commander_H_

#include "Command.h"
#include "Info.h"
#include "technique/Communication.h"

// 属性を保持するための構造体の定義
typedef struct Commander
{
	Command *command;
	Communication *communication;
} Commander;

// 公開操作
void Commander_init(Commander* this);
void Commander_action(Commander* this, Info *info);

#endif /* _Commander_H_ */
