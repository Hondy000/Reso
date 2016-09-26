/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\GraphicsObject\Basic\CBaseShader.cpp
 *
 * @brief	Implements the base shader class.
 **************************************************************************************************/

#include <fstream>
#include "../Public/BaseGraphicsShader.h"

/**********************************************************************************************//**
  * @fn	CBaseShader::CBaseShader()
  *
  * @brief	Default constructor.
  *
  * @author	Kazuyuki Honda
  * @date	2015/08/02
  **************************************************************************************************/

BaseGraphicsShader::BaseGraphicsShader()
{
}

/**********************************************************************************************//**
 * @fn	CBaseShader::~CBaseShader()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

BaseGraphicsShader::~BaseGraphicsShader()
{
}

/**********************************************************************************************//**
 * @fn	void CBaseShader::OutputShaderErrorMessage ( Microsoft::WRL::ComPtr<ID3D10Blob> errorMessage, TCHAR* shaderFilename)
 *
 * @brief	Output shader error message.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	errorMessage		  	Message describing the error.
 * @param [in,out]	shaderFilename	If non-null, filename of the shader file.
 **************************************************************************************************/

void BaseGraphicsShader::OutputShaderErrorMessage
(
	Microsoft::WRL::ComPtr<ID3D10Blob> errorMessage,
	TCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	std::ofstream fout;

	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	//errorMessage->Release();
	//errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.

	return;
}
