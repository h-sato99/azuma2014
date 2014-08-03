/*******************************************************************************
**  �t�@�C����  �FCommunication.c
**  �T�v        �F
**  �ڍ�        �F
*******************************************************************************/

#include "Communication.h"

static void Communication_sendData(Communication* this);
static void Communication_receiveData(Communication* this);

void Communication_init(Communication* this)
{
	this->dataLength = 0;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCommunication_communicate
--  �T�v        �FBluetooth�𗘗p����PC�ƒʐM����
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Communication_communicate(Communication* this)
{
	BOOL isConnection;

	isConnection = Bluetooth_checkConnection(this->bluetooth);
	if(isConnection == TRUE)
	{
		// �ڑ����̏ꍇ
		Communication_sendData(this);
		Communication_receiveData(this);
	}
	else
	{
		// ���ڑ��̏ꍇ
		Bluetooth_start(this->bluetooth);
		isConnection = Bluetooth_checkConnection(this->bluetooth);
		if(isConnection == TRUE)
		{
			ecrobot_sound_tone(659, 100, 70);
		}
	}
}

/*------------------------------------------------------------------------------
--  �֐���      �FCommunication_sendData
--  �T�v        �FPC�Ƀ��O���𑗐M����
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Communication_sendData(Communication* this)
{
	Logger_send(this->logger);
}

/*------------------------------------------------------------------------------
--  �֐���      �FCommunication_receiveData
--  �T�v        �FPC���瑗�M���ꂽ�f�[�^������
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Communication_receiveData(Communication* this)
{
	this->dataLength = Bluetooth_receive(this->bluetooth, this->buf);
}

/*------------------------------------------------------------------------------
--  �֐���      �FCommunication_setLogData1
--  �T�v        �F���O�ɔC�ӂ̕�����ݒ肷��
--              �F
--  ����        �Fdata  ���O�ɐݒ肷��f�[�^
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Communication_setLogData1(Communication* this, S8 data)
{
	this->logger->data1 = data;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCommunication_setLogData2
--  �T�v        �F���O�ɔC�ӂ̕�����ݒ肷��
--              �F
--  ����        �Fdata  ���O�ɐݒ肷��f�[�^
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Communication_setLogData2(Communication* this, S8 data)
{
	this->logger->data2 = data;
}


/*------------------------------------------------------------------------------
--  �֐���      �FreceiveData
--  �T�v        �FPC������󂯎�����f�[�^����͂��ACommand�ɏ����i�[����
--              �F
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Communication_getCommand(Communication* this)
{
	int intCommand;
	int intValue;

	this->command->command = 0;
	this->command->value = 0;

	// �f�[�^�T�C�Y�̃`�F�b�N
	if(this->dataLength < 5)
	{
		return;
	}

	// �R�}���h
	intCommand = ((int)this->buf[0]) * 10 + ((int)this->buf[1]);
	this->command->command = intCommand;

	// �l
	intValue = ((int)this->buf[3]) * 1000 + ((int)this->buf[4]) * 100 + ((int)this->buf[5]) * 10 + ((int)this->buf[6]);

	if(((int)this->buf[2]) == 1)
	{
		intValue *= -1;
	}

	this->command->value = intValue;
}
