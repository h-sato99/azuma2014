/*******************************************************************************
**  �t�@�C����  �FWheelAverage.h
**  �T�v        �F���ԗւ̒l���擾���A���ς�Ԃ��B
**  �ڍ�        �F���ԗւ̒l���擾���A���ς�Ԃ��B
*******************************************************************************/

#ifndef _WheelAverage_H_
#define _WheelAverage_H_

#include "technique/Wheel.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct WheelAverage
{
	Wheel *wheel;				//�z�C�[���N���X
	int LeftWheel;				//���ԗւ̒l
	int RightWheel;				//�E�ԗւ̒l
	int Average;				//���ԗւ̎擾�p
}WheelAverage;

// ���J����
void WheelAverage_init(WheelAverage* this);
int WheelAverage_action(WheelAverage* this);

#endif /* _WheelAverage_H_ */
