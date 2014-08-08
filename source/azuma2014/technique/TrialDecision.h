/*******************************************************************************
**  �t�@�C����  �FTrialDecision.h
**  �T�v        �F����m�N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef TRIALDECISION_H_
#define TRIALDECISION_H_

#include "OrderList.h"
#include "technique/BumpDecision.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct TrialDecision
{
	OrderList *orderList;
	BumpDecision *bumpDecision;
	int mode;
	int orderNum;
} TrialDecision;

// ���J����
void TrialDecision_init(TrialDecision* this);
BOOL TrialDecision_action(TrialDecision* this);

#endif /* TRIALDICISION_H_ */
