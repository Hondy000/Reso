#pragma	once
#ifdef DIRECTX				   	  

// ���C�u�����̒ǉ�
#pragma comment( lib, "d3d11.lib" )	   

// �g���@�\���g�p����Ă��܂� : �E�Ӓl�̃N���X�����Ӓl�Ɏg�p����܂��B���̃��[�j���O��}������B
#pragma warning(disable: 4238)

// ��W���̊g���@�\���g�p����Ă��܂�: enum 'enum' �����薼�Ŏg�p����܂��B���̃��[�j���O��}������B
#pragma warning(disable: 4482)

// �C���N���[�h
#include <windows.h>
#include <memory>
#include <list>
#include <vector>
#include <map>
#include <math.h>	 

#endif