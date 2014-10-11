/*******************************************************************************
**  �t�@�C����  �FLineComeback.h
**  �T�v        �F
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _LineComeback_H_
#define _LineComeback_H_

#include "competision/OrderList.h"
#include "technique/ColorJudgement.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct LineComeback{
	ColorJudgement *colorJudgement;
	OrderList *orderList;
	int mode;					// ���s���[�h
	int orderNum;				// �I�[�_�[�ԍ�
} LineComeback;

// ���s���[�h��`
typedef enum active{
	STOP,
	TURNLEFT,
	TURNRIGHT
} Active;

// �����p�l��`
typedef enum direction{
	LEFT,
	RIGHT
} Direction;

// ���J����
void LineComeback_init(LineComeback* this);
BOOL LineComeback_main(LineComeback* this,Direction turnDirection);

#endif /* _LineComeback_H_ */
