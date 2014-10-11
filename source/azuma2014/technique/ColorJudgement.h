/*******************************************************************************
**  �t�@�C����  �FColorJudgement.h
**  �T�v        �F
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _ColorJudgement_H_
#define _ColorJudgement_H_


#include "device/LightSensor.h"


// ������ێ����邽�߂̍\���̂̒�`
typedef struct ColorJudgement{
	unsigned int threshold;
	LightSensor *lightSensor;
} ColorJudgement;

typedef enum Color{
	BLACK,
	NON_BLACK,
} COLOR;

// ���J����
void ColorJudgement_init(ColorJudgement* this);
COLOR ColorJudgement_judgeColor(ColorJudgement* this);

#endif /* _ColorJudgement_H_ */

