/*******************************************************************************
**  ファイル名  ：LCD.c
**  概要        ：液晶表示クラス
**  詳細        ：液晶表示に関する処理を行う。
*******************************************************************************/

#include "device/LCD.h"

/* 文字表示位置に関する定数 */
#define C_MAX_POINT_X			15		// X座標：水平方向（最大）
#define C_MIN_POINT_X			0		// X座標：水平方向（最小）
#define C_MAX_POINT_Y			7		// Y座標：垂直方向（最大）
#define C_MIN_POINT_Y			0		// Y座標：垂直方向（最小）


static void LCD_SetPointX(LCD* this, int x);
static void LCD_SetPointY(LCD* this, int y);


void LCD_init(LCD* this)
{
	this->pointX = 0;
	this->pointY = 0;
}

/*------------------------------------------------------------------------------
--  関数名      ：LCD_SetPointX
--  概要        ：文字表示位置（X座標：水平方向）を設定する。
--  引数        ：int			X座標（0～15）
--  戻り値      ：なし
------------------------------------------------------------------------------*/
static void LCD_SetPointX(LCD* this, int x)
{
	int l_setX = x;

	// 下限チェック
	if (l_setX < C_MIN_POINT_X)
	{
		l_setX = C_MIN_POINT_X;
	}
	// 上限チェック
	if (l_setX > C_MAX_POINT_X)
	{
		l_setX = C_MAX_POINT_X;
	}

	this->pointX = l_setX;
}

/*------------------------------------------------------------------------------
--  関数名      ：LCD_SetPointY
--  概要        ：文字表示位置（Y座標：垂直方向）を設定する。
--  引数        ：int			Y座標（0～7）
--  戻り値      ：なし
------------------------------------------------------------------------------*/
static void LCD_SetPointY(LCD* this, int y)
{
	int l_setY = y;

	// 下限・上限チェック
	if (l_setY < C_MIN_POINT_Y)
	{
		l_setY = C_MIN_POINT_Y;
	}
	if (l_setY > C_MAX_POINT_Y)
	{
		l_setY = C_MAX_POINT_Y;
	}

	this->pointY = l_setY;
}

/*------------------------------------------------------------------------------
--  関数名      ：LCD_SetPointXY
--  概要        ：文字表示位置（Y座標：垂直方向）を設定する。
--  引数        ：int			Y座標（0～7）
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void LCD_SetPointXY(LCD* this, int x, int y)
{
	LCD_SetPointX(this, x);
	LCD_SetPointY(this, y);
}


/*------------------------------------------------------------------------------
--  関数名      ：LCD_DisplayStr
--  概要        ：指定文字列を表示する。
--  引数        ：const CHAR*	表示する文字列
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void LCD_DisplayStr(LCD* this, const CHAR* c)
{
	display_goto_xy(this->pointX, this->pointY);
	display_string(c);
	display_update();
}

/*------------------------------------------------------------------------------
--  関数名      ：LCD_DisplayHex
--  概要        ：指定された整数値を16進数で表示する。
--              ：符号なし整数値を表示したい場合は、この関数を使用してください。
--  引数        ：U32			表示する整数値
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void LCD_DisplayHex(LCD* this, U32 value)
{
	display_goto_xy(this->pointX, this->pointY);
	display_hex(value, 14);
	display_update();
}

/*------------------------------------------------------------------------------
--  関数名      ：LCD_DisplayInt
--  概要        ：指定された符号付き整数値を10進数で表示する。
--  引数        ：int			表示する整数値
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void LCD_DisplayInt(LCD* this, int value)
{
	display_goto_xy(this->pointX, this->pointY);
	display_int(value, 14);
	display_update();
}

/*------------------------------------------------------------------------------
--  関数名      ：LCD_DisplayStatus
--  概要        ：以下の内容と指定された文字列を表示する。
--              ：・システムタイマ[msec]
--              ：・バッテリ電圧[mV]
--              ：・モータ回転角度（ポートA/B/C）[度]
--              ：・A/Dセンサデータ（ポートS1/S2/S3/S4）
--              ：・Bluetooth通信状態（1:接続, 0:接続無し）
--              ：・超音波センサ[cm]
--              ：この関数の処理は負荷が高いため、低頻度（例：500msec周期）で
--              ：呼び出すようにしてください。
--  引数        ：const CHAR*	表示する文字列
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void LCD_DisplayStatus(const CHAR* msg)
{
	display_clear(0);
	ecrobot_status_monitor(msg);
}

/*------------------------------------------------------------------------------
--  関数名      ：LCD_DisplayClear
--  概要        ：ディスプレイを初期化する。
--  引数        ：
--  戻り値      ：なし
------------------------------------------------------------------------------*/
void LCD_DisplayClear(LCD* this)
{
	display_clear(0);
	display_update();
}
