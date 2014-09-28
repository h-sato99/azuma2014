/*******************************************************************************
**  �t�@�C����  �FCourse.h
**  �T�v        �F
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _Course_H_
#define _Course_H_

#include "competision/OrderList.h"
#include "competision/Runner.h"


// ������ێ����邽�߂̍\���̂̒�`
typedef struct Course{
	OrderList *orderList;
	int orderNum;
	int mode;
	int target;
} Course;

// ���J����
void Course_init(Course* this);
void Course_resetMode(Course* this);
BOOL Course_strateRunIN(Course* this);
BOOL Course_strateRunOUT(Course* this);
BOOL Course_stableRunOUT(Course* this);
BOOL Course_stableRunIN(Course* this);
BOOL Course_figureL(Course* this);

#endif /* _Course_H_ */
