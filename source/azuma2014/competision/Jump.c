/*******************************************************************************
**  �t�@�C����  �FJump.c
**  �T�v        �F�W�����v��N���X
**  �ڍ�        �F�W�����v��U���Ɋւ��鏈�����`�B
*******************************************************************************/

#include "Jump.h"

#define NONE			0		// �����l
#define TARGET			500		// 臒l
#define LOW				40		// �ᑬ
#define NORMAL			80		// �ʏ�
#define HIGH			120		// ����
#define	BACK			-80		// ���
#define HOLE_DISTANCE	100		// ���s����(��)
#define FINISH_DISTANCE	120		// ���s����(�U��)

typedef enum State
{
	START,
	CHECK_HOLE,
	DASH_RUN,
	FINISHED
} State;

void Jump_init(Jump* this)
{
	this->mode = START;
	this->orderNum = NONE;
}


BOOL Jump_action(Jump* this)
{
	switch(this->mode)
	{
	case START:
		// �����m�ɐ؂�ւ���
		this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,NORMAL,NONE,NONE,HOLE_DISTANCE);
		this->mode = CHECK_HOLE;
		break;

	case CHECK_HOLE:
		// �������m���������肷��
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// �������m�����ꍇ�A�������s�ɐ؂�ւ���
			this->orderNum = OrderList_lineTraceRunning(this->orderList,TARGET,HIGH,NONE,NONE,FINISH_DISTANCE);
			this->mode = DASH_RUN;
		}
		break;

	case DASH_RUN:
		// �������s���������������肷��
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			// �������s�����������ꍇ�A�I�����������s����
			this->mode = FINISHED;
		}
		break;

	case FINISHED:
		// true��Ԃ�
		return true;
	}
	// false��Ԃ�
	return false;

}

