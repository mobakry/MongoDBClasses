// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define MaxNumberOfTrials			3
#define MaxNameSize					128
#define MaxRelationSize				32
#define MaxNumberOfFamilyMembers	50

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

struct Family {
	char Name[MaxNameSize];
	char Relation[MaxRelationSize];
};

struct Person {
	char Name[MaxNameSize];
	int Age;
	Family FamilyMembers[MaxNumberOfFamilyMembers];
	int NumberOfRelatives = 0;
};

// TODO: reference additional headers your program requires here
