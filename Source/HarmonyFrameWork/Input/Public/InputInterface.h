#pragma once
#include "../../Core/Public/Common.h"

enum HF_MOUSE_ENUM
{
	HFM_LEFT,
	HFM_RIGHT,
	HFM_CENTER,
};

class IBaseInput
{
public:
	IBaseInput()
	{
	};

	~IBaseInput()
	{
	};

	virtual BOOL Setup(void) = 0;

	virtual BOOL IsTriggerKeyboard(BYTE numDIK) = 0;
	virtual BOOL IsHoldKeyboard(BYTE numDIK) = 0;
	virtual BOOL IsReleaseKeyboard(BYTE numDIK) = 0;
	virtual BOOL IsRepeatKeyboard(BYTE numDIK, WORD frame) = 0;

	virtual BOOL IsHoldMouse(HF_MOUSE_ENUM) = 0;
	virtual BOOL IsReleaseMouse(HF_MOUSE_ENUM) = 0;
	virtual LONG IsMouseAxisX(void) = 0;
	virtual LONG IsMouseAxisY(void) = 0;
	virtual INT IsMouseWheel(void) = 0;

	virtual BOOL Update(void) = 0;
	virtual void UpdateKeyBoard(void) = 0;
	virtual void UpdateMouse(void) = 0;
	//virtual void UpdatePad(void) = 0;
private:
};
