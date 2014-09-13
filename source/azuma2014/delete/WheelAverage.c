/*******************************************************************************
**  �t�@�C����  �FClass.c
**  �T�v        �F���ԗւ̒l���擾���A���ς�Ԃ��B
**  �ڍ�        �F���ԗւ̒l���擾���A���ς�Ԃ��B
*******************************************************************************/

#include "technique/WheelAverage.h"
#define ConstNumberZero 0;

void WheelAverage_init(WheelAverage* this)
{
	this->LeftWheel = ConstNumberZero;
	this->RightWheel = ConstNumberZero;
	this->Average = ConstNumberZero;
}
int WheelAverage_action(WheelAverage* this)
{
	//�z�C�[���̒l�擾�A���ϒl�̌v�Z
	this->LeftWheel = Wheel_getLeftAngle(this->wheel);
	this->RightWheel = Wheel_getRightAngle(this->wheel);
	this->Average = (this->LeftWheel + this->RightWheel)/2;
	return this->Average;
}
