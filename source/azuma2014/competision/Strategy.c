/*******************************************************************************
**  ファイル名  ：Strategy.c
**  概要        ：戦略クラス
**  詳細        ：
*******************************************************************************/

#include "Strategy.h"

#define BASIC_DISTANCE_OUT 25500
#define BASIC_DISTANCE_IN 23500

static void Strategy_checkState(Strategy* this, Info* info);
static BOOL Strategy_checkBasicStage(Strategy* this, Info* info);
static BOOL Strategy_checkLookUpGate(Strategy* this, Info* info);
static BOOL Strategy_checkSeesaw(Strategy* this, Info* info);

void Strategy_init(Strategy* this)
{
	this->initBasicStageFlag = FALSE;
	this->startGrayDecision = FALSE;
}

/*------------------------------------------------------------------------------
--  関数名      ：Strategy_action
--  概要        ：戦略を実行する
--              ：
--  引数        ：info  全情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Strategy_action(Strategy* this, Info* info)
{
	Strategy_checkState(this, info);

	switch(info->strategyState)
	{
		case(1):
		{
			// ベーシックステージ
			BasicStage_action(this->basicStage, info);
			break;
		}
		case(2):
		{
			// シーソー
			Seesaw_action(this->seesaw, info);
			break;
		}
		case(3):
		{
			// ルックアップゲート
			LookUpGate_action(this->lookUpGate, info);
			break;
		}
		case(4):
		{
			// ガレージイン
			GarageIn_action(this->garageIn, info);
			break;
		}
	}
}

/*------------------------------------------------------------------------------
--  関数名      ：Strategy_checkState
--  概要        ：戦略の切り替えを行う
--              ：
--  引数        ：info  全情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
static void Strategy_checkState(Strategy* this, Info* info)
{
	BOOL check;

	if(info->autoStrategyFlag == FALSE)
	{
		return;
	}

	// 戦略の切り替えを行う
	switch(info->strategyState)
	{
		case(1):
		{
			// ベーシックステージ
			check = Strategy_checkBasicStage(this, info);
			if(check == TRUE)
			{
				ecrobot_sound_tone(659, 100, 95);
				info->strategyState = 10;

				// 難所用の閾値を設定する
				info->settingInfo->target = info->settingInfo->target - 50;
			}
			break;
		}
		case(2):
		{
			// シーソー
			check = Strategy_checkSeesaw(this, info);
			if(check == TRUE)
			{
				// ガレージインへ切替
				info->strategyState = 4;
			}
			break;
		}
		case(3):
		{
			// ルックアップゲート
			check = Strategy_checkLookUpGate(this, info);
			if(check == TRUE)
			{
				// ガレージインへ切替
				info->strategyState = 4;
			}
			break;
		}
		case(10):
		{
			// １回目の灰色検知処理
			if(info->settingInfo->courseType == 0)
			{
				// シーソーへ切替
				info->strategyState = 2;
			}
			else
			{
				// ルックアップゲートへ切替
				info->strategyState = 3;
			}
		}
	}
}

/*------------------------------------------------------------------------------
--  関数名      ：Strategy_checkBasicStage
--  概要        ：ベーシックステージの終了を判定する
--              ：
--  引数        ：info  全情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
static BOOL Strategy_checkBasicStage(Strategy* this, Info* info)
{
	int checkDistance;
	if(this->initBasicStageFlag == FALSE)
	{
		Distance_set(this->distance, info->measureInfo);
		this->initBasicStageFlag = TRUE;
		return FALSE;
	}
	else
	{
		if(info->settingInfo->courseType == 0)
		{
			checkDistance = BASIC_DISTANCE_OUT;
		}
		else
		{
			checkDistance = BASIC_DISTANCE_IN;
		}
		if(Distance_check(this->distance, info->measureInfo, checkDistance))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

/*------------------------------------------------------------------------------
--  関数名      ：Strategy_checkLookUpGate
--  概要        ：ルックアップゲートの終了を判定する
--              ：
--  引数        ：info  全情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
static BOOL Strategy_checkLookUpGate(Strategy* this, Info* info)
{
	if(LookUpGate_checkFinish(this->lookUpGate) == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*------------------------------------------------------------------------------
--  関数名      ：Strategy_checkSeesaw
--  概要        ：シーソーの終了を判定する
--              ：
--  引数        ：info  全情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
static BOOL Strategy_checkSeesaw(Strategy* this, Info* info)
{
	if(Seesaw_checkFinish(this->seesaw) == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
