/*******************************************************************************
**  ファイル名  ：Competision.c
**  概要        ：競技クラス
**  詳細        ：
*******************************************************************************/

#include "Competision.h"



void Competision_init(Competision* this)
{
	// 処理なし
}

/*------------------------------------------------------------------------------
--  関数名      ：Competision_action
--  概要        ：競技用の処理を実行する
--              ：
--  引数        ：info  全情報
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void Competision_action(Competision* this, Info *info)
{
	LineTracer_trace(this->lineTracer, info);

	Strategy_action(this->strategy, info);

	RoboControl_control(this->roboControl);
	//Runner_run(this->runner, info);
}
