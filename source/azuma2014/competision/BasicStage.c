/*******************************************************************************
**  ファイル名  ：BasicStage.c
**  概要        ：ベーシックステージクラス
**  詳細        ：
*******************************************************************************/

#include "BasicStage.h"



void BasicStage_init(BasicStage* this)
{
	this->mode = 0;					// スイッチ用カウンタ
}

/*------------------------------------------------------------------------------
--  関数名      ：BasicStage_action
--  概要        ：ベーシックステージ用の処理を実行する
--              ：
--  引数        ：info  全情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void BasicStage_action(BasicStage* this, Info *info)
{
	if(info->settingInfo->courseType == 1){
		// インコース用
		switch(this->mode){

			// 【case0】前進値を40に設定
			case 0:
				Distance_set(this->distance, info->measureInfo);
				info->runnerInfo->forward = 40;
				info->runnerInfo->dashFlag = FALSE;
				info->runnerInfo->dashvol = 0;
				info->runnerInfo->dashlim = 0;
				this->mode++;
			break;

			// 【case1】前進値を60に設定
			case 1:
				if(Distance_check(this->distance, info->measureInfo, 200)){
					info->runnerInfo->forward = 60;
					info->runnerInfo->dashFlag = FALSE;
					info->runnerInfo->dashvol = 0;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;

			// 【case2】前進値を80に設定
			case 2:
				if(Distance_check(this->distance, info->measureInfo, 400)){
					info->runnerInfo->forward = 80;
					info->runnerInfo->dashFlag = FALSE;
					info->runnerInfo->dashvol = 0;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;

			// 【case3】オフセット値を5上げてダッシュ
			case 3:
				if(Distance_check(this->distance, info->measureInfo, 600)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// ダッシュフラグオフ
			case 4:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// 【case4】オフセット値を5上げてダッシュ
			case 5:
				if(Distance_check(this->distance, info->measureInfo, 6800)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// ダッシュフラグオフ
			case 6:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// 【case5】オフセット値を5上げてダッシュ
			case 7:
				if(Distance_check(this->distance, info->measureInfo, 10600)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// ダッシュフラグオフ
			case 8:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// 【case6】オフセット値を5上げてダッシュ
			case 9:
				if(Distance_check(this->distance, info->measureInfo, 14700)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// ダッシュフラグオフ
			case 10:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// 【case7】オフセット値を5上げてダッシュ
			case 11:
				if(Distance_check(this->distance, info->measureInfo, 18500)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// ダッシュフラグオフ
			case 12:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

		}
	}
	else{
		// アウトコース用
		switch(this->mode){

			// 【case0】前進値を40に設定
			case 0:
				Distance_set(this->distance, info->measureInfo);
				info->runnerInfo->forward = 40;
				info->runnerInfo->dashFlag = FALSE;
				info->runnerInfo->dashvol = 0;
				info->runnerInfo->dashlim = 0;
				this->mode++;
			break;

			// 【case1】前進値を60に設定
			case 1:
				if(Distance_check(this->distance, info->measureInfo, 200)){
					info->runnerInfo->forward = 60;
					info->runnerInfo->dashFlag = FALSE;
					info->runnerInfo->dashvol = 0;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;

			// 【case2】前進値を80に設定
			case 2:
				if(Distance_check(this->distance, info->measureInfo, 400)){
					info->runnerInfo->forward = 80;
					info->runnerInfo->dashFlag = FALSE;
					info->runnerInfo->dashvol = 0;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;

			// 【case3】オフセット値を5上げてダッシュ
			case 3:
				if(Distance_check(this->distance, info->measureInfo, 5700)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// ダッシュフラグオフ
			case 4:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// 【case4】オフセット値を5上げてダッシュ
			case 5:
				if(Distance_check(this->distance, info->measureInfo, 10500)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// ダッシュフラグオフ
			case 6:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// 【case5】オフセット値を5上げてダッシュ
			case 7:
				if(Distance_check(this->distance, info->measureInfo, 15000)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// ダッシュフラグオフ
			case 8:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// 【case6】オフセット値を5上げてダッシュ
			case 9:
				if(Distance_check(this->distance, info->measureInfo, 18000)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
				this->mode++;
			break;
			// ダッシュフラグオフ
			case 10:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// 【case7】オフセット値を5上げてダッシュ
			case 11:
				if(Distance_check(this->distance, info->measureInfo, 21500)){
					info->runnerInfo->dashFlag = TRUE;
					info->runnerInfo->dashvol = 5;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
				this->mode++;
			break;
			// ダッシュフラグオフ
			case 12:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// 【case8】減速１
			case 13:
				if(Distance_check(this->distance, info->measureInfo, 25000)){
					info->runnerInfo->forward = 50;
					info->runnerInfo->dashFlag = FALSE;
					info->runnerInfo->dashvol = 0;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// ダッシュフラグオフ
			case 14:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;

			// 【case9】減速２
			case 15:
				if(Distance_check(this->distance, info->measureInfo, 25300)){
					info->runnerInfo->forward = 20;
					info->runnerInfo->dashFlag = FALSE;
					info->runnerInfo->dashvol = 0;
					info->runnerInfo->dashlim = 0;
					this->mode++;
				}
			break;
			// ダッシュフラグオフ
			case 16:
				info->runnerInfo->dashFlag = FALSE;
				this->mode++;
			break;
		}
	}
}
