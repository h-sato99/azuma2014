/*******************************************************************************
**  �t�@�C����  �Fmodel_impl.c
**  �T�v        �F���f������
**  �ڍ�        �F����̃N���X�Ɏ��܂�Ȃ��������s��
*******************************************************************************/

#include <string.h>

#include "device/Bluetooth.h"
#include "device/Logger.h"
#include "device/Motor.h"
#include "device/TouchSensor.h"
#include "device/GyroSensor.h"
#include "device/LightSensor.h"
#include "device/SonarSensor.h"
#include "device/LCD.h"
#include "device/Timer.h"
#include "technique/BalanceControl.h"
#include "technique/PidControl.h"
#include "technique/Tail.h"
#include "technique/Wheel.h"
#include "technique/Communication.h"
#include "technique/Commander.h"
#include "technique/Distance.h"
#include "technique/Dash.h"
#include "competision/BasicStage.h"
#include "competision/Competision.h"
#include "competision/LineTracer.h"
#include "competision/Runner.h"
#include "competision/Strategy.h"

#include "Info.h"

#include "Calibration.h"

#include "Command.h"
#include "CheckStart.h"

//2014�N�x
#include "competision/OrderList.h"
#include "competision/RoboControl.h"
#include "competision/Jump.h"
#include "competision/Mogul.h"
#include "competision/PendingArea.h"
#include "competision/Course.h"
#include "competision/FigureL.h"
#include "technique/DrivingWheel.h"
#include "technique/FrontWheel.h"
#include "technique/LineChange.h"
#include "technique/TrialDecision.h"
#include "technique/BumpDecision.h"

#include "competision/OrderTest.h"

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// �萔
// �K���̊p�x(100�}5�Ƃ���)
#define C_TAIL_ANGL_DEFAULT     105
#define C_TARGET 550
#define C_COURSE 0
#define C_COURSE_IN 1
#define C_COURSE_OUT 0

// �I�u�W�F�N�g��ÓI�Ɋm�ۂ���
Bluetooth bluetooth;
Logger logger;
Motor leftMotor;
Motor rightMotor;
Motor tailMotor;
TouchSensor touchSensor;
CheckStart checkStart;
GyroSensor gyroSensor;
LightSensor lightSensor;
SonarSensor sonarSensor;
Timer grayDecisionTimer;
Timer lookUpGateTimer;
Command command;
LCD lcd;
Calibration calibration;
Info info;
MeasureInfo courseInfo;
SettingInfo settingInfo;
RunnerInfo runnerInfo;
// �v�f�Z�p�I�u�W�F�N�g
BalanceControl balanceControl;
PidControl pidControl;
Tail tail;
Wheel wheel;
Communication communication;
Commander commander;
Distance distance;
Distance garageInDistance;
Dash dash;
Distance strategyDistance;
Distance lookupGageDistance;
Distance basicStageDistance;

// ���Z�I�u�W�F�N�g
Competision competision;
BasicStage basicStage;
LineTracer lineTracer;
Runner runner;
Strategy strategy;

// 2014�N�x
OrderList orderList;
RoboControl roboControl;
DrivingWheel drivingWheel;
FrontWheel frontWheel;
Motor frontMotor;
LineChange lineChange;
TrialDecision trialDicision;
BumpDecision bumpDecision;
Jump jump;
Mogul mogul;
Course course;
PendingArea pendingArea;
FigureL figureL;

OrderTest orderTest;

// Bluetooth���M�p�Ɋe���i�̏������H����
void test_data_send()
{
	char buf[BT_MAX_RX_BUF_SIZE];
	char* bufPos = &buf;
	int data = 100;
	int len;
	int bufLen = 0;
	int time = systick_get_ms();
	int pidP = info.settingInfo->pidP * 100;
	int pidI = info.settingInfo->pidI * 100;
	int pidD = info.settingInfo->pidD * 100;
	int fP = pidControl.f_p * 100;
	int fI = pidControl.f_i * 100;
	int fD = pidControl.f_d * 100;
	int target = lineTracer.target;
	int brightness = lineTracer.brightness;
	int turn = LineTracer_getTurn(&lineTracer);
	char code[12] = "azumaTest-->";

	len = sizeof(code);
	memcpy(bufPos, code, len);
	bufPos += len;
	bufLen += len;

	/*
	len = sizeof(time);
	memcpy(bufPos, time, len);
	bufPos += len;
	bufLen += len;
	*/

	len = sizeof(data);
	memcpy(bufPos, &data, len);
	bufPos += len;
	bufLen += len;

	len = sizeof(pidP);
	memcpy(bufPos, &pidP, len);
	bufPos += len;
	bufLen += len;

	len = sizeof(pidI);
	memcpy(bufPos, &pidI, len);
	bufPos += len;
	bufLen += len;

	len = sizeof(pidD);
	memcpy(bufPos, &pidD, len);
	bufPos += len;
	bufLen += len;

	len = sizeof(target);
	memcpy(bufPos, &target, len);
	bufPos += len;
	bufLen += len;

	len = sizeof(brightness);
	memcpy(bufPos, &brightness, len);
	bufPos += len;
	bufLen += len;

	len = sizeof(fP);
	memcpy(bufPos, &fP, len);
	bufPos += len;
	bufLen += len;

	len = sizeof(fI);
	memcpy(bufPos, &fI, len);
	bufPos += len;
	bufLen += len;

	len = sizeof(fD);
	memcpy(bufPos, &fD, len);
	bufPos += len;
	bufLen += len;

	len = sizeof(turn);
	memcpy(bufPos, &turn, len);
	bufPos += len;
	bufLen += len;

	Communication_setSendData(&communication, buf, bufLen);
}
//

