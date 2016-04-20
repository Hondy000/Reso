/**********************************************************************************************//**
																								* @file	Input.cpp
																								*
																								* @brief	Implements the input class.
																								**************************************************************************************************/

#include "../Public/DirectInput.h"
#ifdef DIRECTX

																								/**********************************************************************************************//**
																								 * @fn	CDirectInput::CDirectInput()
																								 *
																								 * @brief	Default constructor.
																								 *
																								 * @author	Kazuyuki
																								 * @date	2015/04/08
																								 **************************************************************************************************/

DirectInput::DirectInput()
{
}

/**********************************************************************************************//**
 * @fn	CDirectInput::~CDirectInput()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki
 * @date	2015/04/08
 **************************************************************************************************/

DirectInput::~DirectInput()
{
}

/**********************************************************************************************//**
 * @fn	bool CDirectInput::Setup(void)
 *
 * @brief	Initialises the dinput.
 *
 * @author	Kazuyuki
 * @date	2015/04/08
 *
 * @return	A bool.
 **************************************************************************************************/

bool DirectInput::Setup(void) {
	HRESULT hr = E_FAIL;
	HWND hWnd = GetActiveWindow();
	//	DirectInput オブジェクトの作成
	hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)m_cpDirectInput.GetAddressOf(), NULL);

	//DirectInputデバイス オブジェクトの作成
	hr = m_cpDirectInput->CreateDevice(GUID_SysKeyboard, &pdInDeviceKeyBoard, NULL);

	//デバイスをキーボードに入力
	if (FAILED(hr = pdInDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard)))
	{
	}

	//協調レベルの設定
	if (FAILED(hr = pdInDeviceKeyBoard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND))) {
	}

	pdInDeviceKeyBoard->Acquire();

	//DirectInputデバイス オブジェクトの作成
	if (FAILED(hr = m_cpDirectInput->CreateDevice(GUID_SysMouse, &pdInDeviceMouse, NULL))) {
	}

	// データフォーマットをセット
	if (FAILED(hr = pdInDeviceMouse->SetDataFormat(&c_dfDIMouse2)))
	{
	}

	//協調レベルの設定
	if (FAILED(hr = pdInDeviceMouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_BACKGROUND))) {
	}

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL;
	pdInDeviceMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
	pdInDeviceMouse->Acquire();
	return true;
}

/**********************************************************************************************//**
 * @fn	bool CDirectInput::Update(void)
 *
 * @brief	更新処理.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool DirectInput::Update(void)
{
	UpdateKeyBoard();
	UpdateMouse();
	return true;
}

// キーボード

/**********************************************************************************************//**
 * @fn	void CDirectInput::UpdateKeyBoard(void)
 *
 * @brief	Updates the information key board.
 *
 * @author	Kazuyuki
 * @date	2015/04/08
 **************************************************************************************************/

void DirectInput::UpdateKeyBoard(void)
{
	memcpy((BYTE*)oldInfoKB, (BYTE*)infoKB, sizeof(infoKB));
	pdInDeviceKeyBoard->GetDeviceState(sizeof(infoKB), &infoKB);
}

// マウス

/**********************************************************************************************//**
 * @fn	void CDirectInput::UpdateMouse(void)
 *
 * @brief	Updates the information mouse.
 *
 * @author	Kazuyuki
 * @date	2015/04/08
 **************************************************************************************************/

void DirectInput::UpdateMouse(void)
{
	oldInfoMouse = infoMouse;
	if (FAILED(pdInDeviceMouse->GetDeviceState(sizeof(infoMouse), &infoMouse))) {
		pdInDeviceMouse->Acquire();
	}
}

