///*******************************************************************************
//**  �t�@�C����  �FSeesaw.c
//**  �T�v        �F�V�[�\�[�N���X
//**  �ڍ�        �F
//*******************************************************************************/
//
//#include "Seesaw.h"
//
//#define ForwardLow 60;
//#define ReverceLow -30;
//#define SetGyroLow 500;
//#define SetGyroHigh 700;
//#define ConstNumberZero 0;
//#define ConstNumberOne 1;
//#define ConstNumberTen 10;
//
///*------------------------------------------------------------------------------
//--  �֐���      �FSeesaw_init
//--  �T�v        �F�ϐ��̏�����
//--  ����        �F�Ȃ�
//--  �߂�l      �F�Ȃ�
//------------------------------------------------------------------------------*/
//void Seesaw_init(Seesaw* this)
//{
//	this->SeesawCount 	 = 0;		//�V�[�\�[�̂ӂ�܂�����J�E���g
//	this->ImpactLow 	 = ConstNumberZero;		//�Ռ��̉����l
//	this->ImpactHight 	 = ConstNumberZero;		//�Ռ��̏���l
//	this->forward 		 = ConstNumberZero;		//�O�i�l
//	this->WaitCount		 = ConstNumberZero;		//�ҋ@�p�ϐ�
//	this->isFinished =FALSE;
//}
//
///*------------------------------------------------------------------------------
//--  �֐���      �FImpactDetection
//--  �T�v        �F�Ռ�����
//--              �F
//--  ����        �FImpactLow �Ռ����艺���l,ImpactHigh �Ռ��������l
//--  �߂�l      �F�Ȃ�
//------------------------------------------------------------------------------*/
//void ImpactDetection(Seesaw *this)
//{
//	this->RecieveGyro = GyroSensor_getAngularVelocity(this->gyroSensor);
//
//	//ImpactLow�ɏՌ��̉����l(��菭�������l)�AImpactHight�ɏՌ��̏���l(��菭���Ⴂ�l)���Z�b�g����
//	if (this->ImpactLow >= this->RecieveGyro || this->RecieveGyro >= this->ImpactHight)
//	{
//		//�ҋ@�p�ϐ�������
//		this->WaitCount = ConstNumberZero;
//		//�J�E���g���C���N�������g
//		this->SeesawCount++;
//	}
//}
///*------------------------------------------------------------------------------
//--  �֐���      �FTailUp
//--  �T�v        �F��苗���i�ނɂ�ĐK�������������߂���
//--				�FTailMode:0���K�����グ��
//--              �FTailMode:1���K����������
//--              �F
//--  ����        �Finfo  �S���
//--  �߂�l      �F�Ȃ�
//------------------------------------------------------------------------------*/
//void TailUpDown(Seesaw *this){
//	//�ړ����������ȏ�ɂȂ�����K�����グ��
//	if(this->Average - this->NewAverage >= 2
//		|| this->Average - this->NewAverage <= -2){
//		//�K���̌X�������ȏ�̏ꍇ�K���������グ��
//		if(this->TailMode == 0 && this->TailAngle > this->TailTarget){
//			this->TailAngle -= ConstNumberTen;
//			this->NewAverage = this->Average;
//		}else if(this->TailMode == 1 && this->TailAngle < this->TailTarget){
//			this->TailAngle += ConstNumberTen;
//			this->NewAverage = this->Average;
//		}
//	}
//}
///*------------------------------------------------------------------------------
//--  �֐���      �FWait
//--  �T�v        �FWait����B
//--              �F4msec�Ɉ��Ă΂��̂ŁA250��v1�bWait����B
//--              �F
//--  ����        �F�Ȃ�
//--  �߂�l      �F�Ȃ�
//------------------------------------------------------------------------------*/
//void Wait(Seesaw *this)
//{
//	this->WaitCount++;
//	this->forward = ConstNumberZero;
//	if(this->WaitCount >= 250){
//		this->SeesawCount++;
//	}
//}
//
//void Seesaw_action(Seesaw* this, Info *info)
//{
//	switch(this->SeesawCount)
//	{
//	//***************************************
//	//case0:
//	//		�V�[�\�[�ɂԂ��������Ƃ����m
//	//***************************************
//	case 0:
//		// �ً}��~���I�t�ɂ���
//		info->runnerInfo->emergencyStopCheckFlag = FALSE;
//		//�O�i�l�A�Ռ�����l��ݒ�
//		this->forward = 10;
//		this->ImpactLow = SetGyroLow;
//		this->ImpactHight = SetGyroHigh;
//		//�ݒ肵���Ռ�����l�����ɏՌ�����
//		ImpactDetection(this);
//		this->WaitCount = ConstNumberZero;
//		break;
//	//***************************************
//	//case1:
//	//		�o�b�N����
//	//***************************************
//	case 1:
//		this->forward = -20;
//		this->StrageAverage = WheelAverage_action(this->wheelAverage);
//		this->SeesawCount++;
//		info->runnerInfo->gyroOffset = info->runnerInfo->gyroOffset - 5;
//		info->runnerInfo->turn = 0;
//		info->settingInfo->lineTraceFlg = FALSE;
//		ecrobot_sound_tone(400, 100, 95);
//		break;
//	//***************************************
//	//case2:
//	//		�_�b�V�����ăV�[�\�[�ɏ��グ��
//	//***************************************
//	case 2:
//		this->Average = WheelAverage_action(this->wheelAverage);
//		if(this->Average - this->StrageAverage < -80)
//		{
//			this->StrageAverage = WheelAverage_action(this->wheelAverage);
//			this->forward = 50;
//			info->runnerInfo->gyroOffset = info->runnerInfo->gyroOffset + 5;
//			this->SeesawCount++;
//		}
//		break;
//	//***************************************
//	//case3:
//	//		�z�C�[�����ϒl�̊���擾
//	//***************************************
//	case 3:
//		this->Average = WheelAverage_action(this->wheelAverage);
//		if(this->Average - this->StrageAverage >= 100)
//		{
//			this->StrageAverage = WheelAverage_action(this->wheelAverage);
//			this->SeesawCount++;
//		}
//		break;
//
//	//***************************************
//	//case4:
//	//		�V�[�\�[�V���O��
//	//***************************************
//	case 4:
//		this->forward = 20;
//		info->runnerInfo->turn = -1;
//		this->Average = WheelAverage_action(this->wheelAverage);
//		if(this->Average - this->StrageAverage >= 450)
//		{
//			this->SeesawCount++;
//		}
//		break;
//	//***************************************
//	//case5:
//	//		��~����1�b�ҋ@
//	//***************************************
//	case 5:
//		this->forward = 0;
//		info->runnerInfo->turn = 0;
//		Wait(this);
//		break;
//	//***************************************
//	//case6:
//	//		�z�C�[�����ϒl�̊���擾
//	//***************************************
//	case 6:
//		this->StrageAverage = WheelAverage_action(this->wheelAverage);
//		this->SeesawCount++;
//		ecrobot_sound_tone(500, 100, 95);
//		break;
//	//***************************************
//	//case7:
//	//		�o�b�N
//	//***************************************
//	case 7:
//		this->forward = -30;
//		this->Average = WheelAverage_action(this->wheelAverage);
//		if(this->Average - this->StrageAverage <= -300)
//		{
//			this->SeesawCount++;
//		}
//		break;
//	//***************************************
//	//case8:
//	//		��~����1�b�ҋ@
//	//***************************************
//	case 8:
//		this->forward = 0;
//		Wait(this);
//		break;
//	//***************************************
//	//case9:
//	//		�z�C�[�����ϒl�̊���擾
//	//***************************************
//	case 9:
//		this->StrageAverage = WheelAverage_action(this->wheelAverage);
//		this->SeesawCount++;
//		ecrobot_sound_tone(700, 100, 95);
//		break;
//	//***************************************
//	//case10:
//	//		�V�[�\�[�_�u�������̂܂ܑO�i
//	//***************************************
//	case 10:
//		this->forward = 20;
//		info->runnerInfo->turn = -1;
//		this->Average = WheelAverage_action(this->wheelAverage);
//		if(this->Average - this->StrageAverage > 500)
//		{
//			this->SeesawCount++;
//		}
//		break;
//	//***************************************
//	//default:
//	//		�V�[�\�[�̏I��
//	//***************************************
//	default:
//		info->runnerInfo->emergencyStopCheckFlag = TRUE;
//		info->settingInfo->lineTraceFlg = TRUE;
//		this->isFinished =TRUE;
//	}
//
//	// �O�i�l�𑖍s���ɓn��
//	info->runnerInfo->forward = this->forward;
//}
//
//BOOL Seesaw_checkFinish(Seesaw* this)
//{
//	return this->isFinished;
//}
//
///*------------------------------------------------------------------------------
//--  �֐���      �FSeesaw_action
//--  �T�v        �F�V�[�\�[�p�̏��������s����
//--              �Fcase0�`case1:  �V�[�\�[���グ
//--              �Fcase2�`case5:  �V�[�\�[�V���O��
//--              �Fcase6�`case9:  �V�[�\�[�_�u��
//--              �Fcase10�`case11:�V�[�\�[����~���
//--  ����        �Finfo  �S���
//--  �߂�l      �F�Ȃ�
//------------------------------------------------------------------------------*/
//void Seesaw_action_bk(Seesaw* this, Info *info)
//{
//	switch(this->SeesawCount)
//	{
//	//***************************************
//	//case0:
//	//		�V�[�\�[�ɏ��グ�����Ƃ����m
//	//***************************************
//	case 0:
//		//�O�i�l�A�Ռ�����l��ݒ�
//		this->forward = ForwardLow;
//		this->ImpactLow = SetGyroLow;
//		this->ImpactHight = SetGyroHigh;
//		//�ݒ肵���Ռ�����l�����ɏՌ�����
//		ImpactDetection(this);
//		this->WaitCount = ConstNumberZero;
//		break;
//	//***************************************
//	//case1:
//	//		1�b�ҋ@
//	//***************************************
//	case 1:
//		this->forward = 10;
//		this->WaitCount++;
//		if(this->WaitCount >= 500){
//			this->SeesawCount++;
//		}
//		break;
//
//	//***************************************
//	//case2:
//	//		�z�C�[���̒l���擾���A���ς�ϐ��Ɋi�[
//	//		�K�������낷
//	//***************************************
//	case 2:
//		this->forward = ForwardLow;
//		//�z�C�[���̒l�擾�A���ϒl�̌v�Z
//		this->StrageAverage = WheelAverage_action(this->wheelAverage);
//		//�K���̊p�x�𒲐�
//		this->TailAngle = 120;
//		info->runnerInfo->balanceFlag = FALSE;
//		//���̏�����
//		this->SeesawCount++;
//		this->WaitCount = ConstNumberZero;
//		break;
//	case 3:
//		Wait(this);
//		break;
//	case 4:
//	//***************************************
//	//case3:
//	//		���ԗւ̕��ς̍����擾
//	//		�ŐV�̎ԗ֕��ςƕێ��p�ԗ֕��ς̍������ȏ�ɂȂ�܂őO�i
//	//***************************************
//		this->forward = 30;
//		this->SeesawCount++;
//	case 5:
//	//***************************************
//	//case4:
//	//		���ԗւ̕��ς̍����擾
//	//		���s�̂���苗���i�ނ��ƂɐK���𒲐�
//	//***************************************
//		display_goto_xy(1, 1);
//		display_int(this->SeesawCount, 14);
//		display_update();
//		display_goto_xy(1, 2);
//		display_int(this->StrageAverage, 14);
//		display_update();
//		display_goto_xy(1, 3);
//		display_int(this->Average, 14);
//		display_update();
//		//�z�C�[���̒l�擾�A���ϒl�̌v�Z
//		this->Average = WheelAverage_action(this->wheelAverage);
//		this->TailMode = ConstNumberZero;
//		//this->LengthTarget = 1000;
//		if(this->Average - this->StrageAverage >= 550){
//			this->TailAngle = 50;
//			this->WaitCount = ConstNumberZero;
//			this->SeesawCount++;
//		}else if (this->Average - this->StrageAverage >= 500){
//			this->TailAngle = 60;
//		}else if (this->Average - this->StrageAverage >= 450){
//			this->TailAngle = 80;
//		}
//		break;
//	case 6:
//	//***************************************
//	//case5:
//	//		1�b�ҋ@
//	//***************************************
//		Wait(this);
//		break;
//	case 7:
//	//***************************************
//	//case6:
//	//		���ԗւ̕��ς̍����擾
//	//		���s�̂���苗���i�ނ��ƂɐK���𒲐�
//	//***************************************
//		//�z�C�[���̒l�擾�A���ϒl�̌v�Z
//		this->Average = WheelAverage_action(this->wheelAverage);
//		this->forward =  ReverceLow;
//		this->TailMode = ConstNumberOne;
//		this->TailAngle = 50;
//		if (this->Average - this->StrageAverage <= 320){
//			this->TailAngle = 120;
//			this->WaitCount = ConstNumberZero;
//			ecrobot_sound_tone(659, 100, 95);
//			this->SeesawCount++;
//		}else if(this->Average - this->StrageAverage <= 400){
//			this->TailAngle = 80;
//		}else if(this->Average - this->StrageAverage <= 500){
//			this->TailAngle = 60;
//		}else if(this->Average - this->StrageAverage <= 550){
//			this->TailAngle = 50;
//		}
//		break;
//
//	case 8:
//	//***************************************
//	//case7:
//	//		1�b�ҋ@
//	//***************************************
//		Wait(this);
//		break;
//	case 9:
//	//***************************************
//	//case8:
//	//		���ԗւ̕��ς̍����擾
//	//		���s�̂���苗���i�ނ��ƂɐK���𒲐�
//	//***************************************
//		//�z�C�[���̒l�擾�A���ϒl�̌v�Z
//		this->Average = WheelAverage_action(this->wheelAverage);
//		this->forward = 30;
//		this->TailMode = ConstNumberZero;
//		this->TailTarget = 50;
//		//�ŐV�̎ԗ֕��ςƕێ��p�ԗ֕��ς̍������ȏ�ɂȂ�܂őO�i
//		if(this->Average - this->StrageAverage >= 600){
//			this->TailAngle = 40;
//			this->WaitCount = ConstNumberZero;
//			this->NewAverage = this->Average;
//			this->SeesawCount++;
//		}else if (this->Average - this->StrageAverage >= 550){
//			this->TailAngle = 60;
//		}else if (this->Average - this->StrageAverage >= 450){
//			this->TailAngle = 80;
//		}
//		break;
//	case 10:
//	//***************************************
//	//case9:
//	//		1�b�ҋ@
//	//***************************************
//		Wait(this);
//		break;
//	//***************************************
//	//case10:
//	//		�V�[�\�[�ɏ��グ�����Ƃ����m
//	//***************************************
//	case 11:
//		//�O�i�l�A�Ռ�����l��ݒ�
//		this->forward = ForwardLow;
//		this->ImpactLow = SetGyroLow;
//		this->ImpactHight = SetGyroHigh;
//		//�ݒ肵���Ռ�����l�����ɏՌ�����
//		ImpactDetection(this);
//		break;
//	//***************************************
//	//case11:
//	//		1�b�ҋ@
//	//***************************************
//	case 12:
//		Wait(this);
//		break;
//	default:
//	//***************************************
//	//Defaut:
//	//		Return
//	//***************************************
//		break;
//	}
//	// �O�i�l�𑖍s���ɓn��
//	info->runnerInfo->forward = this->forward;
//	info->runnerInfo->tail = this->TailAngle;
//}
//
