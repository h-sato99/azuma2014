/*******************************************************************************
**  ファイル名  ：Communication.c
**  概要        ：
**  詳細        ：
*******************************************************************************/

#include "Communication.h"

static void Communication_sendLogData(Communication* this);
static void Communication_sendData(Communication* this);
static void Communication_receiveData(Communication* this);
static int Communication_getCommandValue(Communication* this, char* buf, int startValue);

void Communication_init(Communication* this)
{
	this->dataLength = 0;
	this->sendBufLength = 0;
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
		if(this->isSendLog)
		{
			Communication_sendLogData(this);
		}
		if(this->isSendData)
		{
			Communication_sendData(this);
		}
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
void Communication_sendLogData(Communication* this)
{
	Logger_send(this->logger);
}

/*------------------------------------------------------------------------------
--  関数名      ：Communication_sendData
--  概要        ：PCに情報を送信する
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Communication_setSendData(Communication* this, char* buf, unsigned int len)
{
	if(len > BT_MAX_RX_BUF_SIZE)
	{
		return;
	}

	memcpy(this->sendBuf, buf, len);
	this->sendBufLength = len;
}

/*------------------------------------------------------------------------------
--  関数名      ：Communication_sendData
--  概要        ：PCに情報を送信する
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Communication_sendData(Communication* this)
{
	if(this->sendBufLength > 0)
	{
		Bluetooth_send(this->bluetooth, this->sendBuf, this->sendBufLength);
	}
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
//	int intValue;
	int intBufIndex;

	intBufIndex = 0;

	this->command->command = 0;
	this->command->value1 = 0;
	this->command->value2 = 0;
	this->command->value3 = 0;
	this->command->value4 = 0;
	this->command->value5 = 0;

	// データサイズのチェック
	if(this->dataLength < 32)
	{
		return;
	}

	// コマンド
	intCommand = ((int)this->buf[0]) * 10 + ((int)this->buf[1]);
	this->command->command = intCommand;

	intBufIndex = 2;

	// 値
	this->command->value1 = Communication_getCommandValue(this, this->buf, intBufIndex);
	intBufIndex += 5;
	this->command->value2 = Communication_getCommandValue(this, this->buf, intBufIndex);
	intBufIndex += 5;
	this->command->value3 = Communication_getCommandValue(this, this->buf, intBufIndex);
	intBufIndex += 5;
	this->command->value4 = Communication_getCommandValue(this, this->buf, intBufIndex);
	intBufIndex += 5;
	this->command->value5 = Communication_getCommandValue(this, this->buf, intBufIndex);
	intBufIndex += 5;
	this->command->value6 = Communication_getCommandValue(this, this->buf, intBufIndex);
	intBufIndex += 5;
	/*
	if(this->dataLength >= 12)
	{
		this->command->value2 = Communication_getCommandValue(this, this->buf, intBufIndex);
		intBufIndex += 5;
	}
	if(this->dataLength >= 17)
	{
		this->command->value3 = Communication_getCommandValue(this, this->buf, intBufIndex);
		intBufIndex += 5;
	}
	if(this->dataLength >= 22)
	{
		this->command->value4 = Communication_getCommandValue(this, this->buf, intBufIndex);
		intBufIndex += 5;
	}
	if(this->dataLength >= 27)
	{
		this->command->value5 = Communication_getCommandValue(this, this->buf, intBufIndex);
		intBufIndex += 5;
	}
	*/

	/*
	intValue = ((int)this->buf[3]) * 1000 + ((int)this->buf[4]) * 100 + ((int)this->buf[5]) * 10 + ((int)this->buf[6]);

	if(((int)this->buf[2]) == 1)
	{
		intValue *= -1;
	}

	this->command->value = intValue;
	*/

	/*
	display_goto_xy(2, 1);
	display_int(this->command->value1, 14);
	display_goto_xy(2, 2);
	display_int(this->command->value2, 14);
	display_goto_xy(2, 3);
	display_int(this->command->value3, 14);
	display_goto_xy(2, 4);
	display_int(this->command->value4, 14);
	display_goto_xy(2, 5);
	display_int(this->command->value5, 14);
	display_update();
	*/

	this->command->value1 = Communication_getCommandValue(this, this->buf, 2);
}

/*------------------------------------------------------------------------------
--  関数名      ：getCommandValue
--  概要        ：PC側から受け取ったデータを解析し、値(Value)を算出する
--              ：
--              ：
--  引数        ：なし
--  戻り値      ：値(Value)
------------------------------------------------------------------------------*/
static int Communication_getCommandValue(Communication* this, char* buf, int startValue)
{
	int intValue;
	int intValue1000;
	int intValue100;
	int intValue10;
	int intValue1;

	// 数値の計算
	intValue1000 = ((int)this->buf[startValue + 1]) * 1000;
	intValue100 = ((int)this->buf[startValue + 2]) * 100;
	intValue10 = ((int)this->buf[startValue + 3]) * 10;
	intValue1 = (int)this->buf[startValue + 4];

	intValue = intValue1000 + intValue100 + intValue10 + intValue1;

	// 符号の考慮
	if(((int)this->buf[startValue]) == 1)
	{
		intValue *= -1;
	}

	return intValue;
}
