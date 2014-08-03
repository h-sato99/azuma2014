/*******************************************************************************
**  ファイル名  ：Dash.h
**  概要        ：
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _Dash_H_
#define _Dash_H_

#include "Info.h"

// 属性を保持するための構造体の定義
typedef struct Dash
{
	int counter; 							// 汎用カウンタ
} Dash;

// 公開操作
void Dash_init(Dash* this);
void Dash_action(Dash* this,Info *info , int upvol, int uplim);

#endif /* _Dash_H_ */
