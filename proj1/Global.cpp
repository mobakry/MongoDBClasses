#include"stdafx.h"
#include <iostream>
#include "mongoc.h"
#include "Global.h"

//_________________________String Functions______________________//
void CopyString(char *_Dest, char *_Source, int MaxDestSize)
{
	if (_Source == NULL || _Dest==NULL)
		return;

	int Length = strlen(_Source);

	if (Length < MaxDestSize)
		strcpy(_Dest, _Source);
	else
	{
		strncpy(_Dest, _Source, MaxDestSize - 1);
		_Dest[MaxDestSize - 1] = 0;
	}
}

void ConcatString(char *_Dest, char *_Source, int MaxDestSize)
{
	if (_Source == NULL || _Dest == NULL)
		return;

	int SrcLength = strlen(_Source);
	int DestLength = strlen(_Dest);

	if ((DestLength + SrcLength) < MaxDestSize)
		strcat(_Dest, _Source);
	else
	{
		strncat(_Dest, _Source, (MaxDestSize - DestLength - 1));
		_Dest[MaxDestSize - 1] = 0;
	}

}


void ConvertUtf8ToAnsi(char *inputBuffer, char* OutputBuffer)
{
	int nLen = 0;
	char *TempBuffer = NULL;

	// alloc mem
	nLen = strlen(inputBuffer) + 1;

	TempBuffer = new char[2 * nLen];

	//convert to bstr
	MultiByteToWideChar(CP_UTF8, 0, inputBuffer, -1, (LPWSTR)TempBuffer, 2 * nLen);

	//convert to string
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)TempBuffer, -1, OutputBuffer, nLen, NULL, NULL);

	delete TempBuffer;
}

void ConvertAnsiToUtf8(char *inputBuffer, char* OutputBuffer)
{
	int nLen = 0;
	char *TempBuffer = NULL;

	// alloc mem
	nLen = strlen(inputBuffer) + 1;

	TempBuffer = new char[2 * nLen];

	//convert to bstr
	MultiByteToWideChar(CP_ACP, 0, inputBuffer, -1, (LPWSTR)TempBuffer, nLen);

	//convert to string
	WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)TempBuffer, -1, OutputBuffer, 2 * nLen, NULL, NULL);

	delete TempBuffer;
}






BOOL CopyANSIText(char *&SystemResponse, char *Value)
{
	int Length;

	Length = strlen(Value);

	if (Length == 0)
	{
		SystemResponse = NULL;
		return FALSE;
	}

	SystemResponse = new char[Length + 1];

	strcpy(SystemResponse, Value);

	return TRUE;
}

BOOL CopyUTFText(char *&SystemResponse, char *Value)
{
	int Length;

	ConvertUtf8ToAnsi(Value, Value);

	Length = strlen(Value);

	if (Length == 0)
	{
		SystemResponse = NULL;
		return FALSE;
	}

	SystemResponse = new char[Length + 1];

	strcpy(SystemResponse, Value);

	return TRUE;
}