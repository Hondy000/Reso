#pragma	once
#ifdef DIRECTX

// ���C�u�����̒ǉ�
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3dx9.lib" )   // �s�񉉎Z�֐��Ƃ��g������

// �g���@�\���g�p����Ă��܂� : �E�Ӓl�̃N���X�����Ӓl�Ɏg�p����܂��B���̃��[�j���O��}������B
#pragma warning(disable: 4238)

// ��W���̊g���@�\���g�p����Ă��܂�: enum 'enum' �����薼�Ŏg�p����܂��B���̃��[�j���O��}������B
#pragma warning(disable: 4482)

// �C���N���[�h
#include <windows.h>
#include <d3dx11.h>
#include <d3dx9.h>    // D3DXVECTOR3�Ƃ��s�񉉎Z�֐��Ƃ��g������
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