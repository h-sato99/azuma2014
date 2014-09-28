/*******************************************************************************
**  �t�@�C����  �FFrontWheel.h
**  �T�v        �F�K�����[�^����N���X��`
**  �ڍ�        �F
*******************************************************************************/

#ifndef _FrontWheel_H_
#define _FrontWheel_H_

#include "device/Motor.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct FrontWheel
{
	Motor *frontMotor;
	int pwm;
} FrontWheel;

// ���J����
void FrontWheel_init(FrontWheel* this);
void FrontWheel_setAngle(FrontWheel* this, int angle);
//
int FrontWheel_getAngle(FrontWheel* this);
//

#endif /* _FrontWheel_H_ */
