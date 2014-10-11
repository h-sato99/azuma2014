/*******************************************************************************
**  �t�@�C����  �FMogul.c
**  �T�v        �F
**  �ڍ�        �F
*******************************************************************************/

#include "Mogul.h"
#define MOGUL_FORWARD			 40                 // ���[�O���p�O�i�l
#define MOGUL_TURN				 1                    // ���[�O���p����l
#define MOGUL_TURN_STATE 		 0              // ���[�O���p������
#define MOGUL_FINISH_TIME 		 0             // ���[�O���p�I������
#define MOGUL_FINISH_DISTANCE 	 200       // ���[�O���p�I������

#define NONE					0
#define MOGUL_STOP_TIME			200
int i = 0;

/*------------------------------------------------------------------------------
--  �֐���      �FMogul_init
--  �T�v        �F���[�O���U��������������B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Mogul_init(Mogul* this){
	this->orderNum = 0;
	this->mode = 0;
}


/*------------------------------------------------------------------------------
--  �֐���      �FMogul_main
--  �T�v        �F���[�O���U�������s����B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �FBOOL
------------------------------------------------------------------------------*/
BOOL Mogul_main(Mogul* this){
	switch(this->mode)
	{
	case 0:
		//�}�j���A�����s
		this->orderNum = OrderList_manualRunning(
				this->orderList,
				MOGUL_FORWARD,
				MOGUL_TURN,
				MOGUL_TURN_STATE,
				MOGUL_FINISH_TIME,
				MOGUL_FINISH_DISTANCE);
		this->mode = 1;
		break;
	case 1:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_manualRunning(this->orderList,NONE,NONE,NONE,MOGUL_STOP_TIME,NONE);
			this->mode = 2;
		}
		break;
	case 2:
		if (OrderList_checkFinished(this->orderList,this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}


