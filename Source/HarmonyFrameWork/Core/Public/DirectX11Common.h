#pragma once
#ifdef DIRECTX11
#define INCLUDE_DX11COMMON_HEADER

// DirectSDK内部のマクロ再定義警告がうっとうしい
#pragma warning(disable: 4005)			  
// 拡張機能が使用されています : 右辺値のクラスが左辺値に使用されます。このワーニングを抑制する。
#pragma warning(disable: 4238)

// 非標準の拡張機能が使用されています: enum 'enum' が限定名で使用されます。このワーニングを抑制する。
#pragma warning(disable: 4482)

// ライブラリの追加
#pragma comment( lib, "user32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment(lib, "dinput8.lib")
#pragma comment( lib, "Shlwapi.lib" ) // PathFileExists などの API 関数を使いたい
#pragma comment( lib, "winmm.lib" )   // timeGetTime を使いたい	 
#ifdef DIRECTXTEX		
#pragma comment(lib,"DirectXTex.lib")	
#endif
#ifdef DIRECTXTK
#pragma comment(lib,"DirectXTK.lib")	 			
#endif
#pragma comment(lib,"d3dcompiler.lib")
#define STRICT              // 型チェックを厳密に行う
#define WIN32_LEAN_AND_MEAN // ヘッダーからあまり使われない関数を除く


// インクルード
#include <windows.h>
#include <stdio.h>
#include <d3d11.h>
#include <dxgi.h>		 	  
#include <Winstring.h>
#include <d3dcompiler.h>   
#ifdef DIRECTXTEX
#include <DirectXTex.h>
#endif
#include <dinput.h>
#include <XInput.h>
#include <tchar.h>

#include <shlwapi.h>  // PathFileExists などの API 関数を使いたい
#include <mmsystem.h> // timeGetTime を使いたい
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

// 深度ステンシルビューとシェーダーリソースビューのどちらとしても使用できるようにするため型を指定しない
// フォーマットについてはDXGI_FORMAT参照
//#define D3D11USER_DEPTH_FORMAT  DXGI_FORMAT_R8_TYPELESS  // Direct3D11のサンプルでは設定されているが使ってみるとサポートしてないってエラーになる
#define D3D11USER_DEPTH_FORMAT  DXGI_FORMAT_R16_TYPELESS
//#define D3D11USER_DEPTH_FORMAT  DXGI_FORMAT_R32_TYPELESS
//#define D3D11USER_DEPTH_FORMAT  DXGI_FORMAT_R24G8_TYPE

#define UNCOMPILED_SHADER     // ファイルを読み込んでコンパイルする

#define D3D11USER_F_WINDOWSTYLE WS_POPUP
#define D3D11USER_W_WINDOWSTYLE WS_BORDER | WS_CAPTION | WS_SYSMENU

#define SAFE_RELEASE(x) if( x != NULL ){ x->Release(); x = NULL; }
#define SAFE_DELETE(x)  if( x != NULL ){ delete x;  x = NULL; }
#define SAFE_DELETE_ARRAY(x)  if( x != NULL ){ delete[] x;  x = NULL; }
#define SAFE_FREE(x)  if( x != NULL ){ free( x );  x = NULL; }

#endif