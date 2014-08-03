/*******************************************************************************
**  �t�@�C����  �FCompetision.h
**  �T�v        �F���Z�N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _Competision_H_
#define _Competision_H_

#include "Info.h"
#include "LineTracer.h"
#include "Strategy.h"
#include "Runner.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct Competision
{
	LineTracer *lineTracer;
	Strategy *strategy;
	Runner *runner;
} Competision;

// ���J����
void Competision_init(Competision* this);
void Competision_action(Competision* this, Info* info);

#endif /* _Competision_H_ */
