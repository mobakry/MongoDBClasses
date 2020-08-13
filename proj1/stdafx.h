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
#define MaxStringLength				128
#define MaxEntityInfo				64
#define MaxFrameFacts				64
#define MaxObjects					64
#define MaxFramesNo					64


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
}PERSON_STR;




typedef struct
{
	char EntityText[MaxStringLength];

	
}ENTITYINFO_STR;

typedef struct
{

}FRAMEFACTS_STR;

typedef struct
{

}OBJECTS_STR;

typedef struct
{

}FRAME_STR;

typedef struct
{
	char EntityType[MaxStringLength];
	uint64_t ParentId;
	ENTITYINFO_STR EntityInfo[MaxEntityInfo];
	bool AmbClass;
	bool ErrorInStem;
	bool ParaphraseEntities;
	FRAME_STR Frame[MaxFramesNo];
	FRAMEFACTS_STR FrameFacts[MaxFrameFacts];
	bool ClassFacts;
	bool Individuals;
	OBJECTS_STR Objects[MaxObjects];
	bool List;
	bool Inquiries;
	uint32_t ObjectType;
	uint32_t TemplateId;

}ENTITY_STR;