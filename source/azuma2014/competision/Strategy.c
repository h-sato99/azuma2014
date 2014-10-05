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

	// test
	if(info->autoStrategyFlag == FALSE)
	{
		//OrderTest_tailRun(this->orderTest);
		//OrderTest_figureL(this->orderTest);
		//OrderTest_strateRun(this->orderTest);
		//Course_strateRunIN(this->course);
		//Course_stableRunIN(this->course);
		return;
	}
	// test

	// インコース
	if(info->settingInfo->courseType == 1){
		switch(info->strategyState)
		{
			// コースクラス初期化
			case(1):
			{
				Course_resetMode(this->course);
				info->strategyState++;
				break;
			}
			// スタート直後の直線
			case(2):
			{
				if(Course_strateRunIN(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// モーグルまでのカーブ
			case(3):
			{
				if(Course_stableRunIN(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// 衝撃検知
			case(14):
			{
				if(TrialDecision_action(this->trialDecision))
				{
					info->strategyState++;
				}
				break;
			}
			// モーグル
			case(4):
			{
				if(Mogul_main(this->mogul))
				{
					info->strategyState++;
				}
				break;
			}
			case(5):
			{
				if(Course_strateRunIN(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState = 6;
				}
				break;
			}
			case(6):
			{
				if(Course_stableRunIN(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState = 7;
				}
				break;
			}
			case(7):
			{
				//ecrobot_sound_tone(800, 200, 95);
				if(FigureL_action(this->figureL))
				{
					info->strategyState = 8;
				}
				break;
			}
			case(8):
			{
				if(Course_strateRunIN(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState = 9;
				}
				break;
			}
			case(9):
			{
				if(Course_stableRunIN(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState = 10;
				}
				break;
			}
			case(10):
			{
				// stop
				break;
			}
		}
	}
	// アウトコース
	else
	{
		switch(info->strategyState)
		{
			case(1):
			{
				Course_resetMode(this->course);
				info->strategyState = 2;
				break;
			}
			case(2):
			{
				if(Course_strateRunOUT(this->course))
				{
					info->strategyState = 3;
				}
				break;
			}
			case(3):
			{
				if(Jump_action(this->jump))
				{
					info->strategyState = 4;
				}
				break;
			}
			case(4):
			{
				Course_resetMode(this->course);
				info->strategyState = 5;
				break;
			}
			case(5):
			{
				if(Course_stableRunOUT(this->course))
				{
					info->strategyState = 6;
				}
				break;
			}
			case(6):
			{
				if(PendingArea_action(this->pendingArea))
				{
					info->strategyState = 7;
				}
			}
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
	//BOOL check;

}

