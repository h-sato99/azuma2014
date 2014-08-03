/*******************************************************************************
**  ファイル名  ：Logger.c
**  概要        ：ログ出力クラス
**  詳細        ：ロギングデータをマスターデバイスに転送するための処理を行う。
**              ：NXT GamePadのデータロギング機能を使用することができる。
**              ：NXT GamePadではロギングしたデータを任意のCSVファイルとして保存
**              ：することができる。
*******************************************************************************/

#include "Logger.h"


void Logger_dataSet(Logger* this, S8 data1, S8 data2)
{
	this->data1 = data1;
	this->data2 = data2;
}

/*------------------------------------------------------------------------------
--  関数名      ：Logger_Send
--  概要        ：NXTの全ポートに接続されたセンサおよびモータ（回転角度）のデータ
--              ：および内部状態データ（システムタイマ、バッテリ電圧）等を送信
--              ：する。
--              ：
--  引数        ：S8			ユーザーデータ1
--              ：S8			ユーザーデータ2
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Logger_send(Logger* this)
{
	// ロギングデータを送信
	// ----------------------------------------------------------------------
	//	<データパケット>	<項目>                            	<データ型>
	//	 0- 3バイト     	システムタイマー値[msec]          	U32
	//	 4- 4バイト     	ユーザーデータ1                   	S8
	//	 5- 5バイト     	ユーザーデータ2                   	S8
	//	 6- 7バイト     	バッテリ電圧値[mV]                	U16
	//	 8-11バイト     	ポートA ：尻尾モータ				S32
	//	12-15バイト     	ポートB ：サーボモータ回転角度[度]	S32
	//	16-19バイト     	ポートC ：サーボモータ回転角度[度]	S32
	//	20-21バイト     	ポートS1：ジャイロセンサ         	S16
	//	22-23バイト     	ポートS2：超音波センサ  	       	S16
	//	24-25バイト     	ポートS3：光センサ		         	S16
	//	26-27バイト     	ポートS4：タッチセンサ	         	S16
	//	28-31バイト     	超音波センサデータ                	S32
	// ----------------------------------------------------------------------
	ecrobot_bt_data_logger(this->data1, this->data2);
}
