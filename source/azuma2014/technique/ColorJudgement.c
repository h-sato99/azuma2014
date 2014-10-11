/*******************************************************************************
**  �t�@�C����  �FColorJudgement.c
**  �T�v        �F
**  �ڍ�        �F
*******************************************************************************/

#include "ColorJudgement.h"
#define LIGHT_BLACK  570	// ���F�̌��Z���T�l


/*------------------------------------------------------------------------------
--  �֐���      �FColorJudgement_init
--  �T�v        �F�F���������������B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void ColorJudgement_init(ColorJudgement* this){
	this->threshold = LIGHT_BLACK;
}


/*------------------------------------------------------------------------------
--  �֐���      �FColorJudgement_main
--  �T�v        �F�F���肷��B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FTRUE or FALSE
------------------------------------------------------------------------------*/
BOOL ColorJudgement_judgeColor(ColorJudgement* this){
	// ���Z���T����̎擾�l������
	// ���ȏ�ł���΁uTRUE�v���A
	// �����łȂ���΁uFALSE�v��Ԃ�
	if(LightSensor_getBrightness(this->lightSensor) >= this->threshold){
		return  TRUE;
	}
	return FALSE;
} 

