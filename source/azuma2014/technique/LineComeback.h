/*******************************************************************************
**  ファイル名  ：LineComeback.h
**  概要        ：
**  詳細        ：クラスの公開情報を定義する。
*******************************************************************************/

#ifndef _LineComeback_H_
#define _LineComeback_H_

#include "competision/OrderList.h"
#include "technique/ColorJudgement.h"
#include "device/LCD.h"

// 属性を保持するための構造体の定義
typedef struct LineComeback{
	ColorJudgement *colorJudgement;
	OrderList *orderList;
	int mode;					// 走行モード
	int orderNum;				// オーダー番号
	LCD *lcd;
} LineComeback;

// 走行モード定義
typedef enum active{
	STOP,
	TURNLEFT,
	TURNRIGHT,
	LAST
} Active;

// 走行モード定義
typedef enum direction{
	LEFT,
	RIGHT
} Direction;

// 公開操作
void LineComeback_init(LineComeback* this);
BOOL LineComeback_main(LineComeback* this,Direction turnDirection);

#endif /* _LineComeback_H_ */