/**********************************************************************************************//**
 * @fn	bool CDirectInput::IsHoldKeyboard(BYTE numDIK)
 *
 * @brief	Judge hold key board.
 *
 * @author	Kazuyuki
 * @date	2015/04/08
 *
 * @param	numDIK	Number of diks.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool DirectInput::IsHoldKeyboard(BYTE numDIK) {
	if (infoKB[numDIK] & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**********************************************************************************************//**
 * @fn	bool CDirectInput::IsTriggerKeyboard(BYTE numDIK)
 *
 * @brief	Judge trig key board.
 *
 * @author	Kazuyuki
 * @date	2015/04/08
 *
 * @param	numDIK	Number of diks.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool DirectInput::IsTriggerKeyboard(BYTE numDIK)
{
	if ((infoKB[numDIK] & (oldInfoKB[numDIK] ^ 0xff)) & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**********************************************************************************************//**
 * @fn	bool CDirectInput::IsReleaseKeyboard(BYTE numDIK)
 *
 * @brief	Judge release key board.
 *
 * @author	Kazuyuki
 * @date	2015/04/08
 *
 * @param	numDIK	Number of diks.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool DirectInput::IsReleaseKeyboard(BYTE numDIK)
{
	if (((infoKB[numDIK] ^ 0xff) & (oldInfoKB[numDIK])) & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**********************************************************************************************//**
 * @fn	bool CDirectInput::IsRepeatKeyboard(BYTE numDIK, WORD count)
 *
 * @brief	Judge repeat count.
 *
 * @author	Kazuyuki
 * @date	2015/04/08
 *
 * @param	numDIK	Number of diks.
 * @param	count 	Number of.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool DirectInput::IsRepeatKeyboard(BYTE numDIK, WORD count) {
	if ((infoKB[numDIK] & oldInfoKB[numDIK]) & 0x80)
	{
		if (repeatCount[numDIK] < 255)
		{
			repeatCount[numDIK]++;
		}
	}
	else
	{
		repeatCount[numDIK] = 0;
	}

	if (count <= repeatCount[numDIK])
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**********************************************************************************************//**
 * @fn	bool CDirectInput::IsHoldMouse(HF_MOUSE_ENUM button)
 *
 * @brief	Gets hold mouse.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	button	The first parameter.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool DirectInput::IsHoldMouse(HF_MOUSE_ENUM button)
{
	if (infoMouse.rgbButtons[button] & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**********************************************************************************************//**
 * @fn	bool CDirectInput::IsReleaseMouse(HF_MOUSE_ENUM button)
 *
 * @brief	Determines if we can judge release mouse left.
 *
 * @author	Kazuyuki
 * @date	2015/04/08
 *
 * @param	button	The first parameter.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool DirectInput::IsReleaseMouse(HF_MOUSE_ENUM button)
{
	if (((infoMouse.rgbButtons[button] ^ 0xff) & (oldInfoMouse.rgbButtons[button])) & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**********************************************************************************************//**
 * @fn	LONG CDirectInput::IsMouseAxisX(void)
 *
 * @brief	Gets mouse axis x coordinate.
 *
 * @author	Kazuyuki
 * @date	2015/04/08
 *
 * @return	The mouse axis x coordinate.
 **************************************************************************************************/

LONG DirectInput::MouseAxisX(void)
{
	return infoMouse.lX;
}

/**********************************************************************************************//**
 * @fn	LONG CDirectInput::IsMouseAxisY(void)
 *
 * @brief	Gets mouse axis y coordinate.
 *
 * @author	Kazuyuki
 * @date	2015/04/08
 *
 * @return	The mouse axis y coordinate.
 **************************************************************************************************/

LONG DirectInput::IsMouseAxisY(void)
{
	return infoMouse.lY;
}

/**********************************************************************************************//**
 * @fn	INT CDirectInput::IsMouseWheel(void)
 *
 * @brief	Gets the wheel.
 *
 * @author	Kazuyuki
 * @date	2015/04/08
 *
 * @return	The wheel.
 **************************************************************************************************/

INT DirectInput::IsMouseWheel(void)
{
	return infoMouse.lZ;
}

#endif