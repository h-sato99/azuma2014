/*******************************************************************************
**  �t�@�C����  �FBumpDecision.c
**  �T�v        �F�Փˌ��m�N���X
**  �ڍ�        �F
*******************************************************************************/

#include "BumpDecision.h"

#define TARGET	500		//臒l

// ����������
void BumpDecision_init(BumpDecision* this)
{

}

//
BOOL BumpDecision_checkBump(BumpDecision* this)
{

	// �W���C���Z���T�̒l�𔻒肷��
	if(GyroSensor_getAngularVelocity(this) > TARGET)
	{
		// �W���C���Z���T��臒l�𒴂����ꍇ�Atrue��Ԃ�
		return true;
	}

	// false��Ԃ�
	return false;
}
