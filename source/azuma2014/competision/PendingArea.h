/*******************************************************************************
**  �t�@�C����  �FPendingArea.h
**  �T�v        �F
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef PENDINGAREA_H_
#define PENDINGAREA_H_

#include "competision/OrderList.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct PendingArea{
	OrderList *orderList;
	int orderNum;
	int mode;
	int privateMode;
} PendingArea;

typedef enum PendingAreaState
{
	PENDINGAREA_START,
	PENDINGAREA_CHECK_POINT1,
	PENDINGAREA_CHECK_POINT2,
	PENDINGAREA_CHECK_POINT3,
	PENDINGAREA_CHECK_POINT4,
	PENDINGAREA_CHECK_POINT5,
	PENINGAREA_FINISHED
} PendingAreaState;

// ���J����
void PendingArea_init(PendingArea* this);
BOOL PendingArea_main(PendingArea* this);


#endif /* PENDINGAREA_H_ */
