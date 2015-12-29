#pragma	once
#ifdef DIRECTX

// ライブラリの追加
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3dx9.lib" )   // 行列演算関数とか使うため

// 拡張機能が使用されています : 右辺値のクラスが左辺値に使用されます。このワーニングを抑制する。
#pragma warning(disable: 4238)

// 非標準の拡張機能が使用されています: enum 'enum' が限定名で使用されます。このワーニングを抑制する。
#pragma warning(disable: 4482)

// インクルード
#include <windows.h>
#include <d3dx11.h>
#include <d3dx9.h>    // D3DXVECTOR3とか行列演算関数とか使うため
#include <memory>
#include <list>
#include <vector>
#include <map>
#include <math.h>

typedef D3DXVECTOR2 HFVECTOR2;
typedef D3DXVECTOR3 HFVECTOR3;
typedef D3DXVECTOR4 HFVECTOR4;
typedef D3DXMATRIX	HFMATRIX;
typedef D3DXPLANE HFPLANE;
typedef D3DXQUATERNION HFQUATERNION;
typedef D3DXCOLOR HFCOLOR;
#endif