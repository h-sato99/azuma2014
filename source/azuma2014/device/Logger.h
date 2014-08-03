/*******************************************************************************
**  �t�@�C����  �FLogger.h
**  �T�v        �F���O�o�̓N���X�i�w�b�_�t�@�C���j
**  �ڍ�        �F���M���O�f�[�^���}�X�^�[�f�o�C�X�ɓ]�����邽�߂̏������`�B
**              �FNXT GamePad�̃f�[�^���M���O�@�\���g�p���邱�Ƃ��ł���B
**              �FNXT GamePad�ł̓��M���O�����f�[�^��C�ӂ�CSV�t�@�C���Ƃ��ĕۑ�
**              �F���邱�Ƃ��ł���B
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
