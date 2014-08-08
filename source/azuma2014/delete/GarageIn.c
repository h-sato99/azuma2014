///*******************************************************************************
//**  �t�@�C����  �FGarageIn.c
//**  �T�v        �F�K���[�W�C���N���X
//**  �ڍ�        �F
//*******************************************************************************/
//
//#include "GarageIn.h"
//
//#define STOP     	    	0 		// ��~
//#define LOW     	    	20 		// �ᑬ
//#define TAIL_ANGL			90		// �K���̊p�x
//#define DISTANCE_OF_SEESAW 	720  	// �V�[�\�[����̈ړ�����
//#define DISTANCE_OF_LOOKUP 	2900  	// ���b�N�A�b�v�Q�[�g����̈ړ�����
//
//void GrageIn_init(GarageIn* this)
//{
//	this->isInitialized	= FALSE; 					// �������t���O
//	this->forward		= LOW;   					// �O�i�l
//	this->turn			= -1;						// ����l
//	this->tAngle		= TAIL_ANGL;				// �K���p�x
//}
//
///*------------------------------------------------------------------------------
//--  �֐���      �FGarageIn_action
//--  �T�v        �F�K���[�W�C���p�̏��������s����
//--              �F
//--  ����        �Finfo  �S���
//--  �߂�l      �F�Ȃ�
//------------------------------------------------------------------------------*/
//void GarageIn_action(GarageIn* this, Info* info)
//{
//	this->turn = 0;
//	this->tAngle = TAIL_ANGL;
//	this->forward = LOW;
//
//	// ������(�X�^�[�g���Ԃ̎擾)
//	if(! this->isInitialized)
//	{
//		// ���[�^�̒l�������Z�b�g
//		Distance_set(this->distance, info->measureInfo);
//		// �������ςɂ���
//		this->isInitialized = TRUE;
//	}
//
//
//	// �A�E�g�R�[�X�̏ꍇ
//	if (info->settingInfo->courseType == 0)
//	{
//		// �V�[�\�[����K���[�W�C���܂Ői�񂾏ꍇ
//		if (Distance_check(this->distance, info->measureInfo, DISTANCE_OF_SEESAW))
//		{
//			info->runnerInfo->turn = this->turn;
//			info->runnerInfo->tail = this->tAngle;
//			info->runnerInfo->balanceFlag = FALSE;
//			info->settingInfo->lineTraceFlg = FALSE;
//			this->forward = STOP;
//		}
//	}
//	// �C���R�[�X�̏ꍇ
//	else
//	{
//		// ���b�N�A�b�v�Q�[�g����K���[�W�C���܂Ői�񂾏ꍇ
//		if (Distance_check(this->distance, info->measureInfo, DISTANCE_OF_LOOKUP))
//		{
//			info->runnerInfo->turn = this->turn;
//			info->runnerInfo->tail = this->tAngle;
//			info->runnerInfo->balanceFlag = FALSE;
//			info->settingInfo->lineTraceFlg = FALSE;
//			this->forward = STOP;
//		}
//	}
//	info->runnerInfo->forward = this->forward;
//}
