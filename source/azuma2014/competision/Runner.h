/*******************************************************************************
**  �t�@�C����  �FRunner.h
**  �T�v        �F���s�N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _Runner_H_
#define _Runner_H_

#include "Info.h"
#include "RunnerInfo.h"
#include "CourseInfo.h"
#include "technique/Tail.h"
#include "technique/Wheel.h"
#include "technique/BalanceControl.h"
#include "technique/Dash.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct Runner
{
	Tail *tail;
	Wheel *wheel;
	BalanceControl *balanceControl;
	Dash *dash;
} Runner;

// ���J����
void Runner_init(Runner* this);
void Runner_run(Runner* this, Info* info);

#endif /* _Runner_H_ */
