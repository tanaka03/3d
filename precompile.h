#ifndef PRECOMPILE_H_
#define PRECOMPILE_H_

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <assert.h>
#include <tchar.h> 
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")	//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

// スクリーンの幅
constexpr int SCREEN_WIDTH = 1280;
// スクリーンの高さ
constexpr int SCREEN_HEIGHT = 720;

#endif // PRECOMPILE_H_