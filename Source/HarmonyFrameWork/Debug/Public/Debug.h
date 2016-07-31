#pragma once			 
#include "..\..\Utility\Public\HFString.h"

#define CONSOLE_LOG(fmt,...) (HFDebug::Debug::Debug::GetInstance()->ConsoleLog(fmt, __VA_ARGS__));

namespace HFDebug
{
	class Debug
	{
	public:
		~Debug();
		static Debug* GetInstance() 
		{
			static Debug instance;
			return &instance;
		}
	private:
		Debug();
		static FILE* m_fp;
	public:

		// �R���\�[����ʕ\��
		void StartConsole();
		// �R���\�[���I���
		void EndConsole();


		void SetConsoleTextGray()
		{
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		}

		void SetConsoleTextRed()
		{
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
		}

		void SetConsoleTextGreen()
		{
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		}

		void SetConsoleTextWhite()
		{
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		}


		// �R���\�[���Ƀ��O���o��
		template<typename... Args>
		void ConsoleLog(const Args&... args)
		{
//#if defined(DEBUG) || defined(_DEBUG)
			std::stringstream sout;
			UTILITY::ConcatString(sout, args...);
			std::string out = sout.str();
			std::cout << (out);
//#endif
		};


		// IDE�̕��Ƀ��O���o��
		template<typename... Args>
		static
		void Log(const Args&... args)
		{
#if defined(DEBUG) || defined(_DEBUG)
			std::stringstream sout;
			UTILITY::ConcatString(sout, args...);
			std::string out = sout.str();
			OutputDebugString(out.c_str());
#endif
		};

	private:

	};



}