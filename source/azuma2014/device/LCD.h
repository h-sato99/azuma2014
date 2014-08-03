/*******************************************************************************
**  �t�@�C����  �FLCD.h
**  �T�v        �F�t���\���N���X�i�w�b�_�t�@�C���j
**  �ڍ�        �F�t���\���Ɋւ��鏈�����`�B
*******************************************************************************/

#ifndef _LCD_H_
#define _LCD_H_

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct LCD
{
	int pointX;
	int pointY;
} LCD;

void LCD_init(LCD* this);

void LCD_SetPointXY(LCD* this, int x, int y);

void LCD_DisplayStr(LCD* this, const CHAR* c);

void LCD_DisplayHex(LCD* this, U32 value);

void LCD_DisplayInt(LCD* this, int value);

void LCD_DisplayStatus( const CHAR* msg);

void LCD_DisplayClear(LCD* this);

#endif /* _LCD_H_ */
