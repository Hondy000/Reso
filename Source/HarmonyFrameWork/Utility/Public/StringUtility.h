#pragma once
#include <string>
namespace UTILITY
{


	/**********************************************************************************************//**
																									* @fn	inline void ExtractionStringBlockFromSentence ( std::string& outsSring, std::string& sentence, int index, std::string& startKeyword, std::string& endKeyword, int* progressIndex )
																									*
																									* @brief	文字列からブロック指定した文字を元に文字列を抽出.
																									*
																									* @author	Kazuyuki Honda
																									* @date	2015/11/01
																									*
																									* @param [in,out]	outsSring	 	The outs sring.
																									* @param [in,out]	sentence	 	The sentence.
																									* @param	index				 	Zero-based index of the.
																									* @param [in,out]	startKeyword 	ブロック先頭文字.
																									* @param [in,out]	endKeyword   	ブロック終端文字.
																									* @param [in,out]	progressIndex	If non-null, zero-based index of the progress.
																									**************************************************************************************************/

	inline void ExtractionStringBlockFromSentence
		(
			std::string& outsSring,
			int& progressIndex,
			std::string& sentence,
			std::string& startKeyword,
			std::string& endKeyword,
			int index
			)
	{
		size_t firstStartPoint = sentence.find(startKeyword, index);
		size_t endPoint = sentence.find(endKeyword, firstStartPoint + startKeyword.length());
		size_t conpStartPoint = sentence.find(startKeyword, firstStartPoint + startKeyword.length());
		size_t lastEndPoint = endPoint;
		// endが見つかる前にまたstartが見つかった場合
		if (startKeyword != endKeyword)
		{
			while (conpStartPoint < lastEndPoint &&  -1 != conpStartPoint)
			{
				endPoint = lastEndPoint;
				conpStartPoint = sentence.find(startKeyword, conpStartPoint + startKeyword.length());
				lastEndPoint = sentence.find(endKeyword, endPoint + endKeyword.length());
			}
		}
		if (-1 != firstStartPoint&& -1 != endPoint)
		{
			firstStartPoint += startKeyword.length();

			outsSring = sentence.substr(firstStartPoint, endPoint - firstStartPoint);
		}
		if (progressIndex)
		{
			progressIndex += lastEndPoint - index;
		}
	}

