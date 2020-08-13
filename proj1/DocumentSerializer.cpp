#include "stdafx.h"
#include "DocumentSerializer.h"
#include<string.h>


CDocumentSerializer::CDocumentSerializer()
{
}


CDocumentSerializer::~CDocumentSerializer()
{
}

void CDocumentSerializer::Serialize(CBson *Document, PERSON_STR &person) {

	char Key[64];
	bson_iter_t iter;
	const bson_value_t *FieldValue = nullptr;
	
	if (bson_iter_init(&iter, Document->GetDocument())) {

		while (bson_iter_next(&iter)) {

			strcpy(Key, bson_iter_key(&iter));
			FieldValue = bson_iter_value(&iter);

			if ((strcmp(Key, "name") == 0) &&  BSON_ITER_HOLDS_UTF8(&iter) ) {
				strcpy(person.Name, FieldValue->value.v_utf8.str);
				continue;
			}
			if ((strcmp(Key, "age") == 0) && BSON_ITER_HOLDS_INT32(&iter)) {
				FieldValue = bson_iter_value(&iter);
				person.Age = FieldValue->value.v_int32;
				continue;
			}
			if ((strcmp(Key, "family") == 0) && BSON_ITER_HOLDS_ARRAY(&iter)) {
				SerializeNestedArray(&iter,person);
			}
		}
	}
}

	void CDocumentSerializer::SerializeNestedArray(bson_iter_t* iter, PERSON_STR &person) {

		char Key[64];
		const bson_value_t *FieldValue = nullptr;
		bson_iter_t  child, child2;
		uint64_t FamilyMemberId = 0;
		//Reset number of family members
		person.NumberOfRelatives = 0;
		bson_iter_recurse(iter, &child);
		
		//Loop over family members
		while (bson_iter_next(&child)) {
			
			//increment number of family members
			person.NumberOfRelatives++;
			
			//Parsing data for each member
			bson_iter_recurse(&child,&child2);
			while (bson_iter_next(&child2)) {
				strcpy(Key, bson_iter_key(&child2));
				FieldValue = bson_iter_value(&child2);

				if ((strcmp(Key, "name") == 0) && BSON_ITER_HOLDS_UTF8(&child2)) {
					strcpy(person.FamilyMembers[FamilyMemberId].Name, FieldValue->value.v_utf8.str);
					continue;
				}
				if ((strcmp(Key, "relation") == 0) && BSON_ITER_HOLDS_UTF8(&child2)) {
					strcpy(person.FamilyMembers[FamilyMemberId].Relation, FieldValue->value.v_utf8.str);
				}
				FamilyMemberId++;
			}
		}

	}