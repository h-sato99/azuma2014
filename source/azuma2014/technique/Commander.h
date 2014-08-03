/*******************************************************************************
**  �t�@�C����  �FCommander.h
**  �T�v        �F�R�}���h���s�N���X��`
**  �ڍ�        �F
*******************************************************************************/

#ifndef _Commander_H_
#define _Commander_H_

#include "Command.h"
#include "Info.h"
#include "technique/Communication.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct Commander
{
	Command *command;
	Communication *communication;
} Commander;

// ���J����
void Commander_init(Commander* this);
void Commander_action(Commander* this, Info *info);

#endif /* _Commander_H_ */
