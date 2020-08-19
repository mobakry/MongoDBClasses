#pragma once
#include "BsonSerializer.h"

#define MAX_STRING_LENGTH 128
#define MAX_MEMBERS 10

typedef struct {
	char Name[MAX_STRING_LENGTH];
	char Relation[MAX_STRING_LENGTH];
}FAMILY_MEMBER_STR;


typedef struct {
	char Name[MAX_STRING_LENGTH];
	int Age;
	FAMILY_MEMBER_STR FamilyMembers[MAX_MEMBERS];
	int FamilyMembersCount;

}PERSON_STR;



class CDocumentSerializer :	public CBsonSerializer<PERSON_STR> 
{
public:

	void Serialize(const CBsonDocument &Document, PERSON_STR& PersonInfo);

private:

	void SerializeFamilyMemberDocument(bson_iter_t* Iterator, PERSON_STR& PersonInfo);
	void SerializeFamilyMemberArray(bson_iter_t* Iterator, PERSON_STR& PersonInfo);

};

