/*******************************************************************************
**  �t�@�C����  �FLineComeback.c
**  �T�v        �F
**  �ڍ�        �F
*******************************************************************************/

#include "LineComeback.h"
#define COMEBACK_FORWARD			40		// ���C�����A�p�O�i�l
#define COMEBACK_TURN				100		// ���C�����A�p����l
#define COMEBACK_TURN_STATE			1		// ���C�����A�p������
#define COMEBACK_FINISH_TIME		0		// ���C�����A�p�I������
#define COMEBACK_FINISH_DISTANCE	100		// ���C�����A�p�I������


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
		this->orderNum = OrderList_stop(this->orderList);
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
		// ���C�����������瑖�s��~
		OrderList_stop(this->orderList);
		// ���C�����A�̉���炵�ATRUE��Ԃ�
		ecrobot_sound_tone(659, 70, 95);
		return TRUE;
	}
	return FALSE;
}


