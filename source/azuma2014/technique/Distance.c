/*******************************************************************************
**  �t�@�C����  �FDistance.c
**  �T�v        �F��������N���X
**  �ڍ�        �F���s�̂��ړ����������𑪂�
*******************************************************************************/

#include "Distance.h"

static int Distance_calc(Distance* this, MeasureInfo* measureInfo);

/*------------------------------------------------------------------------------
--  �֐���      �FDistance_init
--  �T�v        �F����������B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Distance_init(Distance* this)
{
	this->initDistance = 0;
}

/*------------------------------------------------------------------------------
--  �֐���      �FDistance_set
--  �T�v        �F��Ƃ��鋗����ݒ肷��B
--              �F
--  ����        �FmeasureInfo ������
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Distance_set(Distance* this, MeasureInfo* measureInfo)
{
	this->initDistance = Distance_calc(this, measureInfo);
}

/*------------------------------------------------------------------------------
--  �֐���      �FDistance_check
--  �T�v        �F�w�肵���������ړ��������ǂ������m�F����B
--              �F
--  ����        �FmeasureInfo ������
--              �Fdistance    ����
--  �߂�l      �F�m�F����
------------------------------------------------------------------------------*/
BOOL Distance_check(Distance* this, MeasureInfo* measureInfo, int distance)
{
	int calcWork;

	calcWork = this->initDistance - Distance_calc(this, measureInfo);

	// ��Βl�ɂ���
	if(calcWork < 0)
	{
		calcWork *= -1;
	}

	if(calcWork >= distance)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*------------------------------------------------------------------------------
--  �֐���      �FDistance_calc
--  �T�v        �F���E���[�^�̏o�͒l���狗�����Z�o����B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F����
------------------------------------------------------------------------------*/
static int Distance_calc(Distance* this, MeasureInfo* measureInfo)
{
	int calcWork;

	calcWork = (measureInfo->leftMotorAngle + measureInfo->rightMotorAngle) / 2;

	return calcWork;
}
