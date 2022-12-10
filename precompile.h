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
#pragma comment(lib,"winmm.lib")	//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

//fbx
#pragma comment(lib,"libfbxsdk-md.lib")
#pragma comment(lib,"libxml2-md.lib")
#pragma comment(lib,"zlib-md.lib")
#include <fbxsdk.h>

#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

// �X�N���[���̕�
constexpr int SCREEN_WIDTH = 1280;
// �X�N���[���̍���
constexpr int SCREEN_HEIGHT = 720;

#endif // PRECOMPILE_H_