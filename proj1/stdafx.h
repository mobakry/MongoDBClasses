// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define MaxNumberOfTrials	3


struct InsertManyReturnStruct
{
	bool Result;
	int InsertCount;
};

struct UpdateReturnStruct
{
	bool Result;
	int matchedCount;
	int modifiedCount;
};
struct DeleteReturnStruct
{
	bool Result;
	int deletedCount;
};



// TODO: reference additional headers your program requires here
