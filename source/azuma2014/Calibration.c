/*******************************************************************************
**  ファイル名  ：Calibration.c
**  概要        ：キャリブレーションクラス
**  詳細        ：キャリブレーションに関する処理を行う。
*******************************************************************************/

#include "Calibration.h" /* キャリブレーション ヘッダファイル */

#define C_CALIBRATE_COUNT 1000  //光センサ値取得回数

static void Calibration_SetBlack(Calibration* this);
static void Calibration_SetWhite(Calibration* this);
static void Calibration_SetGray(Calibration* this);


/*------------------------------------------------------------------------------
--  関数名      ：Calibration_MeasureLight
--  概要        ：光測定を行う。
--              ：
--  引数        ：なし
--  戻り値      ：色取得構造体
------------------------------------------------------------------------------*/
void Calibration_MeasureLight(Calibration* this)
{
	// キャリブレーション開始サウンド
	ecrobot_sound_tone(440, 100, 95);
	/* 黒色取得処理開始 */
	// タッチセンサが押されるまで待機
	while(1)
	{
		// LCDに黒色取得準備ができたことを表示
		// EXITボタンが押下されたら灰色値に適当な値を設定し、処理を抜ける
		if(ecrobot_is_ENTER_button_pressed())
		{
			this -> gray = 550;
			return;
		}
		else
		{
			if(TouchSensor_isPressed(this->touchSensor))
			{
				systick_wait_ms(1000);
				break;
			}
		}
	}
	// 黒色を取得する
	Calibration_SetBlack(this);
	// 黒色取得完了サウンド
	ecrobot_sound_tone(554, 100, 95);
	
	/* 白色取得処理開始 */
	// タッチセンサが押されるまで待機
	while(1)
	{
		// LCDに白色取得準備ができたことを表示
		// EXITボタンが押下されたら灰色値に適当な値を設定し、処理を抜ける
		if(ecrobot_is_ENTER_button_pressed())
		{
			this -> gray = 550;
			return;
		}
		else
		{
			if(TouchSensor_isPressed(this->touchSensor))
			{
				systick_wait_ms(1000);
				break;
			}
		}
	}
	// 白色を取得する
	Calibration_SetWhite(this);
	// 白色取得完了サウンド
	ecrobot_sound_tone(659, 100, 95);
	
	/* 灰色取得処理開始 */
	// タッチセンサが押されるまで待機
	while(1)
	{
		// LCDに灰色取得準備ができたことを表示
		// EXITボタンが押下されたら灰色値に適当な値を設定し、処理を抜ける
		if(ecrobot_is_ENTER_button_pressed())
		{
			this -> gray = 550;
			return;
		}
		else
		{
			if(TouchSensor_isPressed(this->touchSensor))
			{
				systick_wait_ms(1000);
				break;
			}
		}
	}
	// 灰色を取得する
	Calibration_SetGray(this);
	// 灰色取得完了サウンド
	ecrobot_sound_tone(880, 200, 95);
	
	LCD_DisplayClear(this->lcd);
		
	// 取得結果表示
	LCD_SetPointXY(this->lcd, 3, 0);
	LCD_DisplayInt(this->lcd, this->black);
	
	LCD_SetPointXY(this->lcd, 3, 1);
	LCD_DisplayInt(this->lcd, this->white);
	
	LCD_SetPointXY(this->lcd, 3, 2);
	LCD_DisplayInt(this->lcd, this->gray);
}

/*------------------------------------------------------------------------------
--  関数名      ：Calibration_GetBlack
--  概要        ：黒色を取得する。
--              ：
--  引数        ：なし
--  戻り値      ：int			黒色取得値（10ビットA/Dコンバータ）
------------------------------------------------------------------------------*/
static void Calibration_SetBlack(Calibration* this)
{
	unsigned int i;
	unsigned long l_iCurBlack;				// 黒色取得計算値
	
	// 黒色取得計算値初期化
	l_iCurBlack = 0;
	
	// 黒色を取得する
	for (i = 0; i < C_CALIBRATE_COUNT; i++) {
		// C_CALIBRATE_COUNT回、黒値を取得
		l_iCurBlack = l_iCurBlack + LightSensor_getBrightness(this->lightSensor);
	}
	
	// 取得した黒値の平均を求める
	l_iCurBlack = l_iCurBlack / C_CALIBRATE_COUNT;
	
	this->black = l_iCurBlack;
}

/*------------------------------------------------------------------------------
--  関数名      ：Calibration_GetWhite
--  概要        ：白色を取得する。
--              ：
--  引数        ：なし
--  戻り値      ：int		白色取得値（10ビットA/Dコンバータ）
------------------------------------------------------------------------------*/
static void Calibration_SetWhite(Calibration* this)
{
	unsigned int i;
	unsigned long l_iCurWhite;				// 白色取得計算値
	
	// 白色取得計算値初期化
	l_iCurWhite = 0;
	
	// 白色を取得する
	for (i = 0; i < C_CALIBRATE_COUNT; i++) {
		// C_CALIBRATE_COUNT回、白値を取得
		l_iCurWhite = l_iCurWhite + LightSensor_getBrightness(this->lightSensor);
	}
	
	// 取得した白値の平均を求める
	l_iCurWhite = l_iCurWhite / C_CALIBRATE_COUNT;
	
	this->white = l_iCurWhite;
}

/*------------------------------------------------------------------------------
--  関数名      ：Calibration_GetGray
--  概要        ：灰色を取得する。
--              ：
--  引数        ：なし
--  戻り値      ：int		灰色取得値（10ビットA/Dコンバータ）
------------------------------------------------------------------------------*/
static void Calibration_SetGray(Calibration* this)
{
	unsigned int i;
	unsigned long l_iCurGray;				// 灰色取得計算値
	
	// 灰色取得計算値初期化
	l_iCurGray = 0;
	
	// 灰色を取得する
	for (i = 0; i < C_CALIBRATE_COUNT; i++) {
		// C_CALIBRATE_COUNT回、灰値を取得
		l_iCurGray = l_iCurGray + LightSensor_getBrightness(this->lightSensor);
	}
	
	// 取得した灰値の平均を求める
	l_iCurGray = l_iCurGray / C_CALIBRATE_COUNT;
	
	this->gray = l_iCurGray;
}