// �^�X�N�̐錾
DeclareCounter(SysTimerCnt);
DeclareTask(TaskInit);
DeclareTask(TaskMain);
DeclareTask(TaskBuletooth);

// �f�o�C�X�������p�t�b�N�֐�
// ���̊֐���nxtOSEK�N�����Ɏ��s����܂��B
void ecrobot_device_initialize()
{
	// �Z���T�A���[�^�Ȃǂ̊e�f�o�C�X�̏������֐���
	// �����Ŏ������邱�Ƃ��ł��܂�
	// �ˁ@���Z���T�ԐFLED��ON�ɂ���
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
	SonarSensor_init(&sonarSensor, NXT_PORT_S2);
}

// �f�o�C�X�I���p�t�b�N�֐�
// ���̊֐���STOP�܂���EXIT�{�^���������ꂽ���Ɏ��s����܂��B
void ecrobot_device_terminate()
{
	// �Z���T�A���[�^�Ȃǂ̊e�f�o�C�X�̏I���֐���
	// �����Ŏ������邱�Ƃ��ł��܂��B
	// �ˁ@���Z���T�ԐFLED��OFF�ɂ���
	ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
	Bluetooth_terminate(&bluetooth);
	SonarSensor_term(&sonarSensor);
}

// 1msec�������荞��(ISR�J�e�S��2)����N������郆�[�U�[�p�t�b�N�֐�
void user_1ms_isr_type2(void)
{
	// �J�E���^��Increment����
	SignalCounter(SysTimerCnt);
}

