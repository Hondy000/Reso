#pragma once
#ifdef DIRECTX11
#define INCLUDE_DX11COMMON_HEADER
// ���������[�N�������Ƀf�o�b�K�ɏo�͂�����e���킩��₷������
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC                            // malloc�ɂ�郁�������[�N���o��CPP�t�@�C�����ƍs���o�͎w��
#define NEW  new(_NORMAL_BLOCK, __FILE__, __LINE__)  // new �ɂ�郁�������[�N���o��CPP�t�@�C�����ƍs���o�͎w��
#else
#define NEW  new
#endif

// ���C�u�����̒ǉ�
#pragma comment( lib, "user32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3dx9.lib" )   // �s�񉉎Z�֐��Ƃ��g������
#pragma comment(lib, "dinput8.lib")
#pragma comment( lib, "Shlwapi.lib" ) // PathFileExists �Ȃǂ� API �֐����g������
#pragma comment( lib, "winmm.lib" )   // timeGetTime ���g������

// �g���@�\���g�p����Ă��܂� : �E�Ӓl�̃N���X�����Ӓl�Ɏg�p����܂��B���̃��[�j���O��}������B
#pragma warning(disable: 4238)

// ��W���̊g���@�\���g�p����Ă��܂�: enum 'enum' �����薼�Ŏg�p����܂��B���̃��[�j���O��}������B
#pragma warning(disable: 4482)

#define STRICT              // �^�`�F�b�N�������ɍs��
#define WIN32_LEAN_AND_MEAN // �w�b�_�[���炠�܂�g���Ȃ��֐�������

// �C���N���[�h
#include <windows.h>
#include <stdio.h>
#include <d3dx11.h>
#include <d3dx9.h>    // D3DXVECTOR3�Ƃ��s�񉉎Z�֐��Ƃ��g������
#include <dinput.h>
#include <XInput.h>
#include <tchar.h>
#include <shlwapi.h>  // PathFileExists �Ȃǂ� API �֐����g������
#include <mmsystem.h> // timeGetTime ���g������
#include <wrl.h>
#include <memory>
#include <list>
#include <vector>
#include <stack>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define D3D11USER_FORMAT        DXGI_FORMAT_R8G8B8A8_UNORM

// �[�x�X�e���V���r���[�ƃV�F�[�_�[���\�[�X�r���[�̂ǂ���Ƃ��Ă��g�p�ł���悤�ɂ��邽�ߌ^���w�肵�Ȃ�
// �t�H�[�}�b�g�ɂ��Ă�DXGI_FORMAT�Q��
//#define D3D11USER_DEPTH_FORMAT  DXGI_FORMAT_R8_TYPELESS  // Direct3D11�̃T���v���ł͐ݒ肳��Ă��邪�g���Ă݂�ƃT�|�[�g���ĂȂ����ăG���[�ɂȂ�
#define D3D11USER_DEPTH_FORMAT  DXGI_FORMAT_R16_TYPELESS
//#define D3D11USER_DEPTH_FORMAT  DXGI_FORMAT_R32_TYPELESS
//#define D3D11USER_DEPTH_FORMAT  DXGI_FORMAT_R24G8_TYPE

#define UNCOMPILED_SHADER     // �t�@�C����ǂݍ���ŃR���p�C������

#define D3D11USER_F_WINDOWSTYLE WS_POPUP
#define D3D11USER_W_WINDOWSTYLE WS_BORDER | WS_CAPTION | WS_SYSMENU

#define SAFE_RELEASE(x) if( x != NULL ){ x->Release(); x = NULL; }
#define SAFE_DELETE(x)  if( x != NULL ){ delete x;  x = NULL; }
#define SAFE_DELETE_ARRAY(x)  if( x != NULL ){ delete[] x;  x = NULL; }
#define SAFE_FREE(x)  if( x != NULL ){ free( x );  x = NULL; }

#endif