	// 数字を見つけるまで探索してstd::stringに格納する関数
	inline bool CollectionNumbersFromString(
		std::string* pOutString,
		int* pOutProgterss,
		const std::string* pInString,
		const int pInIndex)
	{
		int i = 0;
		for (i = 0; i + pInIndex < pInString->size(); i++)
		{
			// 数字を見つけた
			if (isdigit(pInString->at(i + pInIndex)))
			{
				*pOutString += pInString->at(i + pInIndex);
			}
			else
			{
				break;
			}
			pInIndex;
		}
		*pOutProgterss = i;
		if (pOutString->size() == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	// +-があるか判定
	inline bool IsPlusAndMinus
		(
			const std::string& str,
			const int& index)
	{
		if (index < 0 && str.size() < index)
		{
			return false;
		}
		if (str.at(index) == '+' || str.at(index) == '-')
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// 指数判定
	inline bool IsExponentCharactor
		(
			const std::string& str,
			const int& index)
	{
		if (index < 0 && str.size() < index)
		{
			return false;
		}
		if (str.at(index) == 'e' || str.at(index) == 'E')
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// '.'判定
	inline bool IsDotCharactor
		(
			const std::string& str,
			const int& index)
	{
		if (index < 0 && str.size() < index)
		{
			return false;
		}
		if (str.at(index) == '.')
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/**********************************************************************************************//**
																									* @fn	inline bool ExtractionNumbersFromString ( std::string* pOutString, int* pOutEnd, const std::string* pInString, const int* pInIndex)
																									*
																									* @brief	文字列から数字(文字列)を取り出す.
																									*
																									* @author	Kazuyuki Honda
																									* @date	2015/11/01
																									*
																									* @param [in,out]	pOutString	抜き出した文字列.
																									* @param [in,out]	pOutEnd   	終了インデックス.
																									* @param	pInString		  	数字を抜き出したい文字列.
																									* @param	pInIndex		  	数字を探し始めるオフセットインデックス.
																									*
																									* @return	true if it succeeds, false if it fails.
																									*
																									**************************************************************************************************/

	inline bool ExtractionNumbersFromString
		(
			std::string* pOutString,
			int* pOutEnd,
			const std::string* pInString,
			const int* pInIndex)
	{
#ifdef DEBUG
		if (!pOutString || !pInString || !pInIndex)
		{
			return false;
		}
#endif
		pOutString->clear();

		// 文字列内探索

		int i = 0;
		for (i = 0; i + *pInIndex < pInString->size(); i++)
		{
			// 数字を見つけた
			if (isdigit(pInString->at(i + *pInIndex)))
			{
				int n;
				if (0 < (i + *pInIndex) && IsPlusAndMinus(*pInString, int(i - 1 + *pInIndex)))
				{
					*pOutString += pInString->at(i - 1 + *pInIndex);
				}

				CollectionNumbersFromString(pOutString, &n, pInString, *pInIndex + i);
				i += n;
				break;
			}
		}
		// 文字列終了
		if (i + *pInIndex >= pInString->size())
		{
			return false;
		}

		// size以下で数字が連続している
		// 少数があるか
		if (IsDotCharactor(*pInString, int(i + *pInIndex)))
		{
			*pOutString += pInString->at(i + *pInIndex);
			i++;
			// 数字を見つけた
			if (isdigit(pInString->at(i + *pInIndex)))
			{
				int n;
				// ひとつ前の文字が+-か調べる
				if (0 < (i + *pInIndex) && IsPlusAndMinus(*pInString, int(i - 1 + *pInIndex)))
				{
					*pOutString += pInString->at(i - 1 + *pInIndex);
				}

				CollectionNumbersFromString(pOutString, &n, pInString, *pInIndex + i);
				i += n;
			}
		}

		// 指数表記かも
		if (0 < (i + *pInIndex) && IsExponentCharactor(*pInString, int(i + *pInIndex)))
		{
			*pOutString += pInString->at(i + *pInIndex);
			i++;
			// +,-
			if (0 < (i + *pInIndex) && IsPlusAndMinus(*pInString, int(i + *pInIndex)))
			{
				*pOutString += pInString->at(i + *pInIndex);
				i++;
			}

			// 数字を見つけた
			if (isdigit(pInString->at(i + *pInIndex)))
			{
				int n;

				CollectionNumbersFromString(pOutString, &n, pInString, *pInIndex + i);
				i += n;
			}
		}

		*pOutEnd = *pInIndex + i;

		return true;
	}

	/**********************************************************************************************//**
																									* @fn	inline std::string AnalysisFormat(std::string filePath)
																									*
																									* @brief	ファイルパスからファイル名を探す.
																									*
																									* @author	Kazuyuki Honda
																									* @date	2015/08/02
																									*
																									* @param	filePath	Full pathname of the file.
																									*
																									* @return	A std::string.
																									**************************************************************************************************/

	inline std::string AnalysisFileName(std::string filePath)
	{
		std::string fileName;

		// ひとまずスラッシュのみ対応
		size_t dotPosition = filePath.find_last_of("/");
		return fileName;
	}

	/**********************************************************************************************//**
																									* @fn	inline std::string AnalysisFormat(std::string filePath)
																									*
																									* @brief	ファイルパスから拡張子を探す.
																									*
																									* @author	Kazuyuki Honda
																									* @date	2015/08/02
																									*
																									* @param	filePath	Full pathname of the file.
																									*
																									* @return	A std::string.
																									**************************************************************************************************/

	inline std::string AnalysisFormat(std::string filePath)
	{
		size_t dotPosition = filePath.find_last_of(".");
		std::string format(filePath, dotPosition + 1, filePath.size() - (dotPosition));
		return format;
	}

	/**********************************************************************************************//**
																									* @fn	inline bool StringToInteger( int* pOut, std::string pIn )
																									*
																									* @brief	文字列から整数変換.
																									*
																									* @author	Kazuyuki Honda
																									* @date	2015/08/02
																									*
																									* @param [in,out]	pOut	If non-null, the out. 変換された数値
																									* @param	pIn				The in. 変換する文字列
																									*
																									* @return	true if it succeeds, false if it fails. 変換の成功可否
																									**************************************************************************************************/
	inline bool StringToInteger
		(
			int* pOut,	// 変換された数値
			std::string pIn	// 変換する文字列
			)
	{
		try
		{
			*pOut = std::stoi(pIn);
		}
		catch (std::invalid_argument e)
		{
#ifdef DEBUG
			//cout << e.what() << endl;
#endif
			return false;
		}
		catch (std::out_of_range e)
		{
#ifdef DEBUG
			//	cout << e.what() << endl;
#endif
			return false;
		}
		return true;
	}

	inline bool StringToFloat
		(
			float* pOut,	// 変換された数値
			std::string pIn	// 変換する文字列
			)
	{
		try
		{
			*pOut = std::stof(pIn);
		}
		catch (std::invalid_argument e)
		{
#ifdef DEBUG
			//cout << e.what() << endl;
#endif
			return false;
		}
		catch (std::out_of_range e)
		{
#ifdef DEBUG
			//	cout << e.what() << endl;
#endif
			return false;
		}
		return true;
	}


	inline std::string Narrow(const std::wstring& src)
	{
		char * mbs = new char[src.length() * MB_CUR_MAX + 1];
		size_t* size = nullptr;
		wcstombs_s(size, mbs, src.length() * MB_CUR_MAX + 1, src.c_str(), src.length() * MB_CUR_MAX + 1);
		std::string dest(mbs);
		operator delete[](mbs);
		return dest;
	}

	inline std::wstring Widen(const std::string& src)
	{
		wchar_t * wcs = new wchar_t[src.length() * MB_CUR_MAX + 1];
		size_t* size = nullptr;
		mbstowcs_s(size, wcs, src.length() * MB_CUR_MAX + 1, src.c_str(), src.length() * MB_CUR_MAX + 1);
		std::wstring dest(wcs);
		operator delete[](wcs);
		return dest;
	}
};