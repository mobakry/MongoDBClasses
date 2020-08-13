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
typedef struct
{
	bool Result;
	int deletedCount;
}DeleteReturnStruct;

typedef struct {
	char Name[MaxNameSize];
	char Relation[MaxRelationSize];
}Family;


typedef struct
{
	char Name[MaxNameSize];
	int Age = 10;
	Family FamilyMembers[MaxNumberOfFamilyMembers];
	int NumberOfRelatives = 0;
}Person;

