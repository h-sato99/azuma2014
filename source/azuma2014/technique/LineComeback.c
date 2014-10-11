/*******************************************************************************
**  ファイル名  ：LineComeback.c
**  概要        ：
**  詳細        ：
*******************************************************************************/

#include "LineComeback.h"
#define NONE						0
#define COMEBACK_FORWARD			50		// ライン復帰用前進値
#define COMEBACK_TURN				100		// ライン復帰用旋回値
#define COMEBACK_TURN_STATE			1		// ライン復帰用旋回状態
#define COMEBACK_FINISH_TIME		0		// ライン復帰用終了時間
#define COMEBACK_FINISH_DISTANCE	100		// ライン復帰用終了距離
#define COMEBACK_STOP_TIME			2000	// ライン復帰用終了時間

/*------------------------------------------------------------------------------
--  関数名      ：LineComeback_init
--  概要        ：初期化する。
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void LineComeback_init(LineComeback* this){
	this->mode = STOP;
}


/*------------------------------------------------------------------------------
--  関数名      ：LineComeback_main
--  概要        ：ライン復帰を実行する。
--              ：
--  引数        ：turnDirection（旋回方向）→0:LEFT,1以上:RIGHT
--  戻り値      ：なし
------------------------------------------------------------------------------*/
BOOL LineComeback_main(LineComeback* this,Direction turnDirection){
	switch(this->mode){
	case STOP:
		// 走行停止する
		this->orderNum = OrderList_manualRunning(this->orderList,NONE,NONE,NONE,COMEBACK_STOP_TIME,NONE);
		if(turnDirection==LEFT){
			this->mode = TURNLEFT;
			return FALSE;
		}
		this->mode = TURNRIGHT;
		return FALSE;

	case TURNLEFT:
		// 左に旋回する
		if (OrderList_checkFinished(this->orderList,this->orderNum)){
			this->orderNum = OrderList_turnOnSpotLeft(
				this->orderList,
				COMEBACK_FORWARD,
				COMEBACK_TURN,
				COMEBACK_FINISH_TIME,
				COMEBACK_FINISH_DISTANCE);
			ecrobot_sound_tone(659, 70, 95);
			LCD_SetPointXY(this->lcd, 3, 1);
			LCD_DisplayInt(this->lcd, this->orderNum);
			this->mode = TURNRIGHT;
		}
		break;

	case TURNRIGHT:
		// 右に旋回する
		if (OrderList_checkFinished(this->orderList,this->orderNum)){
			this->orderNum = OrderList_turnOnSpotRight(
				this->orderList,
				COMEBACK_FORWARD,
				COMEBACK_TURN,
				COMEBACK_FINISH_TIME,
				COMEBACK_FINISH_DISTANCE);
			ecrobot_sound_tone(659, 70, 95);
			LCD_SetPointXY(this->lcd, 3, 2);
			LCD_DisplayInt(this->lcd, this->orderNum);
			this->mode = TURNLEFT;
		}
		break;

	case LAST:
		// 色判定で黒を取得した後、最後の処理が終わるまで待機
		if (OrderList_checkFinished(this->orderList,this->orderNum)){
			ecrobot_sound_tone(400, 70, 95);
			LCD_SetPointXY(this->lcd, 3, 3);
			LCD_DisplayInt(this->lcd, this->orderNum);
			return TRUE;
		}
		return FALSE;
	}

	// 色判定を使って黒を探す
	if(ColorJudgement_judgeColor(this->colorJudgement)){
		OrderList_finishOrder(this->orderList,this->orderNum);
		this->orderNum = OrderList_manualRunning(this->orderList,NONE,NONE,NONE,COMEBACK_STOP_TIME,NONE);
		this->mode = LAST;
		return FALSE;
	}
	return FALSE;
}

