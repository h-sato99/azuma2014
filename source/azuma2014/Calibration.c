/*******************************************************************************
**  �t�@�C����  �FCalibration.c
**  �T�v        �F�L�����u���[�V�����N���X
**  �ڍ�        �F�L�����u���[�V�����Ɋւ��鏈�����s���B
*******************************************************************************/

#include "Calibration.h" /* �L�����u���[�V���� �w�b�_�t�@�C�� */

#define C_CALIBRATE_COUNT 1000  //���Z���T�l�擾��

static void Calibration_SetBlack(Calibration* this);
static void Calibration_SetWhite(Calibration* this);
static void Calibration_SetGray(Calibration* this);


/*------------------------------------------------------------------------------
--  �֐���      �FCalibration_MeasureLight
--  �T�v        �F��������s���B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�F�擾�\����
------------------------------------------------------------------------------*/
void Calibration_MeasureLight(Calibration* this)
{
	// �L�����u���[�V�����J�n�T�E���h
	ecrobot_sound_tone(440, 100, 95);
	/* ���F�擾�����J�n */
	// �^�b�`�Z���T���������܂őҋ@
	while(1)
	{
		// LCD�ɍ��F�擾�������ł������Ƃ�\��
		// EXIT�{�^�����������ꂽ��D�F�l�ɓK���Ȓl��ݒ肵�A�����𔲂���
		if(ecrobot_is_ENTER_button_pressed())
		{
			this -> gray = 550;
			return;
		}
		else
		{
			if(TouchSensor_isPressed(this->touchSensor))
			{
				systick_wait_ms(1000);
				break;
			}
		}
	}
	// ���F���擾����
	Calibration_SetBlack(this);
	// ���F�擾�����T�E���h
	ecrobot_sound_tone(554, 100, 95);
	
	/* ���F�擾�����J�n */
	// �^�b�`�Z���T���������܂őҋ@
	while(1)
	{
		// LCD�ɔ��F�擾�������ł������Ƃ�\��
		// EXIT�{�^�����������ꂽ��D�F�l�ɓK���Ȓl��ݒ肵�A�����𔲂���
		if(ecrobot_is_ENTER_button_pressed())
		{
			this -> gray = 550;
			return;
		}
		else
		{
			if(TouchSensor_isPressed(this->touchSensor))
			{
				systick_wait_ms(1000);
				break;
			}
		}
	}
	// ���F���擾����
	Calibration_SetWhite(this);
	// ���F�擾�����T�E���h
	ecrobot_sound_tone(659, 100, 95);
	
	/* �D�F�擾�����J�n */
	// �^�b�`�Z���T���������܂őҋ@
	while(1)
	{
		// LCD�ɊD�F�擾�������ł������Ƃ�\��
		// EXIT�{�^�����������ꂽ��D�F�l�ɓK���Ȓl��ݒ肵�A�����𔲂���
		if(ecrobot_is_ENTER_button_pressed())
		{
			this -> gray = 550;
			return;
		}
		else
		{
			if(TouchSensor_isPressed(this->touchSensor))
			{
				systick_wait_ms(1000);
				break;
			}
		}
	}
	// �D�F���擾����
	Calibration_SetGray(this);
	// �D�F�擾�����T�E���h
	ecrobot_sound_tone(880, 200, 95);
	
	LCD_DisplayClear(this->lcd);
		
	// �擾���ʕ\��
	LCD_SetPointXY(this->lcd, 3, 0);
	LCD_DisplayInt(this->lcd, this->black);
	
	LCD_SetPointXY(this->lcd, 3, 1);
	LCD_DisplayInt(this->lcd, this->white);
	
	LCD_SetPointXY(this->lcd, 3, 2);
	LCD_DisplayInt(this->lcd, this->gray);
}

/*------------------------------------------------------------------------------
--  �֐���      �FCalibration_GetBlack
--  �T�v        �F���F���擾����B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �Fint			���F�擾�l�i10�r�b�gA/D�R���o�[�^�j
------------------------------------------------------------------------------*/
static void Calibration_SetBlack(Calibration* this)
{
	unsigned int i;
	unsigned long l_iCurBlack;				// ���F�擾�v�Z�l
	
	// ���F�擾�v�Z�l������
	l_iCurBlack = 0;
	
	// ���F���擾����
	for (i = 0; i < C_CALIBRATE_COUNT; i++) {
		// C_CALIBRATE_COUNT��A���l���擾
		l_iCurBlack = l_iCurBlack + LightSensor_getBrightness(this->lightSensor);
	}
	
	// �擾�������l�̕��ς����߂�
	l_iCurBlack = l_iCurBlack / C_CALIBRATE_COUNT;
	
	this->black = l_iCurBlack;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCalibration_GetWhite
--  �T�v        �F���F���擾����B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �Fint		���F�擾�l�i10�r�b�gA/D�R���o�[�^�j
------------------------------------------------------------------------------*/
static void Calibration_SetWhite(Calibration* this)
{
	unsigned int i;
	unsigned long l_iCurWhite;				// ���F�擾�v�Z�l
	
	// ���F�擾�v�Z�l������
	l_iCurWhite = 0;
	
	// ���F���擾����
	for (i = 0; i < C_CALIBRATE_COUNT; i++) {
		// C_CALIBRATE_COUNT��A���l���擾
		l_iCurWhite = l_iCurWhite + LightSensor_getBrightness(this->lightSensor);
	}
	
	// �擾�������l�̕��ς����߂�
	l_iCurWhite = l_iCurWhite / C_CALIBRATE_COUNT;
	
	this->white = l_iCurWhite;
}

/*------------------------------------------------------------------------------
--  �֐���      �FCalibration_GetGray
--  �T�v        �F�D�F���擾����B
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �Fint		�D�F�擾�l�i10�r�b�gA/D�R���o�[�^�j
------------------------------------------------------------------------------*/
static void Calibration_SetGray(Calibration* this)
{
	unsigned int i;
	unsigned long l_iCurGray;				// �D�F�擾�v�Z�l
	
	// �D�F�擾�v�Z�l������
	l_iCurGray = 0;
	
	// �D�F���擾����
	for (i = 0; i < C_CALIBRATE_COUNT; i++) {
		// C_CALIBRATE_COUNT��A�D�l���擾
		l_iCurGray = l_iCurGray + LightSensor_getBrightness(this->lightSensor);
	}
	
	// �擾�����D�l�̕��ς����߂�
	l_iCurGray = l_iCurGray / C_CALIBRATE_COUNT;
	
	this->gray = l_iCurGray;
}
