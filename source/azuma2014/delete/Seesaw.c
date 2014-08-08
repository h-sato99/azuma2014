///*******************************************************************************
//**  ファイル名  ：Seesaw.c
//**  概要        ：シーソークラス
//**  詳細        ：
//*******************************************************************************/
//
//#include "Seesaw.h"
//
//#define ForwardLow 60;
//#define ReverceLow -30;
//#define SetGyroLow 500;
//#define SetGyroHigh 700;
//#define ConstNumberZero 0;
//#define ConstNumberOne 1;
//#define ConstNumberTen 10;
//
///*------------------------------------------------------------------------------
//--  関数名      ：Seesaw_init
//--  概要        ：変数の初期化
//--  引数        ：なし
//--  戻り値      ：なし
//------------------------------------------------------------------------------*/
//void Seesaw_init(Seesaw* this)
//{
//	this->SeesawCount 	 = 0;		//シーソーのふるまい制御カウント
//	this->ImpactLow 	 = ConstNumberZero;		//衝撃の下限値
//	this->ImpactHight 	 = ConstNumberZero;		//衝撃の上限値
//	this->forward 		 = ConstNumberZero;		//前進値
//	this->WaitCount		 = ConstNumberZero;		//待機用変数
//	this->isFinished =FALSE;
//}
//
///*------------------------------------------------------------------------------
//--  関数名      ：ImpactDetection
//--  概要        ：衝撃判定
//--              ：
//--  引数        ：ImpactLow 衝撃判定下限値,ImpactHigh 衝撃判定上限値
//--  戻り値      ：なし
//------------------------------------------------------------------------------*/
//void ImpactDetection(Seesaw *this)
//{
//	this->RecieveGyro = GyroSensor_getAngularVelocity(this->gyroSensor);
//
//	//ImpactLowに衝撃の下限値(より少し高い値)、ImpactHightに衝撃の上限値(より少し低い値)をセットする
//	if (this->ImpactLow >= this->RecieveGyro || this->RecieveGyro >= this->ImpactHight)
//	{
//		//待機用変数初期化
//		this->WaitCount = ConstNumberZero;
//		//カウントをインクリメント
//		this->SeesawCount++;
//	}
//}
///*------------------------------------------------------------------------------
//--  関数名      ：TailUp
//--  概要        ：一定距離進むにつれて尻尾を少しずつ調節する
//--				：TailMode:0→尻尾を上げる
//--              ：TailMode:1→尻尾を下げる
//--              ：
//--  引数        ：info  全情報
//--  戻り値      ：なし
//------------------------------------------------------------------------------*/
//void TailUpDown(Seesaw *this){
//	//移動距離が一定以上になったら尻尾を上げる
//	if(this->Average - this->NewAverage >= 2
//		|| this->Average - this->NewAverage <= -2){
//		//尻尾の傾きが一定以上の場合尻尾を少し上げる
//		if(this->TailMode == 0 && this->TailAngle > this->TailTarget){
//			this->TailAngle -= ConstNumberTen;
//			this->NewAverage = this->Average;
//		}else if(this->TailMode == 1 && this->TailAngle < this->TailTarget){
//			this->TailAngle += ConstNumberTen;
//			this->NewAverage = this->Average;
//		}
//	}
//}
///*------------------------------------------------------------------------------
//--  関数名      ：Wait
//--  概要        ：Waitする。
//--              ：4msecに一回呼ばれるので、250回計1秒Waitする。
//--              ：
//--  引数        ：なし
//--  戻り値      ：なし
//------------------------------------------------------------------------------*/
//void Wait(Seesaw *this)
//{
//	this->WaitCount++;
//	this->forward = ConstNumberZero;
//	if(this->WaitCount >= 250){
//		this->SeesawCount++;
//	}
//}
//
//void Seesaw_action(Seesaw* this, Info *info)
//{
//	switch(this->SeesawCount)
//	{
//	//***************************************
//	//case0:
//	//		シーソーにぶつかったことを検知
//	//***************************************
//	case 0:
//		// 緊急停止をオフにする
//		info->runnerInfo->emergencyStopCheckFlag = FALSE;
//		//前進値、衝撃判定値を設定
//		this->forward = 10;
//		this->ImpactLow = SetGyroLow;
//		this->ImpactHight = SetGyroHigh;
//		//設定した衝撃判定値を元に衝撃判定
//		ImpactDetection(this);
//		this->WaitCount = ConstNumberZero;
//		break;
//	//***************************************
//	//case1:
//	//		バックする
//	//***************************************
//	case 1:
//		this->forward = -20;
//		this->StrageAverage = WheelAverage_action(this->wheelAverage);
//		this->SeesawCount++;
//		info->runnerInfo->gyroOffset = info->runnerInfo->gyroOffset - 5;
//		info->runnerInfo->turn = 0;
//		info->settingInfo->lineTraceFlg = FALSE;
//		ecrobot_sound_tone(400, 100, 95);
//		break;
//	//***************************************
//	//case2:
//	//		ダッシュしてシーソーに乗り上げる
//	//***************************************
//	case 2:
//		this->Average = WheelAverage_action(this->wheelAverage);
//		if(this->Average - this->StrageAverage < -80)
//		{
//			this->StrageAverage = WheelAverage_action(this->wheelAverage);
//			this->forward = 50;
//			info->runnerInfo->gyroOffset = info->runnerInfo->gyroOffset + 5;
//			this->SeesawCount++;
//		}
//		break;
//	//***************************************
//	//case3:
//	//		ホイール平均値の基準を取得
//	//***************************************
//	case 3:
//		this->Average = WheelAverage_action(this->wheelAverage);
//		if(this->Average - this->StrageAverage >= 100)
//		{
//			this->StrageAverage = WheelAverage_action(this->wheelAverage);
//			this->SeesawCount++;
//		}
//		break;
//
//	//***************************************
//	//case4:
//	//		シーソーシングル
//	//***************************************
//	case 4:
//		this->forward = 20;
//		info->runnerInfo->turn = -1;
//		this->Average = WheelAverage_action(this->wheelAverage);
//		if(this->Average - this->StrageAverage >= 450)
//		{
//			this->SeesawCount++;
//		}
//		break;
//	//***************************************
//	//case5:
//	//		停止して1秒待機
//	//***************************************
//	case 5:
//		this->forward = 0;
//		info->runnerInfo->turn = 0;
//		Wait(this);
//		break;
//	//***************************************
//	//case6:
//	//		ホイール平均値の基準を取得
//	//***************************************
//	case 6:
//		this->StrageAverage = WheelAverage_action(this->wheelAverage);
//		this->SeesawCount++;
//		ecrobot_sound_tone(500, 100, 95);
//		break;
//	//***************************************
//	//case7:
//	//		バック
//	//***************************************
//	case 7:
//		this->forward = -30;
//		this->Average = WheelAverage_action(this->wheelAverage);
//		if(this->Average - this->StrageAverage <= -300)
//		{
//			this->SeesawCount++;
//		}
//		break;
//	//***************************************
//	//case8:
//	//		停止して1秒待機
//	//***************************************
//	case 8:
//		this->forward = 0;
//		Wait(this);
//		break;
//	//***************************************
//	//case9:
//	//		ホイール平均値の基準を取得
//	//***************************************
//	case 9:
//		this->StrageAverage = WheelAverage_action(this->wheelAverage);
//		this->SeesawCount++;
//		ecrobot_sound_tone(700, 100, 95);
//		break;
//	//***************************************
//	//case10:
//	//		シーソーダブル＆そのまま前進
//	//***************************************
//	case 10:
//		this->forward = 20;
//		info->runnerInfo->turn = -1;
//		this->Average = WheelAverage_action(this->wheelAverage);
//		if(this->Average - this->StrageAverage > 500)
//		{
//			this->SeesawCount++;
//		}
//		break;
//	//***************************************
//	//default:
//	//		シーソーの終了
//	//***************************************
//	default:
//		info->runnerInfo->emergencyStopCheckFlag = TRUE;
//		info->settingInfo->lineTraceFlg = TRUE;
//		this->isFinished =TRUE;
//	}
//
//	// 前進値を走行情報に渡す
//	info->runnerInfo->forward = this->forward;
//}
//
//BOOL Seesaw_checkFinish(Seesaw* this)
//{
//	return this->isFinished;
//}
//
///*------------------------------------------------------------------------------
//--  関数名      ：Seesaw_action
//--  概要        ：シーソー用の処理を実行する
//--              ：case0～case1:  シーソー乗り上げ
//--              ：case2～case5:  シーソーシングル
//--              ：case6～case9:  シーソーダブル
//--              ：case10～case11:シーソーから降りる
//--  引数        ：info  全情報
//--  戻り値      ：なし
//------------------------------------------------------------------------------*/
//void Seesaw_action_bk(Seesaw* this, Info *info)
//{
//	switch(this->SeesawCount)
//	{
//	//***************************************
//	//case0:
//	//		シーソーに乗り上げたことを検知
//	//***************************************
//	case 0:
//		//前進値、衝撃判定値を設定
//		this->forward = ForwardLow;
//		this->ImpactLow = SetGyroLow;
//		this->ImpactHight = SetGyroHigh;
//		//設定した衝撃判定値を元に衝撃判定
//		ImpactDetection(this);
//		this->WaitCount = ConstNumberZero;
//		break;
//	//***************************************
//	//case1:
//	//		1秒待機
//	//***************************************
//	case 1:
//		this->forward = 10;
//		this->WaitCount++;
//		if(this->WaitCount >= 500){
//			this->SeesawCount++;
//		}
//		break;
//
//	//***************************************
//	//case2:
//	//		ホイールの値を取得し、平均を変数に格納
//	//		尻尾を下ろす
//	//***************************************
//	case 2:
//		this->forward = ForwardLow;
//		//ホイールの値取得、平均値の計算
//		this->StrageAverage = WheelAverage_action(this->wheelAverage);
//		//尻尾の角度を調節
//		this->TailAngle = 120;
//		info->runnerInfo->balanceFlag = FALSE;
//		//次の処理へ
//		this->SeesawCount++;
//		this->WaitCount = ConstNumberZero;
//		break;
//	case 3:
//		Wait(this);
//		break;
//	case 4:
//	//***************************************
//	//case3:
//	//		両車輪の平均の差を取得
//	//		最新の車輪平均と保持用車輪平均の差が一定以上になるまで前進
//	//***************************************
//		this->forward = 30;
//		this->SeesawCount++;
//	case 5:
//	//***************************************
//	//case4:
//	//		両車輪の平均の差を取得
//	//		走行体が一定距離進むごとに尻尾を調節
//	//***************************************
//		display_goto_xy(1, 1);
//		display_int(this->SeesawCount, 14);
//		display_update();
//		display_goto_xy(1, 2);
//		display_int(this->StrageAverage, 14);
//		display_update();
//		display_goto_xy(1, 3);
//		display_int(this->Average, 14);
//		display_update();
//		//ホイールの値取得、平均値の計算
//		this->Average = WheelAverage_action(this->wheelAverage);
//		this->TailMode = ConstNumberZero;
//		//this->LengthTarget = 1000;
//		if(this->Average - this->StrageAverage >= 550){
//			this->TailAngle = 50;
//			this->WaitCount = ConstNumberZero;
//			this->SeesawCount++;
//		}else if (this->Average - this->StrageAverage >= 500){
//			this->TailAngle = 60;
//		}else if (this->Average - this->StrageAverage >= 450){
//			this->TailAngle = 80;
//		}
//		break;
//	case 6:
//	//***************************************
//	//case5:
//	//		1秒待機
//	//***************************************
//		Wait(this);
//		break;
//	case 7:
//	//***************************************
//	//case6:
//	//		両車輪の平均の差を取得
//	//		走行体が一定距離進むごとに尻尾を調節
//	//***************************************
//		//ホイールの値取得、平均値の計算
//		this->Average = WheelAverage_action(this->wheelAverage);
//		this->forward =  ReverceLow;
//		this->TailMode = ConstNumberOne;
//		this->TailAngle = 50;
//		if (this->Average - this->StrageAverage <= 320){
//			this->TailAngle = 120;
//			this->WaitCount = ConstNumberZero;
//			ecrobot_sound_tone(659, 100, 95);
//			this->SeesawCount++;
//		}else if(this->Average - this->StrageAverage <= 400){
//			this->TailAngle = 80;
//		}else if(this->Average - this->StrageAverage <= 500){
//			this->TailAngle = 60;
//		}else if(this->Average - this->StrageAverage <= 550){
//			this->TailAngle = 50;
//		}
//		break;
//
//	case 8:
//	//***************************************
//	//case7:
//	//		1秒待機
//	//***************************************
//		Wait(this);
//		break;
//	case 9:
//	//***************************************
//	//case8:
//	//		両車輪の平均の差を取得
//	//		走行体が一定距離進むごとに尻尾を調節
//	//***************************************
//		//ホイールの値取得、平均値の計算
//		this->Average = WheelAverage_action(this->wheelAverage);
//		this->forward = 30;
//		this->TailMode = ConstNumberZero;
//		this->TailTarget = 50;
//		//最新の車輪平均と保持用車輪平均の差が一定以上になるまで前進
//		if(this->Average - this->StrageAverage >= 600){
//			this->TailAngle = 40;
//			this->WaitCount = ConstNumberZero;
//			this->NewAverage = this->Average;
//			this->SeesawCount++;
//		}else if (this->Average - this->StrageAverage >= 550){
//			this->TailAngle = 60;
//		}else if (this->Average - this->StrageAverage >= 450){
//			this->TailAngle = 80;
//		}
//		break;
//	case 10:
//	//***************************************
//	//case9:
//	//		1秒待機
//	//***************************************
//		Wait(this);
//		break;
//	//***************************************
//	//case10:
//	//		シーソーに乗り上げたことを検知
//	//***************************************
//	case 11:
//		//前進値、衝撃判定値を設定
//		this->forward = ForwardLow;
//		this->ImpactLow = SetGyroLow;
//		this->ImpactHight = SetGyroHigh;
//		//設定した衝撃判定値を元に衝撃判定
//		ImpactDetection(this);
//		break;
//	//***************************************
//	//case11:
//	//		1秒待機
//	//***************************************
//	case 12:
//		Wait(this);
//		break;
//	default:
//	//***************************************
//	//Defaut:
//	//		Return
//	//***************************************
//		break;
//	}
//	// 前進値を走行情報に渡す
//	info->runnerInfo->forward = this->forward;
//	info->runnerInfo->tail = this->TailAngle;
//}
//
