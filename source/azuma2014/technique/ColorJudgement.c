/*******************************************************************************
**  ファイル名  ：ColorJudgement.c
**  概要        ：
**  詳細        ：
*******************************************************************************/

#include "ColorJudgement.h"
#define LIGHT_BLACK  570	// 黒色の光センサ値


/*------------------------------------------------------------------------------
--  関数名      ：ColorJudgement_init
--  概要        ：色判定を初期化する。
--              ：
--  引数        ：なし
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void ColorJudgement_init(ColorJudgement* this){
	this->threshold = LIGHT_BLACK;
}


/*------------------------------------------------------------------------------
--  関数名      ：ColorJudgement_main
--  概要        ：色判定する。
--              ：
--  引数        ：なし
--  戻り値      ：TRUE or FALSE
------------------------------------------------------------------------------*/
BOOL ColorJudgement_judgeColor(ColorJudgement* this){
	// 光センサからの取得値を見て
	// 黒以上であれば「TRUE」を、
	// そうでなければ「FALSE」を返す
	if(LightSensor_getBrightness(this->lightSensor) >= this->threshold){
		return  TRUE;
	}
	return FALSE;
} 

