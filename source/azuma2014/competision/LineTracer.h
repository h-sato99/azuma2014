/*******************************************************************************
**  �t�@�C����  �FLineTracer.h
**  �T�v        �F���C���g���[�X�N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/
#ifndef _LineTracer_H_
#define _LineTracer_H_

#include "Info.h"
#include "device/LightSensor.h"
#include "technique/PidControl.h"


// ������ێ����邽�߂̍\���̂̒�`
typedef struct LineTracer
{
	LightSensor *lightSensor;
	PidControl *pidControl;
	int brightness;
	int turnDeff1;
	int turnDeff2;
	int count;
	F32 turn;
	float target;
} LineTracer;


// ���J����
void LineTracer_init(LineTracer* this);
void LineTracer_trace(LineTracer* this, Info* info);
F32 LineTracer_getTurn(LineTracer* this);
void LineTracer_setTarget(LineTracer* this, float target);
#endif /* _LineTracer_H_ */

