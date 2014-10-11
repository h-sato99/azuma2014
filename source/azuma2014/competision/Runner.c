/*******************************************************************************
**  ファイル名  ：Runner.c
**  概要        ：走行クラス
**  詳細        ：
*******************************************************************************/

#include "Runner.h"

static void Runner_run_MUNUAL(Runner* this, float target, F32 forward, F32 turn, int runningState);
static void Runner_run_LINETRACE(Runner* this, float target, F32 forward, F32 turn, int runningState);
static void Runner_run_TURN_INIT(Runner* this, int turnState);
static void Runner_run_TURN_FRONT(Runner* this, int turnState);
static void Runner_run_TURN_DRIVING(Runner* this, int turnState);
static void Runner_run_TURN_SPOT(Runner* this, int turnState);
static void Runner_manualRun(Runner* this, F32 forward, F32 turn);
static void Runner_lineTraceRun(Runner* this, F32 forward, F32 turn);
static void Runner_fowardFrontWheel(Runner* this);
static void Runner_turnByFrontWheel(Runner* this);
static void Runner_turnByDrivingWheel(Runner* this);
static void Runner_turnOnSpotLeft(Runner* this);
static void Runner_turnOnSpotRight(Runner* this);

void Runner_init(Runner* this)
{
	this->runningState = MUNUAL;
	this->turnState = TURN_INIT;
}

int Runner_getDistance(Runner* this)
{
	int calcWork;
	int leftPwm;
	int rightPwm;

	leftPwm = DrivingWheel_getLeftAngle(this->drivingWheel);
	rightPwm = DrivingWheel_getRightAngle(this->drivingWheel);

	if (leftPwm < 0)
	{
		leftPwm = leftPwm * -1;
	}
	if (rightPwm < 0)
	{
		rightPwm = rightPwm * -1;
	}

	calcWork = (leftPwm + rightPwm) / 2;
	if(calcWork < 0)
	{
		calcWork *= -1;
	}

	return calcWork;
}

void Runner_run(Runner* this, F32 forward, F32 turn, float target, int runningState, int turnState)
{
	switch(this->runningState)
	{
		case MUNUAL:
			//ecrobot_sound_tone(659, 100, 95);
			Runner_run_MUNUAL(this, target, forward, turn, runningState);
			break;
		case LINETRACE:
			Runner_run_LINETRACE(this, target, forward, turn, runningState);
			break;
		default:
			break;
	}
	switch(this->turnState)
	{
		case TURN_INIT:
			Runner_run_TURN_INIT(this, turnState);
			break;
		case TURN_DRIVING:
			Runner_run_TURN_DRIVING(this, turnState);
			break;
		case TURN_FRONT:
			Runner_run_TURN_FRONT(this, turnState);
			break;
		case TURN_LEFT:
			Runner_run_TURN_SPOT(this, turnState);
			break;
		case TURN_RIGHT:
			Runner_run_TURN_SPOT(this, turnState);
			break;
	}
}

static void Runner_run_MUNUAL(Runner* this, float target, F32 forward, F32 turn, int runningState)
{
	/*
	display_goto_xy(2, 4);
	display_int(runningState, 14);
	display_goto_xy(2, 5);
	display_int(forward, 14);
	display_update();
	*/
	if(runningState == MUNUAL)
	{
		this->runningState = MUNUAL;
		Runner_manualRun(this, forward, turn);
	}
	else
	{
		this->runningState = LINETRACE;
		Runner_lineTraceRun(this, forward, target);
	}
}

static void Runner_run_LINETRACE(Runner* this, float target, F32 forward, F32 turn, int runningState)
{
	if(runningState == LINETRACE)
	{
		this->runningState = LINETRACE;
		Runner_lineTraceRun(this, forward, target);
	}
	else
	{
		this->runningState = MUNUAL;
		Runner_manualRun(this, forward, turn);
	}
}

static void Runner_run_TURN_INIT(Runner* this, int turnState)
{
	int frontWheelAngle;

	frontWheelAngle = FrontWheel_getAngle(this->frontWheel);

	if(frontWheelAngle == 0 && turnState == TURN_FRONT)
	{
		this->turnState = TURN_FRONT;
		Runner_turnByFrontWheel(this);
	}
	else if(frontWheelAngle == 0 && turnState == TURN_DRIVING)
	{
		this->turnState = TURN_DRIVING;
		Runner_turnByDrivingWheel(this);
	}
	else if(frontWheelAngle == 0 && turnState == TURN_LEFT)
	{
		this->turnState = TURN_LEFT;
		Runner_turnOnSpotLeft(this);
	}
	else if(frontWheelAngle == 0 && turnState == TURN_RIGHT)
	{
		this->turnState = TURN_RIGHT;
		Runner_turnOnSpotRight(this);
	}
	else
	{
		this->turnState = TURN_INIT;
		Runner_fowardFrontWheel(this);
	}
}

static void Runner_run_TURN_FRONT(Runner* this, int turnState)
{
	if(turnState == TURN_FRONT)
	{
		this->turnState = TURN_FRONT;
		Runner_turnByFrontWheel(this);
	}
	else
	{
		this->turnState = TURN_INIT;
		Runner_fowardFrontWheel(this);
	}
}

static void Runner_run_TURN_DRIVING(Runner* this, int turnState)
{
	if(turnState == TURN_DRIVING)
	{
		this->turnState = TURN_DRIVING;
		Runner_turnByDrivingWheel(this);
	}
	else
	{
		this->turnState = TURN_INIT;
		Runner_fowardFrontWheel(this);
	}
}

