/*******************************************************************************
**  �t�@�C����  �FMogul.h
**  �T�v        �F
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _Mogul_H_
#define _Mogul_H_

#include "competision/OrderList.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct Mogul{
	OrderList *orderList;
	int orderNum;				//
} Mogul;

// ���J����
void Mogul_init(Mogul* this);
BOOL Mogul_main(Mogul* this);

#endif /* _Mogul_H_ */
