/*******************************************************************************
**  �t�@�C����  �FFigureL.c
**  �T�v        �F
**  �ڍ�        �F
*******************************************************************************/

#include "FigureL.h"
#define MOGUL_FORWARD			 40                 // ���[�O���p�O�i�l
#define MOGUL_TURN_FORWARD		 80                 // ���[�O���p�O�i�l
#define MOGUL_TURN				 100                    // ���[�O���p����l
#define MOGUL_TURN_STATE 		 1              // ���[�O���p������
#define MOGUL_FINISH_TIME 		 0             // ���[�O���p�I������
#define MOGUL_FINISH_DISTANCE 	 100       // ���[�O���p�I������
#define MOGUL_TURN_DISTANCE 	 80       // ���[�O���p�I������
#define MOGUL_TARGET 	 500       // ���[�O���p�I������


/*------------------------------------------------------------------------------
--  �֐���      �FFigureL_init
--  �T�v        �F�t�B�M���A�k������������B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void FigureL_init(FigureL* this){
	this->orderNum = 0;
	// test
	this->mode = 0;
//	this->mode = 1;
}


/*------------------------------------------------------------------------------
--  �֐���      �FFigureL_main
--  �T�v        �F�t�B�M���A�k�U�������s����B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL FigureL_action(FigureL* this){
	//ecrobot_sound_tone(659, 70, 95);
	switch(this->mode)
	{
	case 0:
		//�}�j���A�����s
		ecrobot_sound_tone(659, 70, 95);
		this->orderNum = OrderList_lineTraceRunning(
				this->orderList,
				MOGUL_FORWARD,
				MOGUL_TARGET,
				//MOGUL_TURN_STATE,
				2,
				MOGUL_FINISH_TIME,
				MOGUL_FINISH_DISTANCE);
		this->mode = 1;
		break;
	case 1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			OrderList_turnOnSpotLeft(
					this->orderList,
					MOGUL_TURN_FORWARD,
					MOGUL_TURN,
					MOGUL_FINISH_TIME,
					MOGUL_TURN_DISTANCE);
			ecrobot_sound_tone(659, 70, 95);
			this->mode = 2;
		}
		break;
	case 2:
		//���s��~
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					MOGUL_FORWARD,
					MOGUL_TARGET,
					MOGUL_TURN_STATE,
					MOGUL_FINISH_TIME,
					MOGUL_FINISH_DISTANCE);
			ecrobot_sound_tone(659, 70, 95);
			this->mode = 3;
		}
		break;
	case 3:
		//���s��~
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			ecrobot_sound_tone(659, 70, 95);
			this->orderNum = OrderList_manualRunning(
					this->orderList,
					0,
					0,
					0,
					2000,
					0);
		}
		break;
	case 4:
		//���s��~
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			ecrobot_sound_tone(659, 70, 95);
			return TRUE;
		}
	}

		return FALSE;
}


