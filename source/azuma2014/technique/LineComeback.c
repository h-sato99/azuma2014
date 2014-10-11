/*******************************************************************************
**  �t�@�C����  �FLineComeback.c
**  �T�v        �F
**  �ڍ�        �F
*******************************************************************************/

#include "LineComeback.h"
#define NONE						0
#define COMEBACK_FORWARD			40		// ���C�����A�p�O�i�l
#define COMEBACK_TURN				100		// ���C�����A�p����l
#define COMEBACK_TURN_STATE			1		// ���C�����A�p������
#define COMEBACK_FINISH_TIME		0		// ���C�����A�p�I������
#define COMEBACK_FINISH_DISTANCE	100		// ���C�����A�p�I������
#define COMEBACK_STOP_TIME			2000	// ���C�����A�p�I������

int i = 0;

/*------------------------------------------------------------------------------
--  �֐���      �FLineComeback_init
--  �T�v        �F����������B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void LineComeback_init(LineComeback* this){
	this->mode = STOP;
}


/*------------------------------------------------------------------------------
--  �֐���      �FLineComeback_main
--  �T�v        �F���C�����A�����s����B
--              �F
--  ����        �FturnDirection�i��������j��0:LEFT,1�ȏ�:RIGHT
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
BOOL LineComeback_main(LineComeback* this,Direction turnDirection){
	switch(this->mode){
	case STOP:
		// ���s��~����
		this->orderNum = OrderList_manualRunning(this->orderList,NONE,NONE,NONE,COMEBACK_STOP_TIME,NONE);
		if(turnDirection==LEFT){
			this->mode = TURNLEFT;
		}
		this->mode = TURNRIGHT;
		return FALSE;

	case TURNLEFT:
		// ���ɐ��񂷂�
		if (OrderList_checkFinished(this->orderList,this->orderNum)){
			OrderList_turnOnSpotLeft(
				this->orderList,
				COMEBACK_FORWARD,
				COMEBACK_TURN,
				COMEBACK_FINISH_TIME,
				COMEBACK_FINISH_DISTANCE);
			ecrobot_sound_tone(659, 70, 95);
			this->mode = TURNRIGHT;
		}
		break;

	case TURNRIGHT:
		// �E�ɐ��񂷂�
		if (OrderList_checkFinished(this->orderList,this->orderNum)){
			OrderList_turnOnSpotRight(
				this->orderList,
				COMEBACK_FORWARD,
				COMEBACK_TURN,
				COMEBACK_FINISH_TIME,
				COMEBACK_FINISH_DISTANCE);
		ecrobot_sound_tone(659, 70, 95);
		this->mode = TURNLEFT;
		}
		break;

	}

	// �F������g���č���T��
	if(ColorJudgement_judgeColor(this->colorJudgement)==BLACK){
		/*
		 * // ���݂̑��s��Ԏ擾���w��
		 * OrderList_nowOrder();
		 * // �擾�������s��ԂŁA���C���g���[�X�̃G�b�W�������擾
		 * �i��L�͖������B���@�m�F�������ʁA�K�v�ȏꍇ�����B�j
		*/

		switch(i)
		{
		case (0):
			OrderList_finishOrder(this->orderList,this->orderNum);
			this->orderNum = OrderList_manualRunning(this->orderList,NONE,NONE,NONE,COMEBACK_STOP_TIME,NONE);
			i++;
			break;
		case (1):
			if (OrderList_checkFinished(this->orderList,this->orderNum)){
				ecrobot_sound_tone(659, 70, 95);
				return TRUE;
			}
			break;
		}

/*
		// ���C�����������瑖�s��~
		OrderList_stop(this->orderList);
		// ���C�����A�̉���炵�ATRUE��Ԃ�
		ecrobot_sound_tone(659, 70, 95);
		return TRUE;
*/
	}
	return FALSE;
}


