/*******************************************************************************
**  �t�@�C����  �FDash.h
**  �T�v        �F
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _Dash_H_
#define _Dash_H_

#include "Info.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct Dash
{
	int counter; 							// �ėp�J�E���^
} Dash;

// ���J����
void Dash_init(Dash* this);
void Dash_action(Dash* this,Info *info , int upvol, int uplim);

#endif /* _Dash_H_ */
