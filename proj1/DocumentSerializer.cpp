#include"stdafx.h"
#include "DocumentSerializer.h"



void  CDocumentSerializer::Serialize(const CBsonDocument &Document, PERSON_STR &PersonInfo) 
{
	bson_iter_t Iterator;
	bson_iter_t FamilyMembersIterator;
	const bson_value_t* Value;
 	char Key[MAX_STRING_LENGTH];

	if (!bson_iter_init(&Iterator, Document.GetDocumentStr())) return;


	PersonInfo.FamilyMembersCount = 0;

	while (bson_iter_next(&Iterator)) {

		strcpy(Key, bson_iter_key(&Iterator));

 		if (strcmp(Key, "name") == 0 && BSON_ITER_HOLDS_UTF8(&Iterator)) {

			Value = bson_iter_value(&Iterator);
			if (Value->value_type == BSON_TYPE_UTF8) {
				strcpy_s(PersonInfo.Name, Value->value.v_utf8.str);
 			}

		}

 		else if (strcmp(Key, "age") == 0 && (BSON_ITER_HOLDS_INT32(&Iterator) || BSON_ITER_HOLDS_DOUBLE(&Iterator))) {

			Value = bson_iter_value(&Iterator);
			if (Value->value_type == BSON_TYPE_INT32) {
				PersonInfo.Age = Value->value.v_int32;
 			}
		}

		else if (strcmp(Key, "family") == 0 && BSON_ITER_HOLDS_ARRAY(&Iterator)) {

			if (!bson_iter_recurse(&Iterator, &FamilyMembersIterator)) continue;
			SerializeFamilyMemberArray(&FamilyMembersIterator, PersonInfo);
			
		}
	}
}


void CDocumentSerializer::SerializeFamilyMemberArray(bson_iter_t* Iterator, PERSON_STR& PersonInfo)
{
	bson_iter_t ArrayIterator;

	while (bson_iter_next(Iterator)) {

		if (BSON_ITER_HOLDS_DOCUMENT(Iterator) && bson_iter_recurse(Iterator, &ArrayIterator)) {
			
			if (PersonInfo.FamilyMembersCount >= MAX_MEMBERS)  break;
			
			SerializeFamilyMemberDocument(&ArrayIterator, PersonInfo);
			PersonInfo.FamilyMembersCount++;

		}

	}
}

void CDocumentSerializer::SerializeFamilyMemberDocument(bson_iter_t* Iterator, PERSON_STR& PersonInfo) 
{
	const bson_value_t* Value;
	char Key[MAX_STRING_LENGTH];

	while (bson_iter_next(Iterator)) {

		strcpy_s(Key, bson_iter_key(Iterator));

		if (strcmp(Key, "name") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {

			Value = bson_iter_value(Iterator);
			if (Value->value_type == BSON_TYPE_UTF8) {
				strcpy(PersonInfo.FamilyMembers[PersonInfo.FamilyMembersCount].Name, Value->value.v_utf8.str);
			}

		}

		else if (strcmp(Key, "relation") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {

			Value = bson_iter_value(Iterator);
			if (Value->value_type == BSON_TYPE_UTF8) {
				strcpy(PersonInfo.FamilyMembers[PersonInfo.FamilyMembersCount].Relation, Value->value.v_utf8.str);
			}

		}
	}
}
