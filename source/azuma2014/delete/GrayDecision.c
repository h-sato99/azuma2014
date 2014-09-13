/*******************************************************************************
**  ファイル名  ：GrayDecision.c
**  概要        ：灰色検知クラス
**  詳細        ：灰色検知の判定用処理を行う。
*******************************************************************************/

#include "GrayDecision.h"

#define C_WHITE_CAL    50   // 白色の基準値計算用
#define C_GETCOUNT     15   // 取得回数が何回以上かの基準値


/*------------------------------------------------------------------------------
--  関数名      ：GrayDecision_init
--  概要        ：灰色検知で使用する全変数を初期化。
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void GrayDecision_init(GrayDecision* this)
{
	this->GrayPassCnt = 0;

	this->lightget = 0;
	this->light_target = 0;
	this->getcount = 0;

	this->isInitialized = FALSE;
	this->forward = 0;
	this->turn = -1;
	this->mode = 0;
}


/*------------------------------------------------------------------------------
--  関数名      ：GrayDecision_setTarget
--  概要        ：白色基準値決定。
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void GrayDecision_setTarget(GrayDecision* this, int target)
{
	// 白色基準値をキャリブレーションの白＋基準計算値に設定
	this->light_target = target + C_WHITE_CAL;
}

/*------------------------------------------------------------------------------
--  関数名      ：GrayDecision_main
--  概要        ：灰色検知のメイン処理。
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void GrayDecision_main(GrayDecision* this, Info *info)
{
	this->forward = 0;
	this->turn = 0;
}
void GrayDecision_main_bk(GrayDecision* this, Info *info)
{
	// 光センサの値を取得する
	this->lightget = (int)LightSensor_getBrightness(this->lightSensor);

	// 取得した値が白色基準値以下であるか判定
	if (this->lightget <= this->light_target)
	{
		// 取得回数カウンタに1を加算する
		this->getcount = this->getcount + 1;

	}
	else
	{
		// 取得回数初期化
		this->getcount = 0;

		// ライントレースに戻る
		return;

	}

	// 取得回数が基準値以上か（脱線したか）を判定
	if (this->getcount >= C_GETCOUNT)
	{
		// スタート時間の取得（初めの一度だけ行う）
		if(! this->isInitialized)
		{
			// 脱線処理スタート時間取得
			Timer_set(this->timer);
			// 処理モードを２に設定
			this->mode = 1;
			// スタート時間取得済にする
			this->isInitialized = TRUE;
		}

		switch(this->mode)
		{
			case 1:
				// モーターを止める
				this->forward = 0;
				this->turn = 0;
				// 処理モードに２を設定
				this->mode = 2;
				break;

			case 2:
				// ０．５秒ウェイトしたらラインへ復帰の処理
				if(Timer_check(this->timer, 500))
				{
					this->forward = 0;
					this->turn = 50;
					this->mode = 3;

				}
				break;

			case 3:
				// １秒ウェイトしたらラインへ復帰の処理
				if(Timer_check(this->timer, 1000))
				{
					this->forward = 30;
					this->turn = 0;

					// 各変数初期化
					this->mode = 0;
					this->getcount = 0;
					this->isInitialized = FALSE;

					//
					this->GrayPassCnt = this->GrayPassCnt + 1;

				}
				break;

			default:
				// ライントレースに戻る
				return;
		}

	// 値を設定してライントレースに戻る
	info->runnerInfo->forward = this->forward;
	info->runnerInfo->turn = this->turn;
	return;

	}
}
