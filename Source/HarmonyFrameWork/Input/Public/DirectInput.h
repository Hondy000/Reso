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

	bool Setup(void);
	bool IsTriggerKeyboard(BYTE numDIK);
	bool IsHoldKeyboard(BYTE numDIK);
	bool IsReleaseKeyboard(BYTE numDIK);
	bool IsRepeatKeyboard(BYTE numDIK, WORD frame);

	bool IsHoldMouse(HF_MOUSE_ENUM);
	bool IsReleaseMouse(HF_MOUSE_ENUM);
	LONG MouseAxisX(void);
	LONG IsMouseAxisY(void);
	INT IsMouseWheel(void);

	bool Update(void);
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
