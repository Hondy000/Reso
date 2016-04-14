#pragma once
#include "InputInterface.h"

#define DIK_MAX (DIK_MEDIASELECT + 1)
#define LOCAL_PLAYER_MAX (4)

class DirectInput
	:public IBaseInput
{
public:
	DirectInput();
	~DirectInput();

	BOOL Setup(void);
	BOOL IsTriggerKeyboard(BYTE numDIK);
	BOOL IsHoldKeyboard(BYTE numDIK);
	BOOL IsReleaseKeyboard(BYTE numDIK);
	BOOL IsRepeatKeyboard(BYTE numDIK, WORD frame);

	BOOL IsHoldMouse(HF_MOUSE_ENUM);
	BOOL IsReleaseMouse(HF_MOUSE_ENUM);
	LONG IsMouseAxisX(void);
	LONG IsMouseAxisY(void);
	INT IsMouseWheel(void);

	BOOL Update(void);
	void UpdateKeyBoard(void);
	void UpdateMouse(void);

private:

	Microsoft::WRL::ComPtr< IDirectInput> m_cpDirectInput;
	LPDIRECTINPUTDEVICE pdInDeviceKeyBoard;		// キーボード用
	LPDIRECTINPUTDEVICE pdInDeviceMouse;		// マウス用

	BYTE infoKB[256];
	BYTE oldInfoKB[256];
	BYTE repeatCount[DIK_MAX];

	DIMOUSESTATE2 infoMouse;
	DIMOUSESTATE2 oldInfoMouse;

	XINPUT_STATE xInputStatus[LOCAL_PLAYER_MAX];
};
