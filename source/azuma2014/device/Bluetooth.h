/*******************************************************************************
**  �t�@�C����  �FBluetooth.h
**  �T�v        �FBluetooth����N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _Bluetooth_H_
#define _Bluetooth_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

typedef struct Bluetooth
{
	char *passKey;
} Bluetooth;

void Bluetooth_init(Bluetooth* this);
void Bluetooth_start(Bluetooth* this);
BOOL Bluetooth_checkConnection(Bluetooth* this);
void Bluetooth_terminate(Bluetooth* this);
unsigned int Bluetooth_receive(Bluetooth* this, char* buf);
int Bluetooth_send(Bluetooth* this, char* buf, unsigned int len);

#endif /* _Bluetooth_H_ */
