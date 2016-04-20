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

	virtual bool Setup(void) = 0;

	virtual bool IsTriggerKeyboard(BYTE numDIK) = 0;
	virtual bool IsHoldKeyboard(BYTE numDIK) = 0;
	virtual bool IsReleaseKeyboard(BYTE numDIK) = 0;
	virtual bool IsRepeatKeyboard(BYTE numDIK, WORD frame) = 0;

	virtual bool IsHoldMouse(HF_MOUSE_ENUM) = 0;
	virtual bool IsReleaseMouse(HF_MOUSE_ENUM) = 0;
	virtual LONG MouseAxisX(void) = 0;
	virtual LONG IsMouseAxisY(void) = 0;
	virtual INT IsMouseWheel(void) = 0;

	virtual bool Update(void) = 0;
	virtual void UpdateKeyBoard(void) = 0;
	virtual void UpdateMouse(void) = 0;
	//virtual void UpdatePad(void) = 0;
private:
};
