#pragma once
#include "../../Core/Public/Common.h"
#include "InputInterface.h"
#ifdef DIRECTX
#include "DierctX\DirectInput.h"
#endif

#define sINPUT (InputManager::GetInstance()->GetInput())

class InputManager
{
public:
	~InputManager() {};

	HFRESULT Setup(void)
	{
#ifdef DIRECTX
		m_spInput = std::shared_ptr<DirectInput>(new DirectInput);

#endif
		return m_spInput->Setup();
	}

	static InputManager* GetInstance(void)
	{
		static InputManager singleton;
		return &singleton;
	}

	std::shared_ptr<IBaseInput> GetInput(void)
	{
		return m_spInput;
	}

private:
	InputManager() {};
	std::shared_ptr<IBaseInput> m_spInput;
};
