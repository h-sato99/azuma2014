/*******************************************************************************
**  ファイル名  ：FigureL.c
**  概要        ：
**  詳細        ：
*******************************************************************************/

#include "FigureL.h"
#define MOGUL_FORWARD			 40                 // モーグル用前進値
#define MOGUL_TURN_FORWARD		 80                 // モーグル用前進値
#define MOGUL_TURN				 100                    // モーグル用旋回値
#define MOGUL_TURN_STATE 		 1              // モーグル用旋回状態
#define MOGUL_FINISH_TIME 		 0             // モーグル用終了時間
#define MOGUL_FINISH_DISTANCE 	 100       // モーグル用終了距離
#define MOGUL_TURN_DISTANCE 	 80       // モーグル用終了距離
#define MOGUL_TARGET 	 500       // モーグル用終了距離


/*------------------------------------------------------------------------------
--  関数名      ：FigureL_init
--  概要        ：フィギュアＬを初期化する。
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void FigureL_init(FigureL* this){
	this->orderNum = 0;
	// test
	this->mode = 0;
//	this->mode = 1;
}


/*------------------------------------------------------------------------------
--  関数名      ：FigureL_main
--  概要        ：フィギュアＬ攻略を実行する。
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL FigureL_action(FigureL* this){
	//ecrobot_sound_tone(659, 70, 95);
	switch(this->mode)
	{
	case 0:
		//マニュアル走行
		ecrobot_sound_tone(659, 70, 95);
		this->orderNum = OrderList_lineTraceRunning(
				this->orderList,
				MOGUL_FORWARD,
				MOGUL_TARGET,
				//MOGUL_TURN_STATE,
				2,
				MOGUL_FINISH_TIME,
				MOGUL_FINISH_DISTANCE);
		this->mode = 1;
		break;
	case 1:
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			OrderList_turnOnSpotLeft(
					this->orderList,
					MOGUL_TURN_FORWARD,
					MOGUL_TURN,
					MOGUL_FINISH_TIME,
					MOGUL_TURN_DISTANCE);
			ecrobot_sound_tone(659, 70, 95);
			this->mode = 2;
		}
		break;
	case 2:
		//走行停止
		if (OrderList_checkFinished(this->orderList,this->orderNum))
		{
			this->orderNum = OrderList_lineTraceRunning(
					this->orderList,
					MOGUL_FORWARD,
					MOGUL_TARGET,
					MOGUL_TURN_STATE,
					MOGUL_FINISH_TIME,
					MOGUL_FINISH_DISTANCE);
			ecrobot_sound_tone(659, 70, 95);
			this->mode = 3;
		}
		break;
	case 3:
		//走行停止
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			ecrobot_sound_tone(659, 70, 95);
			this->orderNum = OrderList_manualRunning(
					this->orderList,
					0,
					0,
					0,
					2000,
					0);
		}
		break;
	case 4:
		//走行停止
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			ecrobot_sound_tone(659, 70, 95);
			return TRUE;
		}
	}

		return FALSE;
}


