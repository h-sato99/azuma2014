/*******************************************************************************
**  �t�@�C����  �FCheckStart.h
**  �T�v        �F�X�^�[�g����N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef CHECK_START_H_
#define CHECK_START_H_

#include "Info.h"
#include "technique/Tail.h"
#include "device/TouchSensor.h"
#include "device/Bluetooth.h"
#include "technique/Communication.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct CheckStart
{
	TouchSensor *touchSensor;
	Communication *communication;
	Tail *tail;
	int tailAngl;
	int started;
} CheckStart;


// ���J����
void CheckStart_init(CheckStart* this);
void CheckStart_waitStart(CheckStart* this, Info* info);
BOOL CheckStart_isStart(CheckStart* this);

#endif
