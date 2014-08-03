/*******************************************************************************
**  ファイル名  ：Communication.c
**  概要        ：
**  詳細        ：
*******************************************************************************/

#include "Communication.h"

static void Communication_sendData(Communication* this);
static void Communication_receiveData(Communication* this);

void Communication_init(Communication* this)
{
	this->dataLength = 0;
}

/*------------------------------------------------------------------------------
--  関数名      ：Communication_communicate
--  概要        ：Bluetoothを利用してPCと通信する
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Communication_communicate(Communication* this)
{
	BOOL isConnection;

	isConnection = Bluetooth_checkConnection(this->bluetooth);
	if(isConnection == TRUE)
	{
		// 接続中の場合
		Communication_sendData(this);
		Communication_receiveData(this);
	}
	else
	{
		// 未接続の場合
		Bluetooth_start(this->bluetooth);
		isConnection = Bluetooth_checkConnection(this->bluetooth);
		if(isConnection == TRUE)
		{
			ecrobot_sound_tone(659, 100, 70);
		}
	}
}

/*------------------------------------------------------------------------------
--  関数名      ：Communication_sendData
--  概要        ：PCにログ情報を送信する
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Communication_sendData(Communication* this)
{
	Logger_send(this->logger);
}

/*------------------------------------------------------------------------------
--  関数名      ：Communication_receiveData
--  概要        ：PCから送信されたデータを受取る
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Communication_receiveData(Communication* this)
{
	this->dataLength = Bluetooth_receive(this->bluetooth, this->buf);
}

/*------------------------------------------------------------------------------
--  関数名      ：Communication_setLogData1
--  概要        ：ログに任意の文字を設定する
--              ：
--  引数        ：data  ログに設定するデータ
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Communication_setLogData1(Communication* this, S8 data)
{
	this->logger->data1 = data;
}

/*------------------------------------------------------------------------------
--  関数名      ：Communication_setLogData2
--  概要        ：ログに任意の文字を設定する
--              ：
--  引数        ：data  ログに設定するデータ
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Communication_setLogData2(Communication* this, S8 data)
{
	this->logger->data2 = data;
}


/*------------------------------------------------------------------------------
--  関数名      ：receiveData
--  概要        ：PC側から受け取ったデータを解析し、Commandに情報を格納する
--              ：
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Communication_getCommand(Communication* this)
{
	int intCommand;
	int intValue;

	this->command->command = 0;
	this->command->value = 0;

	// データサイズのチェック
	if(this->dataLength < 5)
	{
		return;
	}

	// コマンド
	intCommand = ((int)this->buf[0]) * 10 + ((int)this->buf[1]);
	this->command->command = intCommand;

	// 値
	intValue = ((int)this->buf[3]) * 1000 + ((int)this->buf[4]) * 100 + ((int)this->buf[5]) * 10 + ((int)this->buf[6]);

	if(((int)this->buf[2]) == 1)
	{
		intValue *= -1;
	}

	this->command->value = intValue;
}
