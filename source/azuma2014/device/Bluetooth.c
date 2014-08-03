/*******************************************************************************
**  ファイル名  ：Bluetooth.c
**  概要        ：Bluetooth制御クラス
**  詳細        ：Bluetoothに関する制御を行う
*******************************************************************************/

#include "device/Bluetooth.h"

#define C_PASS_KEY          "0005" /* Bluetooth通信用パスキー */


void Bluetooth_init(Bluetooth* this)
{
	this->passKey = C_PASS_KEY;
}

void Bluetooth_start(Bluetooth* this)
{

	// NXTをBluetooth通信のスレーブデバイスとして初期化し、マスターデバイス
	// （PC、NXTマスターデバイス）との接続を確立する
	ecrobot_init_bt_slave(this->passKey);
}

BOOL Bluetooth_checkConnection(Bluetooth* this)
{
	SINT status;

	// 接続が確立しているか確認
	status = ecrobot_get_bt_status();

	if(status == BT_STREAM)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


/*------------------------------------------------------------------------------
--  関数名      ：Bluetooth_terminate
--  概要        ：Bluetooth通信の終了処理を行う（。
--              ：nxtOSEKが提供しているデバイス終了用フック関数内で必ず呼び出す
--              ：こと。
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Bluetooth_terminate(Bluetooth* this)
{
	// Bluetooth通信を終了
	ecrobot_term_bt_connection();
}

// 以降はリモートスタート用
/*------------------------------------------------------------------------------
--  関数名      ：Bluetooth_receive
--  概要        ：Buletoothからのデータを受信する
--              ：
--  引数        ：char		受信データ
--  戻り値      ：受信データの長さ
------------------------------------------------------------------------------*/
unsigned int Bluetooth_receive(Bluetooth* this, char* buf)
{
	return ecrobot_read_bt(buf, 0, BT_MAX_RX_BUF_SIZE);
}


/*------------------------------------------------------------------------------
--  関数名      ：Bluetooth_send
--  概要        ：Buletoothからのデータを送信する
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
int Bluetooth_send(Bluetooth* this, char* buf, unsigned int len)
{
	return ecrobot_send_bt(buf, 0, len);
}


