/*******************************************************************************
**  �t�@�C����  �FBumpDecision.h
**  �T�v        �F�Փˌ��m�N���X��`
**  �ڍ�        �F
*******************************************************************************/

#ifndef BUMPDECISION_H_
#define BUMPDECISION_H_

#include "device/GyroSensor.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct BumpDecision
{
	GyroSensor *gyroSensor;
} BumpDecision;

void BumpDecision_init(BumpDecision* this);
BOOL BumpDecision_checkBump(BumpDecision* this);

#endif /* BUMPDECISION_H_ */
