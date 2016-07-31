#pragma	once
#ifdef DIRECTX				   	  

// ライブラリの追加
#pragma comment( lib, "d3d11.lib" )	   

// 拡張機能が使用されています : 右辺値のクラスが左辺値に使用されます。このワーニングを抑制する。
#pragma warning(disable: 4238)

// 非標準の拡張機能が使用されています: enum 'enum' が限定名で使用されます。このワーニングを抑制する。
#pragma warning(disable: 4482)

// インクルード
#include <windows.h>
#include <memory>
#include <list>
#include <vector>
#include <map>
#include <math.h>	 

#endif