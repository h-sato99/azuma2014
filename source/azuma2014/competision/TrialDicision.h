/*******************************************************************************
**  �t�@�C����  �FTrialDicision.h
**  �T�v        �F����m�N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef TRIALDICISION_H_
#define TRIALDICISION_H_

#include "OrderList.h"
#include "technique/BumpDecision.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct TrialDicision
{
	OrderList *orderList;
	BumpDecision *bumpDecision;
	int mode;
	int orderNum;
} TrialDicision;

// ���J����
void TrialDicision_init(TrialDicision* this);
BOOL TrialDicision_action(TrialDicision* this);

#endif /* TRIALDICISION_H_ */
