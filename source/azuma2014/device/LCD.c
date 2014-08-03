/*******************************************************************************
**  �t�@�C����  �FLCD.c
**  �T�v        �F�t���\���N���X
**  �ڍ�        �F�t���\���Ɋւ��鏈�����s���B
*******************************************************************************/

#include "device/LCD.h"

/* �����\���ʒu�Ɋւ���萔 */
#define C_MAX_POINT_X			15		// X���W�F���������i�ő�j
#define C_MIN_POINT_X			0		// X���W�F���������i�ŏ��j
#define C_MAX_POINT_Y			7		// Y���W�F���������i�ő�j
#define C_MIN_POINT_Y			0		// Y���W�F���������i�ŏ��j


static void LCD_SetPointX(LCD* this, int x);
static void LCD_SetPointY(LCD* this, int y);


void LCD_init(LCD* this)
{
	this->pointX = 0;
	this->pointY = 0;
}

/*------------------------------------------------------------------------------
--  �֐���      �FLCD_SetPointX
--  �T�v        �F�����\���ʒu�iX���W�F���������j��ݒ肷��B
--  ����        �Fint			X���W�i0�`15�j
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
static void LCD_SetPointX(LCD* this, int x)
{
	int l_setX = x;

	// �����`�F�b�N
	if (l_setX < C_MIN_POINT_X)
	{
		l_setX = C_MIN_POINT_X;
	}
	// ����`�F�b�N
	if (l_setX > C_MAX_POINT_X)
	{
		l_setX = C_MAX_POINT_X;
	}

	this->pointX = l_setX;
}

/*------------------------------------------------------------------------------
--  �֐���      �FLCD_SetPointY
--  �T�v        �F�����\���ʒu�iY���W�F���������j��ݒ肷��B
--  ����        �Fint			Y���W�i0�`7�j
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
static void LCD_SetPointY(LCD* this, int y)
{
	int l_setY = y;

	// �����E����`�F�b�N
	if (l_setY < C_MIN_POINT_Y)
	{
		l_setY = C_MIN_POINT_Y;
	}
	if (l_setY > C_MAX_POINT_Y)
	{
		l_setY = C_MAX_POINT_Y;
	}

	this->pointY = l_setY;
}

/*------------------------------------------------------------------------------
--  �֐���      �FLCD_SetPointXY
--  �T�v        �F�����\���ʒu�iY���W�F���������j��ݒ肷��B
--  ����        �Fint			Y���W�i0�`7�j
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void LCD_SetPointXY(LCD* this, int x, int y)
{
	LCD_SetPointX(this, x);
	LCD_SetPointY(this, y);
}


/*------------------------------------------------------------------------------
--  �֐���      �FLCD_DisplayStr
--  �T�v        �F�w�蕶�����\������B
--  ����        �Fconst CHAR*	�\�����镶����
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void LCD_DisplayStr(LCD* this, const CHAR* c)
{
	display_goto_xy(this->pointX, this->pointY);
	display_string(c);
	display_update();
}

/*------------------------------------------------------------------------------
--  �֐���      �FLCD_DisplayHex
--  �T�v        �F�w�肳�ꂽ�����l��16�i���ŕ\������B
--              �F�����Ȃ������l��\���������ꍇ�́A���̊֐����g�p���Ă��������B
--  ����        �FU32			�\�����鐮���l
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void LCD_DisplayHex(LCD* this, U32 value)
{
	display_goto_xy(this->pointX, this->pointY);
	display_hex(value, 14);
	display_update();
}

/*------------------------------------------------------------------------------
--  �֐���      �FLCD_DisplayInt
--  �T�v        �F�w�肳�ꂽ�����t�������l��10�i���ŕ\������B
--  ����        �Fint			�\�����鐮���l
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void LCD_DisplayInt(LCD* this, int value)
{
	display_goto_xy(this->pointX, this->pointY);
	display_int(value, 14);
	display_update();
}

/*------------------------------------------------------------------------------
--  �֐���      �FLCD_DisplayStatus
--  �T�v        �F�ȉ��̓��e�Ǝw�肳�ꂽ�������\������B
--              �F�E�V�X�e���^�C�}[msec]
--              �F�E�o�b�e���d��[mV]
--              �F�E���[�^��]�p�x�i�|�[�gA/B/C�j[�x]
--              �F�EA/D�Z���T�f�[�^�i�|�[�gS1/S2/S3/S4�j
--              �F�EBluetooth�ʐM��ԁi1:�ڑ�, 0:�ڑ������j
--              �F�E�����g�Z���T[cm]
--              �F���̊֐��̏����͕��ׂ��������߁A��p�x�i��F500msec�����j��
--              �F�Ăяo���悤�ɂ��Ă��������B
--  ����        �Fconst CHAR*	�\�����镶����
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void LCD_DisplayStatus(const CHAR* msg)
{
	display_clear(0);
	ecrobot_status_monitor(msg);
}

/*------------------------------------------------------------------------------
--  �֐���      �FLCD_DisplayClear
--  �T�v        �F�f�B�X�v���C������������B
--  ����        �F
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void LCD_DisplayClear(LCD* this)
{
	display_clear(0);
	display_update();
}
