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
				if(Course_IN_StartToCurve(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// カーブ
			case(3):
			{
				if(Course_IN_CurveToLineChange(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// ライン切替
			case(4):
			{
				if(LineChange_action(this->lineChange) == TRUE)
				{
					info->strategyState++;
				}
				break;
			}
			// 2周目スタート地点
			case(5):
			{
				if(Course_IN_LineChangeToReStart(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// スタート直後の直線
			case(6):
			{
				if(Course_IN_StartToCurve(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// 2周目カーブ
			case(7):
			{
				if(Course_IN_CurveToMogul(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// 難所検知
			case(8):
			{
				if(TrialDecision_action(this->trialDecision))
				{
					info->strategyState++;
				}
				break;
			}
			// モーグル
			case(9):
			{
				if(Mogul_main(this->mogul))
				{
					info->strategyState++;
				}
				break;
			}
			// ライン復帰
			case(10):
			{
				if(LineComeback_main(this->lineComeback,1))
				{
					info->strategyState++;
				}
				break;
			}
			// マニュアル走行切替
			case(11):
			{
				if(Course_IN_MogulToManual(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// マニュアル走行
			case(12):
			{
				if(Course_IN_ManualToFigureL(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// 難所検知
			case(13):
			{
				if(TrialDecision_action(this->trialDecision))
				{
					info->strategyState++;
				}
				break;
			}
			// フィギュアL
			case(14):
			{
				//ecrobot_sound_tone(800, 200, 95);
				if(FigureL_action(this->figureL))
				{
					info->strategyState++;
				}
				break;
			}
			// ライン復帰
			case(15):
			{
				if(LineComeback_main(this->lineComeback,1))
				{
					info->strategyState++;
				}
				break;
			}
			// 停止位置まで走行
			case(16):
			{
				if(Course_IN_FigureLToStop(this->course) == TRUE)
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// 停止
			case(17):
			{
				// stop
				Course_stop(this->course);
				break;
			}
			//テスト用
			case(50):
				if(Mogul_main(this->mogul))
				{
					ecrobot_sound_tone(559, 100, 95);
				}
				break;
			case(51):
				if(FigureL_action(this->figureL))
				{
					ecrobot_sound_tone(559, 100, 95);
				}
				break;
			case(52):
				if(LineComeback_main(this->lineComeback,0))
				{
					ecrobot_sound_tone(559, 100, 95);
				}
				break;
			case(53):
				if(LineComeback_main(this->lineComeback,1))
				{
					ecrobot_sound_tone(559, 100, 95);
				}
				break;
		}
	}
	// アウトコース
	else
	{
		switch(info->strategyState)
		{
			// コースクラス初期化
			case(1):
			{
				Course_resetMode(this->course);
				info->strategyState++;
				break;
			}
			// スタート
			case(2):
			{
				if(Course_OUT_StartToCurve(this->course))
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// 第1カーブ
			case(3):
			{
				if(Course_OUT_CurveToJump(this->course))
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// 難所検知
			case(4):
			{
				if(TrialDecision_action(this->trialDecision))
				{
					info->strategyState++;
				}
				break;
			}
			// ジャンプ台
			case(5):
			{
				if(Jump_action(this->jump))
				{
					info->strategyState++;
				}
				break;
			}
			// ライン復帰
			case(6):
			{
				if(LineComeback_main(this->lineComeback,1))
				{
					info->strategyState++;
				}
				break;
			}
			// ダッシュ開始
			case(7):
			{
				if(Course_OUT_JumpToDashStart(this->course))
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// ダッシュ
			case(8):
			{
				if(Course_OUT_DashStartToDashEnd(this->course))
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// ダッシュ終了
			case(9):
			{
				if(Course_OUT_DashEndToPending(this->course))
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// 難所検知
			case(10):
			{
				if(TrialDecision_action(this->trialDecision))
				{
					info->strategyState++;
				}
				break;
			}
			// 仕様未確定エリア
			case(11):
			{
				if(PendingArea_action(this->pendingArea))
				{
					info->strategyState++;
				}
				break;
			}
			// ライン復帰
			case(12):
			{
				if(LineComeback_main(this->lineComeback,1))
				{
					info->strategyState++;
				}
				break;
			}
			// 第4カーブ
			case(13):
			{
				if(Course_OUT_PendingToCurve(this->course))
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// ゴール
			case(14):
			{
				if(Course_OUT_CurveToGoal(this->course))
				{
					Course_resetMode(this->course);
					info->strategyState++;
				}
				break;
			}
			// 停止
			case(15):
			{
				// stop
				Course_stop(this->course);
				break;
			}
			//テスト用
			case(50):
				if(Jump_action(this->jump))
				{
					ecrobot_sound_tone(559, 100, 95);
				}
				break;
			case(51):
				if(PendingArea_action(this->pendingArea))
				{
					ecrobot_sound_tone(559, 100, 95);
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
	//BOOL check;

}

