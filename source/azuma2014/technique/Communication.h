/*******************************************************************************
**  ファイル名  ：Communication.h
**  概要        ：
**  詳細        ：
*******************************************************************************/

#ifndef _Communication_H_
#define _Communication_H_

#include "command.h"
#include "device/Logger.h"
#include "device/Bluetooth.h"

// 属性を保持するための構造体の定義
typedef struct Communication
{
	Command *command;
	Bluetooth *bluetooth;
	Logger *logger;
	char buf[BT_MAX_RX_BUF_SIZE];
	int dataLength;
} Communication;

// 公開操作
void Communication_init(Communication* this);
void Communication_communicate(Communication* this);
void Communication_getCommand(Communication* this);
void Communication_setLogData1(Communication* this, S8 data);
void Communication_setLogData2(Communication* this, S8 data);

#endif /* _Communication_H_ */
