/*******************************************************************************
**  �t�@�C����  �FPendingArea.h
**  �T�v        �F
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef PENDINGAREA_H_
#define PENDINGAREA_H_

#include "competision/OrderList.h"
#include "competision/Runner.h"

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
BOOL PendingArea_action(PendingArea* this);
void PendingArea_privateModeInit(PendingArea* this);
BOOL PendingArea_straight(PendingArea* this);
BOOL PendingArea_left(PendingArea* this);
BOOL PendingArea_right(PendingArea* this);
BOOL PendingArea_leftOblique(PendingArea* this);
BOOL PendingArea_rightOblique(PendingArea* this);


#endif /* PENDINGAREA_H_ */
