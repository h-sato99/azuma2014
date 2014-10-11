/*******************************************************************************
**  ファイル名  ：Mogul.c
**  概要        ：
**  詳細        ：
*******************************************************************************/

#include "Mogul.h"
#define MOGUL_FORWARD			 40                 // モーグル用前進値
#define MOGUL_TURN				 1                    // モーグル用旋回値
#define MOGUL_TURN_STATE 		 0              // モーグル用旋回状態
#define MOGUL_FINISH_TIME 		 0             // モーグル用終了時間
#define MOGUL_FINISH_DISTANCE 	 200       // モーグル用終了距離

#define NONE					0
#define MOGUL_STOP_TIME			200
int i = 0;

/*------------------------------------------------------------------------------
--  関数名      ：Mogul_init
--  概要        ：モーグル攻略を初期化する。
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Mogul_init(Mogul* this){
	this->orderNum = 0;
	this->mode = 0;
}


/*------------------------------------------------------------------------------
--  関数名      ：Mogul_main
--  概要        ：モーグル攻略を実行する。
--              ：
--  引数        ：なし
--  戻り値      ：BOOL
------------------------------------------------------------------------------*/
BOOL Mogul_main(Mogul* this){
	switch(this->mode)
	{
	case 0:
		//マニュアル走行
		this->orderNum = OrderList_manualRunning(
				this->orderList,
				MOGUL_FORWARD,
				MOGUL_TURN,
				MOGUL_TURN_STATE,
				MOGUL_FINISH_TIME,
				MOGUL_FINISH_DISTANCE);
		this->mode = 1;
		break;
	case 1:
		if(OrderList_checkFinished(this->orderList, this->orderNum)){
			this->orderNum = OrderList_manualRunning(this->orderList,NONE,NONE,NONE,MOGUL_STOP_TIME,NONE);
			this->mode = 2;
		}
		break;
	case 2:
		if (OrderList_checkFinished(this->orderList,this->orderNum)){
			return TRUE;
		}
	}
	return FALSE;
}


