/*******************************************************************************
**  �t�@�C����  �FLineComeback.c
**  �T�v        �F
**  �ڍ�        �F
*******************************************************************************/

#include "LineComeback.h"
#define NONE						0
#define COMEBACK_FORWARD			50		// ���C�����A�p�O�i�l
#define COMEBACK_TURN				100		// ���C�����A�p����l
#define COMEBACK_TURN_STATE			1		// ���C�����A�p������
#define COMEBACK_FINISH_TIME		0		// ���C�����A�p�I������
#define COMEBACK_FINISH_DISTANCE	100		// ���C�����A�p�I������
#define COMEBACK_STOP_TIME			2000	// ���C�����A�p�I������

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
			return FALSE;
		}
		this->mode = TURNRIGHT;
		return FALSE;

	case TURNLEFT:
		// ���ɐ��񂷂�
		if (OrderList_checkFinished(this->orderList,this->orderNum)){
			this->orderNum = OrderList_turnOnSpotLeft(
				this->orderList,
				COMEBACK_FORWARD,
				COMEBACK_TURN,
				COMEBACK_FINISH_TIME,
				COMEBACK_FINISH_DISTANCE);
			ecrobot_sound_tone(659, 70, 95);
			LCD_SetPointXY(this->lcd, 3, 1);
			LCD_DisplayInt(this->lcd, this->orderNum);
			this->mode = TURNRIGHT;
		}
		break;

	case TURNRIGHT:
		// �E�ɐ��񂷂�
		if (OrderList_checkFinished(this->orderList,this->orderNum)){
			this->orderNum = OrderList_turnOnSpotRight(
				this->orderList,
				COMEBACK_FORWARD,
				COMEBACK_TURN,
				COMEBACK_FINISH_TIME,
				COMEBACK_FINISH_DISTANCE);
			ecrobot_sound_tone(659, 70, 95);
			LCD_SetPointXY(this->lcd, 3, 2);
			LCD_DisplayInt(this->lcd, this->orderNum);
			this->mode = TURNLEFT;
		}
		break;

	case LAST:
		// �F����ō����擾������A�Ō�̏������I���܂őҋ@
		if (OrderList_checkFinished(this->orderList,this->orderNum)){
			ecrobot_sound_tone(400, 70, 95);
			LCD_SetPointXY(this->lcd, 3, 3);
			LCD_DisplayInt(this->lcd, this->orderNum);
			return TRUE;
		}
		return FALSE;
	}

	// �F������g���č���T��
	if(ColorJudgement_judgeColor(this->colorJudgement)){
		OrderList_finishOrder(this->orderList,this->orderNum);
		this->orderNum = OrderList_manualRunning(this->orderList,NONE,NONE,NONE,COMEBACK_STOP_TIME,NONE);
		this->mode = LAST;
		return FALSE;
	}
	return FALSE;
}

