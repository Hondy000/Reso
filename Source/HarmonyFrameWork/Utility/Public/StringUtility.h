#pragma once
#include <string>
namespace UTILITY
{


	/**********************************************************************************************//**
																									* @fn	inline void ExtractionStringBlockFromSentence ( std::string& outsSring, std::string& sentence, int index, std::string& startKeyword, std::string& endKeyword, int* progressIndex )
																									*
																									* @brief	�����񂩂�u���b�N�w�肵�����������ɕ�����𒊏o.
																									*
																									* @author	Kazuyuki Honda
																									* @date	2015/11/01
																									*
																									* @param [in,out]	outsSring	 	The outs sring.
																									* @param [in,out]	sentence	 	The sentence.
																									* @param	index				 	Zero-based index of the.
																									* @param [in,out]	startKeyword 	�u���b�N�擪����.
																									* @param [in,out]	endKeyword   	�u���b�N�I�[����.
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
		// end��������O�ɂ܂�start�����������ꍇ
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

	// ������������܂ŒT������std::string�Ɋi�[����֐�
	inline bool CollectionNumbersFromString(
		std::string* pOutString,
		int* pOutProgterss,
		const std::string* pInString,
		const int pInIndex)
	{
		int i = 0;
		for (i = 0; i + pInIndex < pInString->size(); i++)
		{
			// ������������
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

	// +-�����邩����
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

	// �w������
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

	// '.'����
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
																									* @brief	�����񂩂琔��(������)�����o��.
																									*
																									* @author	Kazuyuki Honda
																									* @date	2015/11/01
																									*
																									* @param [in,out]	pOutString	�����o����������.
																									* @param [in,out]	pOutEnd   	�I���C���f�b�N�X.
																									* @param	pInString		  	�����𔲂��o������������.
																									* @param	pInIndex		  	������T���n�߂�I�t�Z�b�g�C���f�b�N�X.
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

		// ��������T��

		int i = 0;
		for (i = 0; i + *pInIndex < pInString->size(); i++)
		{
			// ������������
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
		// ������I��
		if (i + *pInIndex >= pInString->size())
		{
			return false;
		}

		// size�ȉ��Ő������A�����Ă���
		// ���������邩
		if (IsDotCharactor(*pInString, int(i + *pInIndex)))
		{
			*pOutString += pInString->at(i + *pInIndex);
			i++;
			// ������������
			if (isdigit(pInString->at(i + *pInIndex)))
			{
				int n;
				// �ЂƂO�̕�����+-�����ׂ�
				if (0 < (i + *pInIndex) && IsPlusAndMinus(*pInString, int(i - 1 + *pInIndex)))
				{
					*pOutString += pInString->at(i - 1 + *pInIndex);
				}

				CollectionNumbersFromString(pOutString, &n, pInString, *pInIndex + i);
				i += n;
			}
		}

		// �w���\�L����
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

			// ������������
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
																									* @brief	�t�@�C���p�X����t�@�C������T��.
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

		// �ЂƂ܂��X���b�V���̂ݑΉ�
		size_t dotPosition = filePath.find_last_of("/");
		return fileName;
	}

	/**********************************************************************************************//**
																									* @fn	inline std::string AnalysisFormat(std::string filePath)
																									*
																									* @brief	�t�@�C���p�X����g���q��T��.
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
																									* @brief	�����񂩂琮���ϊ�.
																									*
																									* @author	Kazuyuki Honda
																									* @date	2015/08/02
																									*
																									* @param [in,out]	pOut	If non-null, the out. �ϊ����ꂽ���l
																									* @param	pIn				The in. �ϊ����镶����
																									*
																									* @return	true if it succeeds, false if it fails. �ϊ��̐�����
																									**************************************************************************************************/
	inline bool StringToInteger
		(
			int* pOut,	// �ϊ����ꂽ���l
			std::string pIn	// �ϊ����镶����
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
			float* pOut,	// �ϊ����ꂽ���l
			std::string pIn	// �ϊ����镶����
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