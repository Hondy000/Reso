#pragma once
#include "../../Core/Public/Common.h"
#include "InputInterface.h"
#ifdef DIRECTX						 
#include "DirectInput.h"
#endif

#ifdef DIRECTX 

#define sINPUT (std::dynamic_pointer_cast<DirectInput>(InputManager::GetInstance()->GetInput()))

#endif // DIRECTX 


class InputManager
{
public:
	~InputManager() {};

	BOOL Setup(void)
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
