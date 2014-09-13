/*******************************************************************************
**  ファイル名  ：Strategy.c
**  概要        ：戦略クラス
**  詳細        ：
*******************************************************************************/

#include "Strategy.h"

#define BASIC_DISTANCE_OUT 25500
#define BASIC_DISTANCE_IN 23500

static void Strategy_checkState(Strategy* this, Info* info);

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
			// 難所用
			break;
		}
		case(3):
		{
			// 難所用
			break;
		}
		case(4):
		{
			// 難所用
			break;
		}
		case(10):
		{
			if(TrialDecision_action(this->trialDecision))
			{
				Jump_action(this->jump);
			}
			break;
		}
		case(11):
		{
			if(TrialDecision_action(this->trialDecision))
			{
				Mogul_main(this->mogul);
			}
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

}

