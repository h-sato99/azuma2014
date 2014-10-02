/*******************************************************************************
**  �t�@�C����  �FLineChange.c
**  �T�v        �F���C���ؑփN���X
**  �ڍ�        �F
*******************************************************************************/

#include "LineChange.h"

#define NONE			0		// �����l
#define NORMAL			50		// �ʏ�
#define TURN			30		// ����l
#define DISTANCE		3000	// ���s����

void LineChange_init(LineChange* this)
{
	this->orderNum = NONE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FLineChange_action
--  �T�v        �F���C���ؑ֏��������s����
--              �F
--  ����        �F
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
BOOL LineChange_action(LineChange* this)
{
	// ���C���̋t���֑��s����
	this->orderNum = OrderList_manualRunning(this->orderList,NORMAL,TURN,TURN_FRONT,NONE,DISTANCE);

	if(OrderList_checkFinished(this->orderList,this->orderNum))
	{
		// ���C���̋t���֑��s�����������ꍇ�A�G�b�W�ؑ֏������s���Atrue��Ԃ�
		// TODO �G�b�W�ؑ֏������K�v
		return TRUE;
	}
	// false��Ԃ�
	return FALSE;
}
