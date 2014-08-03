/*******************************************************************************
**  ファイル名  ：Logger.h
**  概要        ：ログ出力クラス（ヘッダファイル）
**  詳細        ：ロギングデータをマスターデバイスに転送するための処理を定義。
**              ：NXT GamePadのデータロギング機能を使用することができる。
**              ：NXT GamePadではロギングしたデータを任意のCSVファイルとして保存
**              ：することができる。
*******************************************************************************/

#ifndef _Logger_H_
#define _Logger_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

typedef struct Logger
{
	S8 data1;
	S8 data2;
} Logger;


void Logger_dataSet(Logger* this, S8 data1, S8 data2);
void Logger_send(Logger* this);


#endif /* _Logger_H_ */
