/*******************************************************************************
**  �t�@�C����  �FOrder.h
**  �T�v        �F
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _Order_H_
#define _Order_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

typedef enum OrderType
{
	ORDER_TYPE_NONE,
	ORDER_TYPE_MANUAL_RUNNING,
	ORDER_TYPE_LINETRACE_RUNNING,
	ORDER_TYPE_STOP
} OrderType;

// ������ێ����邽�߂̍\���̂̒�`
typedef struct Order
{
	int type;
	int value1;
	int value2;
	int value3;
	int finishTime;
	int finishValue;
	BOOL isFinished;
} Order;

// ���J����
void Order_init(Order* this);

#endif /* _Order_H_ */
