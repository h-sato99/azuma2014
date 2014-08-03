/*******************************************************************************
**  �t�@�C����  �FTail.h
**  �T�v        �F�K�����[�^����N���X��`
**  �ڍ�        �F
*******************************************************************************/

#ifndef _Tail_H_
#define _Tail_H_

#include "device/Motor.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct Tail
{
	Motor *tailMotor;
} Tail;

// ���J����
void Tail_init(Tail* this);
void Tail_setAngle(Tail* this, int angle);
//
int Tail_getAngle(Tail* this);
//

#endif /* _Tail_H_ */
