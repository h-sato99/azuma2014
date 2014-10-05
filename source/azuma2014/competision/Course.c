/*******************************************************************************
**  �t�@�C����  �FCourse.c
**  �T�v        �F
**  �ڍ�        �F
*******************************************************************************/

#include "Course.h"
//#define C_TARGET 600
#define C_TARGET 500


/*------------------------------------------------------------------------------
--  �֐���      �FCourse_init
--  �T�v        �F�R�[�X������������B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Course_init(Course* this){
	this->orderNum = 0;
	this->mode = 0;
	this->target = C_TARGET;
}

void Course_resetMode(Course* this)
{
	//test
	//this->orderNum = OrderList_setPID(this->orderList,5,7,20);
	//test
	this->mode = 0;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_strateRunIN
--  �T�v        �FIN�X�^�[�g�`���[�O��
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_strateRunIN(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,7,20);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
//					100,
					20,
					this->target,
					TURN_DRIVING,
					0,
					1000);
		}
		this->mode = 2;
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_strateRunOUT
--  �T�v        �FOUT�X�^�[�g�`�W�����v��
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_strateRunOUT(Course* this)
{
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,7,20);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					100,
					this->target,
					TURN_DRIVING,
					0,
					1100);
		}
		this->mode = 2;
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_stableRunOUT
--  �T�v        �FOUT�W�����v��`�d�l���m��
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_stableRunOUT(Course* this){
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					40,
					this->target,
					TURN_DRIVING,
					0,
					1800);
			this->mode = 2;
		}
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCourse_stableRunO
--  �T�v        �F
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Course_stableRunIN(Course* this){
	switch(this->mode)
	{
	case 0:
		//PID�ݒ�
		this->orderNum = OrderList_setPID(this->orderList,5,5,50);
		this->mode = 1;
		break;
	case 1:
		//���C���g���[�X���s
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
//					20,
					0,
					this->target,
					TURN_FRONT,
					0,
					1800);
			this->mode = 2;
		}
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}
