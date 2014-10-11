/*******************************************************************************
**  ファイル名  ：Commander.c
**  概要        ：コマンド実行クラス
**  詳細        ：
*******************************************************************************/

#include "Commander.h"

static void Commander_runComand(Commander* this, Info *info);
static void Commander_setCommandResult(Commander* this, BOOL isSuccess);

void Commander_init(Commander* this)
{
	// 処理なし
}

/*------------------------------------------------------------------------------
--  関数名      ：Commander_action
--  概要        ：コマンドを実行し、結果を出力する
--              ：
--  引数        ：info 全情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Commander_action(Commander* this, Info *info)
{
	Communication_getCommand(this->communication);
	if(this->command->command > 0)
	{
		Commander_runComand(this, info);
		Commander_setCommandResult(this, TRUE);
	}
	else
	{
		Commander_setCommandResult(this, FALSE);
	}
}

/*------------------------------------------------------------------------------
--  関数名      ：Commander_runComand
--  概要        ：コマンドを実行する
--              ：
--  引数        ：info 全情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Commander_runComand(Commander* this, Info *info)
{
	// コマンドの処理
	switch(this->command->command){
		// 緊急停止
		case(99):
			info->runnerInfo->emergencyStopFlag = TRUE;
			break;
		// リモートスタート
		case(1):
			info->startFlag = TRUE;
			break;

		// 尻尾角度変更
		case(5):
		{
			info->runnerInfo->tail = this->command->value1;
			break;
		}
		// 前進値変更
		case(10):
		{
			info->runnerInfo->forward = this->command->value1;
			break;
		}
		// 旋回量変更
		case(11):
		{
			info->runnerInfo->turn = this->command->value1;
			break;
		}
		// ライントレース実行フラグ変更
		case(12):
		{
			if(this->command->value1 == 0)
			{
				info->settingInfo->lineTraceFlg = FALSE;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->lineTraceFlg = TRUE;
			}
			break;
		}
		// ルックアップゲート実行フラグ変更
		case(13):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->strategyState = 3;
			}
			break;
		}
		// 倒立制御実行フラグ変更
		case(14):
		{
			if(this->command->value1 == 0)
			{
				info->runnerInfo->balanceFlag = FALSE;
			}
			else
			{
				info->runnerInfo->balanceFlag = TRUE;
			}
			break;
		}
		// 戦略フラグ変更
		case(15):
		{
			info->strategyState = this->command->value1;
			break;
		}
		// ラインエッジ切替フラグ変更
		case(16):
		{
			if(this->command->value1 == 0)
			{
				info->runnerInfo->chengeLineEdgeFlag = FALSE;
			}
			else
			{
				info->runnerInfo->chengeLineEdgeFlag = TRUE;
			}
			break;
		}
		// ジャイロセンサのオフセット値変更
		case(21):
		{
			info->runnerInfo->gyroOffset = this->command->value1;
			break;
		}

		// 閾値変更
		case(22):
		{
			info->settingInfo->target = this->command->value1;
			break;
		}

		// ダッシュ機能オンオフ、オフセット値を一気に上げる量
		case(23):
		{
			if(info->runnerInfo->dashFlag == FALSE)
			{
				info->runnerInfo->dashvol = this->command->value1;
				info->runnerInfo->dashFlag = TRUE;
				break;
			}
			else
			{
				info->runnerInfo->dashFlag = FALSE;
				break;
			}
		}
		// ダッシュ機能で使う、オフセット値を上げる間隔（秒）
		case(24):
		{
			info->runnerInfo->dashlim = this->command->value1;
			info->runnerInfo->dashlim = info->runnerInfo->dashlim * 250;
			break;
		}

		// P制御値変更
		case(31):
		{
			info->settingInfo->pidP = this->command->value1 / 100;
			break;
		}
		// I制御値変更
		case(32):
		{
			info->settingInfo->pidI = this->command->value1 / 100;
			break;
		}
		// D制御値変更
		case(33):
		{
			info->settingInfo->pidD = this->command->value1 / 100;
			break;
		}
		// 自動戦略切替フラグ
		case(50):
		{
			if(this->command->value1 == 0)
			{
				info->autoStrategyFlag = FALSE;
			}
			else
			{
				info->autoStrategyFlag = TRUE;
			}
			break;
		}
		// コース切替
		case(51):
		{
			info->settingInfo->courseType = this->command->value1;
			break;
		}

		// ジャンプ台
		case(60):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 0;
				info->strategyState = 50;
			}
			break;
		}
		// 仕様未確定
		case(61):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 0;
				info->strategyState = 51;
			}
			break;
		}
		// モーグル
		case(62):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 1;
				info->strategyState = 50;
			}
			break;
		}
		// フィギュアL
		case(63):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 1;
				info->strategyState = 51;
			}
			break;
		}
		// ライン復帰(左旋回)
		case(64):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 1;
				info->strategyState = 52;
			}
			break;
		}
		// ライン復帰(右旋回)
		case(65):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 1;
				info->strategyState = 53;
			}
			break;
		}
		// ライン切替
		case(66):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 1;
				info->strategyState = 54;
			}
			break;
		}
		// 衝撃検知
		case(67):
		{
			if(this->command->value1 == 0)
			{
				info->strategyState = 1;
			}
			else if(this->command->value1 == 1)
			{
				info->settingInfo->courseType = 1;
				info->strategyState = 55;
			}
			break;
		}

		// 戦略切替
		case(69):
		{
			info->settingInfo->courseType = this->command->value1;
			info->strategyState = this->command->value2;
			break;
		}
		// 指示リスト追加
		case(70):
		{
			switch(this->command->value1)
			{
				case(0):
				{
					// マニュアル走行
					OrderList_manualRunning(this->orderList, this->command->value2, this->command->value3, this->command->value4, this->command->value5, this->command->value6);
					break;
				}
				case(1):
				{
					// ライントレース走行
					OrderList_lineTraceRunning(this->orderList, this->command->value2, this->command->value3, this->command->value4, this->command->value5, this->command->value6);
					break;
				}
				case(2):
				{
					// 停止
					OrderList_stop(this->orderList);
					break;
				}
				case(3):
				{
					// PID制御定数設定
					OrderList_setPID(this->orderList, this->command->value2, this->command->value3, this->command->value4);
					break;
				}
				case(4):
				{
					// 小範囲左旋回
					OrderList_turnOnSpotLeft(this->orderList, this->command->value2, this->command->value3, this->command->value4, this->command->value5);
					break;
				}
				case(5):
				{
					// 小範囲右旋回
					OrderList_turnOnSpotRight(this->orderList, this->command->value2, this->command->value3, this->command->value4, this->command->value5);
					break;
				}
			}
			break;
		}
	}
}


/*------------------------------------------------------------------------------
--  関数名      ：Commander_setCommandResult
--  概要        ：コマンドの実行結果を出力する
--              ：
--  引数        ：isSuccess 成功フラグ
--              ：  TRUE 成功 / FALSE 失敗
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Commander_setCommandResult(Commander* this, BOOL isSuccess)
{
	if(isSuccess == TRUE)
	{
		ecrobot_sound_tone(659, 100, 95);
		Communication_setLogData1(this->communication, 1);
	}
	else
	{
		Communication_setLogData1(this->communication, 0);
	}
}
