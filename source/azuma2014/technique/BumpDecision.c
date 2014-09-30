/*******************************************************************************
**  �t�@�C����  �FBumpDecision.c
**  �T�v        �F�Փˌ��m�N���X
**  �ڍ�        �F
*******************************************************************************/

#include "BumpDecision.h"

#define TARGET_LOW		300		//臒l
#define TARGET_HIGH		800		//臒l

// ����������
void BumpDecision_init(BumpDecision* this)
{
	this->gyroValue = 600;
}

//
BOOL BumpDecision_checkBump(BumpDecision* this)
{

	this->gyroValue = GyroSensor_getAngularVelocity(this->gyroSensor);
	// �W���C���Z���T�̒l�𔻒肷��
	if(this->gyroValue < TARGET_LOW || this->gyroValue > TARGET_HIGH )
	{
		// �W���C���Z���T��臒l�𒴂����ꍇ�Atrue��Ԃ�
		return true;
	}

	// false��Ԃ�
	return false;
}
