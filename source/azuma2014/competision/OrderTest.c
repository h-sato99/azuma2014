/*******************************************************************************
**  ファイル名  ：OrderTest.c
**  概要        ：
**  詳細        ：
*******************************************************************************/

#include "OrderTest.h"
#define MOGUL_FORWARD			 40                 // モーグル用前進値
#define MOGUL_TURN				 1                    // モーグル用旋回値
#define MOGUL_TURN_STATE 		 0              // モーグル用旋回状態
#define MOGUL_FINISH_TIME 		 0             // モーグル用終了時間
#define MOGUL_FINISH_DISTANCE 	 200       // モーグル用終了距離


/*------------------------------------------------------------------------------
--  関数名      ：OrderTest_init
--  概要        ：モーグル攻略を初期化する。
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void OrderTest_init(OrderTest* this){
	this->orderNum = 0;
	this->mode = 0;
}


/*------------------------------------------------------------------------------
--  関数名      ：OrderTest_main
--  概要        ：モーグル攻略を実行する。
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL OrderTest_tailRun(OrderTest* this){
	switch(this->mode)
	{
	case 0:
		//マニュアル走行
		this->orderNum = OrderList_manualRunning(
				this->orderList,
				-80,
				0,
				TURN_DRIVING,
				0,
				50);
		this->mode = 1;
		break;
	case 1:
		//走行停止
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_manualRunning(
					this->orderList,
					100,
					0,
					TURN_DRIVING,
					0,
					70);
			this->mode = 2;
		}
		break;
	case 2:
		this->orderNum = OrderList_manualRunning(
				this->orderList,
				0,
				0,
				TURN_DRIVING,
				0,
				0);
		return TRUE;

	}
	return FALSE;
}

BOOL OrderTest_figureL(OrderTest* this){
	switch(this->mode)
	{
	case 0:
		//マニュアル走行
		this->orderNum = OrderList_manualRunning(
				this->orderList,
				50,
				0,
				TURN_FRONT,
				0,
				100);
		this->mode = 1;
		break;
	case 1:
		//走行停止
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_manualRunning(
					this->orderList,
					50,
					100,
					TURN_FRONT,
					0,
					500);
			this->mode = 2;
		}
		break;
	case 2:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_manualRunning(
					this->orderList,
					50,
					0,
					TURN_FRONT,
					0,
					0);
			this->mode = 3;
		}
		break;
	case 3:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_manualRunning(
					this->orderList,
					50,
					0,
					TURN_FRONT,
					0,
					0);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL OrderTest_strateRun(OrderTest* this)
{
	switch(this->mode)
	{
	case 0:
		//マニュアル走行
		this->orderNum = OrderList_setPID(this->orderList,5,7,20);
		this->mode = 1;
		break;
	case 1:
		//マニュアル走行
		this->orderNum = OrderList_lineTraceRunning(
				this->orderList,
				50,
				550,
				TURN_DRIVING,
				0,
				0);
		this->mode = 2;
		break;
	}
	return FALSE;
}

