/*******************************************************************************
**  �t�@�C����  �FGrayDecision.h
**  �T�v        �F�D�F���m�N���X��`
**  �ڍ�        �F�D�F���m�̔���p�������s���B
*******************************************************************************/

#ifndef _GrayDecision_H_
#define _GrayDecision_H_

#include "Info.h"
#include "ecrobot_interface.h"
#include "device/Timer.h"
#include "device/LightSensor.h"


// �\���̂̒�`
typedef struct GrayDecision
{
	int GrayPassCnt;				// �D�F���m�������Ō�܂Ŏ��s������

	LightSensor *lightSensor;		// ���Z���T�̐ÓI�����N
	int lightget;					// ���Z���T�̒l
	int light_target;				// ���F�̊�l
	int getcount;					// ���F�̊�l�ȉ��̎擾�񐔃J�E���^

	BOOL isInitialized;             // �������t���O
	int forward; 					// �O�i�l
	int turn;						// ����l
	int mode;						// ���s���[�h
	Timer *timer;					// �^�C�}�[

} GrayDecision;


// ���J����
void GrayDecision_init(GrayDecision* this);
void GrayDecision_setTarget(GrayDecision* this, int target);
void GrayDecision_main(GrayDecision* this, Info *info);

#endif /* _GrayDecision_H_ */

