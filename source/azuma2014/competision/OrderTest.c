/*******************************************************************************
**  �t�@�C����  �FOrderTest.c
**  �T�v        �F
**  �ڍ�        �F
*******************************************************************************/

#include "OrderTest.h"
#define MOGUL_FORWARD			 40                 // ���[�O���p�O�i�l
#define MOGUL_TURN				 1                    // ���[�O���p����l
#define MOGUL_TURN_STATE 		 0              // ���[�O���p������
#define MOGUL_FINISH_TIME 		 0             // ���[�O���p�I������
#define MOGUL_FINISH_DISTANCE 	 200       // ���[�O���p�I������


/*------------------------------------------------------------------------------
--  �֐���      �FOrderTest_init
--  �T�v        �F���[�O���U��������������B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void OrderTest_init(OrderTest* this){
	this->orderNum = 0;
	this->mode = 0;
}


/*------------------------------------------------------------------------------
--  �֐���      �FOrderTest_main
--  �T�v        �F���[�O���U�������s����B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL OrderTest_tailRun(OrderTest* this){
	switch(this->mode)
	{
	case 0:
		//�}�j���A�����s
		this->orderNum = OrderList_manualRunning(
				this->orderList,
				-80,
				0,
				TURN_DRIVING,
				0,
				50);
		this->mode = 1;
		break;
	case 1:
		//���s��~
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_manualRunning(
					this->orderList,
					100,
					0,
					TURN_DRIVING,
					0,
					70);
			this->mode = 2;
		}
		break;
	case 2:
		this->orderNum = OrderList_manualRunning(
				this->orderList,
				0,
				0,
				TURN_DRIVING,
				0,
				0);
		return TRUE;

	}
	return FALSE;
}

BOOL OrderTest_figureL(OrderTest* this){
	switch(this->mode)
	{
	case 0:
		//�}�j���A�����s
		this->orderNum = OrderList_manualRunning(
				this->orderList,
				50,
				0,
				TURN_FRONT,
				0,
				100);
		this->mode = 1;
		break;
	case 1:
		//���s��~
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_manualRunning(
					this->orderList,
					50,
					100,
					TURN_FRONT,
					0,
					500);
			this->mode = 2;
		}
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_manualRunning(
					this->orderList,
					50,
					0,
					TURN_FRONT,
					0,
					0);
			this->mode = 3;
		}
		break;
	case 3:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_manualRunning(
					this->orderList,
					50,
					0,
					TURN_FRONT,
					0,
					0);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL OrderTest_strateRun(OrderTest* this)
{
	switch(this->mode)
	{
	case 0:
		//�}�j���A�����s
		this->orderNum = OrderList_setPID(this->orderList,5,7,20);
		this->mode = 1;
		break;
	case 1:
		//�}�j���A�����s
		this->orderNum = OrderList_lineTraceRunning(
				this->orderList,
				50,
				550,
				TURN_DRIVING,
				0,
				0);
		this->mode = 2;
		break;
	}
	return FALSE;
}

