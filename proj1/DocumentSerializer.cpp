#include "stdafx.h"
#include "DocumentSerializer.h"
#include<string.h>


CDocumentSerializer::CDocumentSerializer()
{
}


CDocumentSerializer::~CDocumentSerializer()
{
}

void CDocumentSerializer::Serialize(CBson* Document) {

	char Key[64];
	bson_iter_t iter, child;
	const bson_value_t *NameFieldValue, *AgeFieldValue, *RelationFieldValue;

	if (bson_iter_init(&iter, Document->GetDocument())) {
		while (bson_iter_next(&iter)) {

			strcpy(Key, bson_iter_key(&iter));

			if (strcmpi(Key, "name")) {
				NameFieldValue = bson_iter_value(&iter);
				strcpy(this->m_Person.Name, NameFieldValue->value.v_utf8.str);
			}
			else if (strcmpi(Key, "age")) {
				AgeFieldValue = bson_iter_value(&iter);
				this->m_Person.Age = AgeFieldValue->value.v_int32;
			}
			else if (strcmpi(Key, "family")) {
				SerializeNestedArray(&iter);

			}
		}
	}
}

	void CDocumentSerializer::SerializeNestedArray(bson_iter_t* iter) {
		char Key[64];
		bson_iter_t *child;
		const bson_value_t *NameFieldValue, *RelationFieldValue;

		bson_iter_recurse(iter, child);

		while (bson_iter_next(child)) {
			strcpy(Key, bson_iter_key(iter));
			if (strcmpi(Key, "name")) {
				strcpy(this->m_Person.FamilyMembers->Name, NameFieldValue->value.v_utf8.str);
			}
			else if (strcmpi(Key, "relation")) {
				RelationFieldValue = bson_iter_value(iter);
				strcpy(this->m_Person.FamilyMembers->Relation, NameFieldValue->value.v_utf8.str);
			}
		}

	}