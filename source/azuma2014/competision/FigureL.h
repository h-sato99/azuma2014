/*******************************************************************************
**  �t�@�C����  �FFigureL.h
**  �T�v        �F
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _FigureL_H_
#define _FigureL_H_

#include "competision/OrderList.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct FigureL{
	OrderList *orderList;
	int orderNum;
	int mode;
} FigureL;

// ���J����
void FigureL_init(FigureL* this);
BOOL FigureL_action(FigureL* this);

#endif /* _FigureL_H_ */