TASK(TaskInit)
{
	// �I�u�W�F�N�g�Ԃ̃����N���\�z����
	checkStart.touchSensor = &touchSensor;
	checkStart.tail = &tail;
	checkStart.communication = &communication;
	calibration.lcd = &lcd;
	calibration.touchSensor = &touchSensor;
	calibration.lightSensor = &lightSensor;
	info.measureInfo = &courseInfo;
	info.runnerInfo = &runnerInfo;
	info.settingInfo = &settingInfo;
	// �v�f�Z�p�I�u�W�F�N�g
	balanceControl.gyroSensor = &gyroSensor;
	balanceControl.wheel = &wheel;
	balanceControl.distance = &distance;
	tail.tailMotor = &tailMotor;
	wheel.leftMotor = &leftMotor;
	wheel.rightMotor = &rightMotor;
	communication.bluetooth = &bluetooth;
	communication.logger = &logger;
	communication.command = &command;
	commander.command = &command;
	commander.communication = &communication;
	commander.orderList = &orderList;
	// ���Z�I�u�W�F�N�g
	competision.lineTracer = &lineTracer;
	competision.strategy = &strategy;
	competision.runner = &runner;
	lineTracer.lightSensor = &lightSensor;
	lineTracer.pidControl = &pidControl;
	strategy.basicStage = &basicStage;
	strategy.distance = &strategyDistance;
	// �헪�I�u�W�F�N�g
	basicStage.distance = &basicStageDistance;

	// ���Z�I�u�W�F�N�g(2014�N�x�ǉ���)
	competision.roboControl = &roboControl;
	roboControl.orderList = &orderList;
	roboControl.runner = &runner;
	frontWheel.frontMotor = &frontMotor;
	drivingWheel.leftMotor = &leftMotor;
	drivingWheel.rightMotor = &rightMotor;
	runner.frontWheel = &frontWheel;
	runner.drivingWheel = &drivingWheel;
	runner.lineTracer = &lineTracer;
	strategy.lineChange = &lineChange;
	strategy.bumpDecision = &bumpDecision;
	strategy.trialDecision = &trialDicision;
	strategy.jump = &jump;
	strategy.mogul = &mogul;
	strategy.course = &course;
	strategy.pendingArea = &pendingArea;
	strategy.orderTest = &orderTest;
	strategy.figureL = &figureL;
	bumpDecision.gyroSensor = &gyroSensor;
	trialDicision.bumpDecision = &bumpDecision;
	trialDicision.orderList = &orderList;
	jump.orderList = &orderList;
	mogul.orderList = &orderList;
	course.orderList = &orderList;
	pendingArea.orderList = &orderList;
	lineChange.orderList = &orderList;
	figureL.orderList = &orderList;

	orderTest.orderList = &orderList;

	// �e�I�u�W�F�N�g������������
	Bluetooth_init(&bluetooth);
	Motor_init(&leftMotor, NXT_PORT_C);
	Motor_init(&rightMotor, NXT_PORT_B);
	CheckStart_init(&checkStart);
	LineTracer_init(&lineTracer);
	PidControl_init(&pidControl);
	Communication_init(&communication);
	LightSensor_init(&lightSensor, NXT_PORT_S3);
	TouchSensor_init(&touchSensor, NXT_PORT_S4);
	GyroSensor_init(&gyroSensor, NXT_PORT_S1);
	LCD_init(&lcd);
	Timer_init(&lookUpGateTimer);
	Timer_init(&grayDecisionTimer);
	Distance_init(&distance);
	Distance_init(&garageInDistance);
	Distance_init(&strategyDistance);
	Distance_init(&basicStageDistance);
	Distance_init(&lookupGageDistance);
	Dash_init(&dash);

	// �e�I�u�W�F�N�g������������(2014�N�x�ǉ�)
	Motor_init(&frontMotor, NXT_PORT_A);
	OrderList_init(&orderList);
	RoboControl_init(&roboControl);
	DrivingWheel_init(&drivingWheel);
	FrontWheel_init(&frontWheel);
	LineChange_init(&lineChange);
	BumpDecision_init(&bumpDecision);
	TrialDecision_init(&trialDicision);
	Jump_init(&jump);
	Mogul_init(&mogul);
	Course_init(&course);
	PendingArea_init(&pendingArea);
	FigureL_init(&figureL);

	OrderTest_init(&orderTest);

	// �R�}���h�̏�����
	command.command = 0;
	command.value1 = 0;
	// ���̏�����
	info.loggerFlag = FALSE;
	info.autoStrategyFlag = TRUE;
//	info.autoStrategyFlag = FALSE;
//	info.strategyState = 0;
	info.strategyState = 7;
	info.startFlag = FALSE;
	info.measureInfo->countGrayMarker  = 0;
	info.measureInfo->leftMotorAngle = 0;
	info.measureInfo->rightMotorAngle = 0;
	info.runnerInfo->balanceFlag = TRUE;
	info.runnerInfo->forward = 0.0;
	info.runnerInfo->tail = C_TAIL_ANGL_DEFAULT;
	info.runnerInfo->turn = 0.0;
	info.settingInfo->courseType = C_COURSE_IN;
	info.runnerInfo->gyroOffset = 608;
	info.runnerInfo->chengeLineEdgeFlag = FALSE;
	info.runnerInfo->dashFlag = FALSE;
	info.runnerInfo->emergencyStopCheckFlag = TRUE;
	info.runnerInfo->emergencyStopFlag = FALSE;
	info.settingInfo->lineTraceFlg = TRUE;
//	info.settingInfo->pidD = 0.05;
	info.settingInfo->pidD = 0.09;
//	info.settingInfo->pidI = 0.07;
//	info.settingInfo->pidI = 0.1;
	info.settingInfo->pidI = 0.08;
	info.settingInfo->pidP = 0.6;
//	info.settingInfo->pidP = 0.5;
	info.settingInfo->target = C_TARGET;
	info.settingInfo->targetwait = 0;
	info.settingInfo->targetbas = 0;

	// Buletooth�ʐM�ݒ�
	communication.isSendData = FALSE;
	communication.isSendLog = TRUE;
	ecrobot_sound_tone(659, 100, 95);

	// �L�����u���[�V����
//	Calibration_MeasureLight(&calibration);

	LCD_DisplayClear(&lcd);

	//test
	//OrderList_lineTraceRunning(&orderList, 23, 570, TURN_FRONT, 0, 0);
	//OrderList_lineTraceRunning(&orderList, 20, 570, TURN_FRONT, 0, 0);
//	OrderList_lineTraceRunning(&orderList, 0, 550, TURN_FRONT, 0, 0);
//	OrderList_lineTraceRunning(&orderList, 0, 500, TURN_FRONT, 0, 0);
	//test

	/*
	//�R�[�X�^�C�v�\��
	LCD_SetPointXY(&lcd, 3, 0);
	LCD_DisplayInt(&lcd, info.settingInfo->courseType);


	//���C���g���[�X�������l
	LCD_SetPointXY(&lcd, 3, 1);
	LCD_DisplayInt(&lcd, (int)info.settingInfo->target);
	*/

	/*
	display_goto_xy(1, 1);
	display_int(orderList.orderIndex, 14);
	display_update();
	*/

	TerminateTask();
}

TASK(TaskMain)
{
	if(CheckStart_isStart(&checkStart) == TRUE)
	{
		Competision_action(&competision, &info);
	}
	else
	{
		// �X�^�[�g�O������Z���T�̒l���擾��������
		pidControl.deff2 = LightSensor_getBrightness(&lightSensor) - settingInfo.target;
		// �X�^�[�g�ҋ@
		CheckStart_waitStart(&checkStart, &info);

		//test
		//FrontWheel_setAngle(&frontWheel, 100);
		//test
	}

	TerminateTask();
}

TASK(TaskBuletooth)
{
	if(communication.isSendData)
	{
		test_data_send();
	}
	Communication_setLogData2(&communication, info.strategyState);
	// PC�Ƃ̒ʐM����
	Communication_communicate(&communication);

	// �R�}���h�̏���
	Commander_action(&commander, &info);

	TerminateTask();
}

