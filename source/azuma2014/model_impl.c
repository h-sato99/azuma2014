/*******************************************************************************
**  ファイル名  ：model_impl.c
**  概要        ：モデル実装
**  詳細        ：特定のクラスに収まらない処理を行う
*******************************************************************************/

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

//2014年度
#include "competision/OrderList.h"
#include "competision/RoboControl.h"
#include "competision/Jump.h"
#include "competision/Mogul.h"
#include "technique/DrivingWheel.h"
#include "technique/FrontWheel.h"
#include "technique/LineChange.h"
#include "technique/TrialDecision.h"
#include "technique/BumpDecision.h"

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// 定数
// 尻尾の角度(100±5とする)
#define C_TAIL_ANGL_DEFAULT     105
#define C_TARGET 550
#define C_COURSE 0

// オブジェクトを静的に確保する
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
// 要素技術オブジェクト
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

// 競技オブジェクト
Competision competision;
BasicStage basicStage;
LineTracer lineTracer;
Runner runner;
Strategy strategy;

// 2014年度
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

// タスクの宣言
DeclareCounter(SysTimerCnt);
DeclareTask(TaskInit);
DeclareTask(TaskMain);
DeclareTask(TaskBuletooth);

// デバイス初期化用フック関数
// この関数はnxtOSEK起動時に実行されます。
void ecrobot_device_initialize()
{
	// センサ、モータなどの各デバイスの初期化関数を
	// ここで実装することができます
	// ⇒　光センサ赤色LEDをONにする
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
	SonarSensor_init(&sonarSensor, NXT_PORT_S2);
}

// デバイス終了用フック関数
// この関数はSTOPまたはEXITボタンが押された時に実行されます。
void ecrobot_device_terminate()
{
	// センサ、モータなどの各デバイスの終了関数を
	// ここで実装することができます。
	// ⇒　光センサ赤色LEDをOFFにする
	ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
	Bluetooth_terminate(&bluetooth);
	SonarSensor_term(&sonarSensor);
}

// 1msec周期割り込み(ISRカテゴリ2)から起動されるユーザー用フック関数
void user_1ms_isr_type2(void)
{
	// カウンタをIncrementする
	SignalCounter(SysTimerCnt);
}

TASK(TaskInit)
{
	// オブジェクト間のリンクを構築する
	checkStart.touchSensor = &touchSensor;
	checkStart.tail = &tail;
	checkStart.communication = &communication;
	calibration.lcd = &lcd;
	calibration.touchSensor = &touchSensor;
	calibration.lightSensor = &lightSensor;
	info.measureInfo = &courseInfo;
	info.runnerInfo = &runnerInfo;
	info.settingInfo = &settingInfo;
	// 要素技術オブジェクト
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
	// 競技オブジェクト
	competision.lineTracer = &lineTracer;
	competision.strategy = &strategy;
	competision.runner = &runner;
	lineTracer.lightSensor = &lightSensor;
	lineTracer.pidControl = &pidControl;
	strategy.basicStage = &basicStage;
	strategy.distance = &strategyDistance;
	// 戦略オブジェクト
	basicStage.distance = &basicStageDistance;

	// 競技オブジェクト(2014年度追加分)
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
	bumpDecision.gyroSensor = &gyroSensor;
	trialDicision.bumpDecision = &bumpDecision;
	trialDicision.orderList = &orderList;
	jump.orderList = &orderList;
	mogul.orderList = &orderList;

	// 各オブジェクトを初期化する
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

	// 各オブジェクトを初期化する(2014年度追加)
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

	// コマンドの初期化
	command.command = 0;
	command.value = 0;
	// 情報の初期化
	info.loggerFlag = FALSE;
	info.autoStrategyFlag = TRUE;
	info.strategyState = 0;
	info.startFlag = FALSE;
	info.measureInfo->countGrayMarker  = 0;
	info.measureInfo->leftMotorAngle = 0;
	info.measureInfo->rightMotorAngle = 0;
	info.runnerInfo->balanceFlag = TRUE;
	info.runnerInfo->forward = 0.0;
	info.runnerInfo->tail = C_TAIL_ANGL_DEFAULT;
	info.runnerInfo->turn = 0.0;
	info.settingInfo->courseType = C_COURSE;
	info.runnerInfo->gyroOffset = 608;
	info.runnerInfo->chengeLineEdgeFlag = FALSE;
	info.runnerInfo->dashFlag = FALSE;
	info.runnerInfo->emergencyStopCheckFlag = TRUE;
	info.runnerInfo->emergencyStopFlag = FALSE;
	info.settingInfo->lineTraceFlg = TRUE;
	info.settingInfo->pidD = 0.05;
	info.settingInfo->pidI = 0.07;
	info.settingInfo->pidP = 0.5;
	info.settingInfo->target = C_TARGET;
	info.settingInfo->targetwait = 0;
	info.settingInfo->targetbas = 0;
	ecrobot_sound_tone(659, 100, 95);

	// キャリブレーション
//	Calibration_MeasureLight(&calibration);

	LCD_DisplayClear(&lcd);

	/*
	//コースタイプ表示
	LCD_SetPointXY(&lcd, 3, 0);
	LCD_DisplayInt(&lcd, info.settingInfo->courseType);

	//ライントレースしきい値
	LCD_SetPointXY(&lcd, 3, 1);
	LCD_DisplayInt(&lcd, (int)info.settingInfo->target);
	*/

	display_goto_xy(1, 1);
	display_int(orderList.orderIndex, 14);
	display_update();

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
		// スタート前から光センサの値を取得し続ける
		pidControl.deff2 = LightSensor_getBrightness(&lightSensor) - settingInfo.target;
		// スタート待機
		CheckStart_waitStart(&checkStart, &info);
	}

	TerminateTask();
}

TASK(TaskBuletooth)
{
	Communication_setLogData2(&communication, info.strategyState);
	// PCとの通信処理
	Communication_communicate(&communication);

	// コマンドの処理
	Commander_action(&commander, &info);

	TerminateTask();
}

