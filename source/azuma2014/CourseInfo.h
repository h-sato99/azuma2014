/*******************************************************************************
**  �t�@�C����  �FCourseInfo.h
**  �T�v        �F�R�[�X���N���X��`
**  �ڍ�        �F
*******************************************************************************/

#ifndef _CourseInfo_H_
#define _CourseInfo_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct MeasureInfo
{
	int countGrayMarker;
	int leftMotorAngle;
	int rightMotorAngle;
	int tailAngle;
	BOOL derailmentFlag;
} MeasureInfo;

// ���J����
// �Ȃ�

#endif /* _CourseInfo_H_ */
