/*******************************************************************************
**  �t�@�C����  �FSeesaw.h
**  �T�v        �F�V�[�\�[�N���X��`
**  �ڍ�        �F�N���X�̌��J�����`����B
*******************************************************************************/

#ifndef _Seesaw_H_
#define _Seesaw_H_

#include "Info.h"
#include "device/GyroSensor.h"
#include "technique/WheelAverage.h"
// ������ێ����邽�߂̍\���̂̒�`
typedef struct Seesaw
{
	//�N���X�p�ϐ�
	GyroSensor *gyroSensor;		//�W���C���Z���T�[�N���X
	WheelAverage *wheelAverage; //WheelAverage�N���X

	//�Ռ����m�p�ϐ�
	unsigned int ImpactLow;		//�Ռ����艺���l
	unsigned int ImpactHight;	//�Ռ��������l
	int forward;		//�O�i�l
	unsigned int RecieveGyro;	//�W���C���Z���T�[�̒l���󂯎��p

	//�ԗւ̒l�擾�p�ϐ�
	int Average;				//���ԗւ̎擾�p
	int StrageAverage;			//�ێ��p���ԗւ̕���
	int NewAverage;				//�ŐV�̕��ϕێ��p

	//���̑��ϐ�
	int SeesawCount;			//��Ԃ̃J�E���g
	int WaitCount;				//Wait�p�J�E���g
	int TailAngle;				//�K���̊p�x
	int LengthTarget;			//�����̖ڕW�l
	int TailMode;				//0�FUp,2�FDown
	int TailTarget;				//�K���̖ڕW�l
	int InfoTail;
	BOOL isFinished;
} Seesaw;

// ���J����
void Seesaw_init(Seesaw* this);					//��������
void Seesaw_action(Seesaw* this, Info *info);	//�V�[�\�[�U��
BOOL Seesaw_checkFinish(Seesaw* this);

#endif /* _Seesaw_H_ */
