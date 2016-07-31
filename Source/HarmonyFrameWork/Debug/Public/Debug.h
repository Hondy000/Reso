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

		// コンソール画面表示
		void StartConsole();
		// コンソール終わり
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


		// コンソールにログを出す
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


		// IDEの方にログを出す
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