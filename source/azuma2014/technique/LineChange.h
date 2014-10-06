/*******************************************************************************
**  �t�@�C����  �FLineChange.h
**  �T�v        �F���C���ؑփN���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef LINECHANGE_H_
#define LINECHANGE_H_

#include "competision/OrderList.h"
#include "competision/LineTracer.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct LineChange
{
	OrderList *orderList;
	LineTracer *lineTracer;
	int orderNum;
	int mode;
} LineChange;

// ���J����
void LineChange_init(LineChange* this);
BOOL LineChange_action(LineChange* this);

#endif /* LINECHANGE_H_ */
