/*******************************************************************************
**  �t�@�C����  �FLineTracer.c
**  �T�v        �F���C���g���[�X�N���X
**  �ڍ�        �F���C���Ɋ֘A���鏈�����`�B
*******************************************************************************/

#include "LineTracer.h"

//static void LineTracer_checDerailment(LineTracer* this, Info* info);

// ����������
void LineTracer_init(LineTracer* this)
{
	this->brightness = 0;
	this->turnDeff1 = 0;
	this->turnDeff2 = 0;
	this->count = 0;
}


/*------------------------------------------------------------------------------
--  �֐���      �FLineTracer_trace
--  �T�v        �F���C���g���[�X���s��
--              �F
--  ����        �Finfo �S���(�R�[�X���A���C���g���[�X�t���O���g�p)
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void LineTracer_trace(LineTracer* this, Info* info)
{
	int calcTurn;

	this->brightness = LightSensor_getBrightness(this->lightSensor);

	// ����ʂ��擾����
	info->settingInfo->target = this->target;
	calcTurn = PidControl_calcTurn(this->pidControl, info->settingInfo, this->brightness);
	if(this->lineEge == LINE_EGE_LEFT)
	{
		// ���G�b�W�̏ꍇ�A����ʂ𔽓]������
		calcTurn *= -1;
	}
	this->turn = calcTurn;

	/*
	display_goto_xy(2, 4);
	display_int(calcTurn, 14);
	display_goto_xy(2, 5);
	display_int(this->target, 14);
	display_update();
	*/
	/*
	if(info->settingInfo->lineTraceFlg == TRUE)
	{
		info->runnerInfo->turn = calcTurn;
	}
	*/

	//LineTracer_checDerailment(this, info);
}

F32 LineTracer_getTurn(LineTracer* this)
{
	return this->turn;
}

void LineTracer_setTarget(LineTracer* this, float target)
{
	this->target = target;
	//ecrobot_sound_tone(659, 100, 95);
}

void LineTracer_setRightEdge(LineTracer* this)
{
	this->lineEge = LINE_EGE_RIGHT;
}

void LineTracer_setLeftEdge(LineTracer* this)
{
	this->lineEge = LINE_EGE_LEFT;
}

int LineTracer_getEdge(LineTracer* this)
{
	return this->lineEge;
}

/*------------------------------------------------------------------------------
--  �֐���      �FLineTracer_checDerailment
--  �T�v        �F�R�[�X����E�����Ă��邩�𔻒f����
--              �F
--  ����        �Finfo ���
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
/*
static void LineTracer_checDerailment(LineTracer* this, Info* info)
{
	BOOL check;

	check = FALSE;

	this->turnDeff1 = this->turnDeff2;
	this->turnDeff2 = info->runnerInfo->turn;

	if(this->turnDeff1 * this->turnDeff2 < 0)
	{
		this->count = 0;
	}
	else
	{
		this->count++;
		if(this->count > 250)
		{
			check = TRUE;
		}
	}

	// �o�h�c���䕔�i�ł̃`�F�b�N��D�悷��
	check = PidControl_checDerailment(this->pidControl);

	info->measureInfo->derailmentFlag = check;
}
*/
