/*******************************************************************************
**  ファイル名  ：LookUpGate.c
**  概要        ：ルックアップゲートクラス
**  詳細        ：ルックアップゲート走行に関する処理を定義。
*******************************************************************************/

#include "LookUpGate.h"

#define STOP     		0 	// 停止
#define LOW     		30 	// 低速
#define NORMAL  		80 	// 通常
#define HIGH    		100 // 高速
#define TAIL_ANGL		95	// 尻尾の角度(100±5とする)
#define STAIRS_ANGL1	80	// 尻尾の角度(１段階傾け)
#define STAIRS_ANGL2	65	// 尻尾の角度(２段階傾け)
#define STAIRS_ANGL3	60	// 尻尾の角度
#define LOOKUP_FORWORD_STOP		0
#define LOOKUP_FORWORD_RUN		20
#define LOOKUP_BACK				-30
#define LOOKUP_FORWORD_WAKEUP	-40
#define LOOKUP_FORWORD_DISTANCE 30

int throwGateFlg;			// ゲート通過フラグ

// 初期化する
void LookUpGate_init(LookUpGate* this)
{
	this->isInitialized	= FALSE; 					// 初期化フラグ
	this->forward		= LOW;   					// 前進値
	this->turn			= -1;						// 旋回値
	this->tAngle		= TAIL_ANGL;				// 尻尾角度
	this->sonar			= 255;						// 障害物との距離
	this->mode			= 0;						// 走行モード
	throwGateFlg        = 0;						// ゲート通過フラグ
	this->isFinished =FALSE;
}


// ルックアップゲートを走行する
void LookUpGate_action(LookUpGate* this, Info *info)
{
	// 初期化(スタート時間の取得)
	if(! this->isInitialized)
	{
		info->runnerInfo->forward = 20;

		// 40msecごとに超音波センサの値を取得する
		if(0 <= systick_get_ms() % 40 && systick_get_ms() % 40 <= 5)
		{
			this->sonar = SonarSensor_get(this->sonarSensor);
		}


		// 超音波センサの値を判定
		// ecrobot_get_sonar_sensorを実行し始めた直後、センサ値は0を返す。
		// そのため、0以下の場合もルックアップゲート処理を開始しない
		// ようにする必要がある。
		if(this->sonar <= 0 || this->sonar > 10)
		{
			// 0以下または30より大きい場合、処理を中断する
			return;
		}
		else
		{
			// 初期化済にする
			this->isInitialized = TRUE;
		}
	}


	switch(this->mode)
	{
		case 0:
			// 障害物を発見したら、モータを止める
			// ロボを傾ける（１段階目）
			Timer_set(this->timer);
			this->forward = 0;
			this->turn = 0;
			this->tAngle = STAIRS_ANGL1;
			this->mode++;
			info->runnerInfo->balanceFlag = FALSE;
			info->settingInfo->target += 50;
			info->settingInfo->lineTraceFlg = FALSE;
			ecrobot_sound_tone(500, 200, 100);
			break;

		case 1:
			// ロボを傾ける（２段階目）
			if(Timer_check(this->timer, 700))
			{
				Timer_set(this->timer);
				this->forward = LOW;
				this->turn = 0;
				this->tAngle = STAIRS_ANGL3;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 2:
			// 直進（ゲートをくぐる）
			if(Distance_check(this->distance, info->measureInfo, 60))
			{
				Distance_set(this->distance, info->measureInfo);
				this->forward = LOW;
				this->turn = 0;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 3:
			// ウェイトする
			if(Distance_check(this->distance, info->measureInfo, 380))
			{
				Timer_set(this->timer);
				this->forward = 0;
				this->turn = 0;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 4:
			// バックする（ゲートをくぐる）
			if(Timer_check(this->timer, 500))
			{
				Distance_set(this->distance, info->measureInfo);
				this->forward = LOOKUP_BACK;
				this->turn = 0;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 5:
			// ウェイトする
			if(Distance_check(this->distance, info->measureInfo, 420))
			{
				Timer_set(this->timer);
				this->forward = 0;
				this->turn = 0;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 6:
			// １秒ウェイトしたら低速で直進（ゲートをくぐる）
			if(Timer_check(this->timer, 500))
			{
				Distance_set(this->distance, info->measureInfo);
				this->forward = LOW;
				this->turn = 0;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 7:
			// ウェイトする
			if(Distance_check(this->distance, info->measureInfo, 440))
			{
				Timer_set(this->timer);
				this->forward = 0;
				this->turn = 0;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 8:
			// ロボを傾ける（１段階目）
			if(Timer_check(this->timer, 500))
			{
				Distance_set(this->distance, info->measureInfo);
				this->forward = LOOKUP_FORWORD_WAKEUP;
				this->turn = 0;
				this->tAngle = STAIRS_ANGL1;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 9:
			// ロボを傾ける（１段階目）
			if(Distance_check(this->distance, info->measureInfo, 60))
			{
				Distance_set(this->distance, info->measureInfo);
				this->forward = LOOKUP_FORWORD_WAKEUP;
				this->turn = 0;
				this->tAngle = TAIL_ANGL;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
			}
			break;

		case 10:
			// ロボを傾ける（１段階目）
			if(Distance_check(this->distance, info->measureInfo, 60))
			{
				Timer_set(this->timer);
				this->forward = 20;
				this->mode++;
				ecrobot_sound_tone(500, 200, 100);
				info->settingInfo->target = 520;
				info->settingInfo->lineTraceFlg = TRUE;
			}
			break;
		default:
			this->isFinished =TRUE;
			return;
	}
	info->runnerInfo->forward = this->forward;
	info->runnerInfo->turn = this->turn;
	info->runnerInfo->tail = this->tAngle;
}

BOOL LookUpGate_checkFinish(LookUpGate* this)
{
	return this->isFinished;
}

