///*******************************************************************************
//**  ファイル名  ：GarageIn.c
//**  概要        ：ガレージインクラス
//**  詳細        ：
//*******************************************************************************/
//
//#include "GarageIn.h"
//
//#define STOP     	    	0 		// 停止
//#define LOW     	    	20 		// 低速
//#define TAIL_ANGL			90		// 尻尾の角度
//#define DISTANCE_OF_SEESAW 	720  	// シーソーからの移動距離
//#define DISTANCE_OF_LOOKUP 	2900  	// ルックアップゲートからの移動距離
//
//void GrageIn_init(GarageIn* this)
//{
//	this->isInitialized	= FALSE; 					// 初期化フラグ
//	this->forward		= LOW;   					// 前進値
//	this->turn			= -1;						// 旋回値
//	this->tAngle		= TAIL_ANGL;				// 尻尾角度
//}
//
///*------------------------------------------------------------------------------
//--  関数名      ：GarageIn_action
//--  概要        ：ガレージイン用の処理を実行する
//--              ：
//--  引数        ：info  全情報
//--  戻り値      ：なし
//------------------------------------------------------------------------------*/
//void GarageIn_action(GarageIn* this, Info* info)
//{
//	this->turn = 0;
//	this->tAngle = TAIL_ANGL;
//	this->forward = LOW;
//
//	// 初期化(スタート時間の取得)
//	if(! this->isInitialized)
//	{
//		// モータの値ををリセット
//		Distance_set(this->distance, info->measureInfo);
//		// 初期化済にする
//		this->isInitialized = TRUE;
//	}
//
//
//	// アウトコースの場合
//	if (info->settingInfo->courseType == 0)
//	{
//		// シーソーからガレージインまで進んだ場合
//		if (Distance_check(this->distance, info->measureInfo, DISTANCE_OF_SEESAW))
//		{
//			info->runnerInfo->turn = this->turn;
//			info->runnerInfo->tail = this->tAngle;
//			info->runnerInfo->balanceFlag = FALSE;
//			info->settingInfo->lineTraceFlg = FALSE;
//			this->forward = STOP;
//		}
//	}
//	// インコースの場合
//	else
//	{
//		// ルックアップゲートからガレージインまで進んだ場合
//		if (Distance_check(this->distance, info->measureInfo, DISTANCE_OF_LOOKUP))
//		{
//			info->runnerInfo->turn = this->turn;
//			info->runnerInfo->tail = this->tAngle;
//			info->runnerInfo->balanceFlag = FALSE;
//			info->settingInfo->lineTraceFlg = FALSE;
//			this->forward = STOP;
//		}
//	}
//	info->runnerInfo->forward = this->forward;
//}
