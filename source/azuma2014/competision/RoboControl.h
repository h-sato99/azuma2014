/*******************************************************************************
**  �t�@�C����  �FRoboControl.h
**  �T�v        �F
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _RoboControl_H_
#define _RoboControl_H_

//#include "kernel.h"
//#include "kernel_id.h"
//#include "ecrobot_interface.h"
#include "competision/OrderList.h"
#include "competision/Runner.h"

#include "Info.h"

// ������ێ����邽�߂̍\���̂̒�`
typedef struct RoboControl
{
	BOOL isInitialized;
	int currentOrderIndex;
//	int finishTime;
//	int finishValue;
	int time;
	int value;
	OrderList *orderList;
	Runner *runner;
} RoboControl;

// ���J����
void RoboControl_init(RoboControl* this);
void RoboControl_control(RoboControl* this, Info* info);

#endif /* _RoboControl_H_ */
