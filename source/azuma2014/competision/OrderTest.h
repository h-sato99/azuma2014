/*******************************************************************************
**  �t�@�C����  �FOrderTest.h
**  �T�v        �F
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _OrderTest_H_
#define _OrderTest_H_

#include "competision/OrderList.h"
#include "competision/Runner.h"


// ������ێ����邽�߂̍\���̂̒�`
typedef struct OrderTest{
	OrderList *orderList;
	int orderNum;				//
	int mode;
} OrderTest;

// ���J����
void OrderTest_init(OrderTest* this);
BOOL OrderTest_tailRun(OrderTest* this);
BOOL OrderTest_figureL(OrderTest* this);
BOOL OrderTest_strateRun(OrderTest* this);

#endif /* _OrderTest_H_ */
