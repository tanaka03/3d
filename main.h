#ifndef _MAIN_H_
#define _MAIN_H_

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")	//システム時刻取得に必要

// スクリーンの幅
const int SCREEN_WIDTH = 1280;
// スクリーンの高さ
const int SCREEN_HEIGHT = 720;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int GetFPS(void);

#endif