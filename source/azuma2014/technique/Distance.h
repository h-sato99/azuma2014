/*******************************************************************************
**  �t�@�C����  �FDistance.h
**  �T�v        �F��������N���X
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _Distance_H_
#define _Distance_H_

#include "CourseInfo.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct Distance
{
	int initDistance;
} Distance;

// ���J����
void Distance_init(Distance* this);
void Distance_set(Distance* this, MeasureInfo* measureInfo);
BOOL Distance_check(Distance* this, MeasureInfo* measureInfo, int distance);

#endif /* _Distance_H_ */
