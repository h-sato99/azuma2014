/*******************************************************************************
**  �t�@�C����  �FCommunication.h
**  �T�v        �F
**  �ڍ�        �F
*******************************************************************************/

#ifndef _Communication_H_
#define _Communication_H_

#include <string.h>

#include "command.h"
#include "device/Logger.h"
#include "device/Bluetooth.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct Communication
{
	Command *command;
	Bluetooth *bluetooth;
	Logger *logger;
	char buf[BT_MAX_RX_BUF_SIZE];
	char sendBuf[BT_MAX_RX_BUF_SIZE];
	int dataLength;
	int sendBufLength;
} Communication;

// ���J����
void Communication_init(Communication* this);
void Communication_communicate(Communication* this);
void Communication_getCommand(Communication* this);
void Communication_setLogData1(Communication* this, S8 data);
void Communication_setLogData2(Communication* this, S8 data);
void Communication_setSendData(Communication* this, char* buf, unsigned int len);

#endif /* _Communication_H_ */