static void Runner_run_TURN_SPOT(Runner* this, int turnState)
{
	if(turnState == TURN_LEFT)
	{
		this->turnState = TURN_LEFT;
		Runner_turnOnSpotLeft(this);
	}
	else if(turnState == TURN_RIGHT)
	{
		this->turnState = TURN_RIGHT;
		Runner_turnOnSpotRight(this);
	}
	else
	{
		this->turnState = TURN_INIT;
		Runner_fowardFrontWheel(this);
	}
}

static void Runner_manualRun(Runner* this, F32 forward, F32 turn)
{
	this->forward = forward;
	this->turn = turn;
}

static void Runner_lineTraceRun(Runner* this, F32 forward, float target)
{
	//ecrobot_sound_tone(659, 100, 95);
	/*
	display_goto_xy(2, 4);
	display_int(forward, 14);
	display_goto_xy(2, 5);
	display_int(target, 14);
	display_update();
	*/
	this->forward = forward;
	LineTracer_setTarget(this->lineTracer, target);
	this->turn = LineTracer_getTurn(this->lineTracer);
}

static void Runner_fowardFrontWheel(Runner* this)
{
	FrontWheel_setAngle(this->frontWheel, 0);

	DrivingWheel_setPwm(this->drivingWheel ,this->forward, this->forward);
}

static void Runner_turnByFrontWheel(Runner* this)
{
	int frontWheelAngle;

	frontWheelAngle = this->turn;

	FrontWheel_setAngle(this->frontWheel, frontWheelAngle);

	DrivingWheel_setPwm(this->drivingWheel ,this->forward, this->forward);
}

static void Runner_turnByDrivingWheel(Runner* this)
{
	int leftPwm;
	int rightPwm;

	// 前後進命令と旋回量からモータPWM出力値を算出
	leftPwm = (int)(this->forward + this->turn);
	rightPwm = (int)(this->forward - this->turn);

	/*
	* PWM出力値がMAX値内になるように調整
	* 前進する場合のみ、PWM出力値がMAX値を超える場合は
	* もう片方のPWM出力値から超過分を減算
	*/
	// 左モータPWM出力値調整
	if(leftPwm > 100)
	{
		if(this->forward > 0)
		{
			rightPwm = rightPwm - (leftPwm - 100);
		}
		leftPwm = 100;
	}
	else if(leftPwm < -100)
	{
		leftPwm = -100;
	}
	// 右モータPWM出力値調整
	if(rightPwm > 100)
	{
		if(this->forward > 0)
		{
			leftPwm = leftPwm - (rightPwm - 100);
		}
		rightPwm = 100;
	}
	else if(rightPwm <-100)
	{
		rightPwm = -100;
	}

	// 前進命令の場合、モーターは逆回転させない
	if(this->forward > 0)
	{
		if(leftPwm < 0)
		{
			leftPwm = 0;
		}
		if(rightPwm < 0)
		{
			rightPwm = 0;
		}
	}

	DrivingWheel_setPwm(this->drivingWheel ,leftPwm, rightPwm);
}

static void Runner_turnOnSpotLeft(Runner* this)
{
	int frontWheelAngle;
	int leftPwm;
	int rightPwm;

	// 前後進命令と旋回量からモータPWM出力値を算出
	frontWheelAngle = this->turn;
	if(frontWheelAngle >= 0)
	{
		// 前輪の旋回量は左向きが負の数なので、プラスの場合は-1を掛ける
		frontWheelAngle *= -1;
	}
	leftPwm = (int)(this->forward * -1);
//	leftPwm = 0;
	rightPwm = (int)(this->forward);

	/*
	* PWM出力値がMAX値内になるように調整
	*/
	// 左モータPWM出力値調整
	if(leftPwm > 100)
	{
		leftPwm = 100;
	}
	else if(leftPwm < -100)
	{
		leftPwm = -100;
	}
	// 右モータPWM出力値調整
	if(rightPwm > 100)
	{
		rightPwm = 100;
	}
	else if(rightPwm <-100)
	{
		rightPwm = -100;
	}

	FrontWheel_setAngle(this->frontWheel, frontWheelAngle);
	DrivingWheel_setPwm(this->drivingWheel ,leftPwm, rightPwm);
}

static void Runner_turnOnSpotRight(Runner* this)
{
	int frontWheelAngle;
	int leftPwm;
	int rightPwm;

	// 前後進命令と旋回量からモータPWM出力値を算出
	frontWheelAngle = this->turn;
	if(frontWheelAngle < 0)
	{
		// 前輪の旋回量は右向きが正の数なので、マイナスの場合は-1を掛ける
		frontWheelAngle *= -1;
	}
	leftPwm = (int)(this->forward);
	rightPwm = (int)(this->forward * -1);
//	rightPwm = 0;

	/*
	* PWM出力値がMAX値内になるように調整
	*/
	// 左モータPWM出力値調整
	if(leftPwm > 100)
	{
		leftPwm = 100;
	}
	else if(leftPwm < -100)
	{
		leftPwm = -100;
	}
	// 右モータPWM出力値調整
	if(rightPwm > 100)
	{
		rightPwm = 100;
	}
	else if(rightPwm <-100)
	{
		rightPwm = -100;
	}

	FrontWheel_setAngle(this->frontWheel, frontWheelAngle);
	DrivingWheel_setPwm(this->drivingWheel ,leftPwm, rightPwm);
}
