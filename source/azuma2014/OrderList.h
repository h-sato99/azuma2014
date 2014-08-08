/*******************************************************************************
**  �t�@�C����  �FOrderList.h
**  �T�v        �F�w�����X�g�N���X��`
**  �ڍ�        �F���s�̂𓮂������߂̎w����ێ�����N���X�B
*******************************************************************************/

#ifndef _OrderList_H_
#define _OrderList_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct OrderList
{
	int orderIndex;
} OrderList;

// ���J����
void OrderList_init(OrderList* this);

#endif /* _OrderList_H_ */
void OrderList_getOrder(OrderList* this);
void OrderList_addOrder(OrderList* this, int type, int value1, int value2, int value3, int finishTime, int finishValue);
void OrderList_finishOrder(OrderList* this, int orderIndex);
BOOL OrderList_checkFinished(OrderList* this, int orderIndex);
int OrderList_manualRunning(OrderList* this, int forward, int turn, int turnState, int finishTime, int finishDistance);
int OrderList_lineTraceRunning(OrderList* this, int target, int forward, int turnState, int finishTime, int finishDistance);
int OrderList_stop(OrderList* this);
