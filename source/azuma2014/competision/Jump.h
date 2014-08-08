/*******************************************************************************
**  �t�@�C����  �FJump.h
**  �T�v        �F�W�����v��N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef JUMP_H_
#define JUMP_H_

#include "OrderList.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct Jump
{
	OrderList *orderList;
	int mode;
	int orderNum;
} Jump;

// ���J����
void Jump_init(Jump* this);
BOOL Jump_action(Jump* this);

#endif /* JUMP_H_ */
