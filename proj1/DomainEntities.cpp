#include"stdafx.h"
#include "DomainEntities.h"



bool CDomainEntities::Serialize(const CBsonDocument &Document, DOMAIN_ENTITY_STR **Data, int &ArraySize)
{
	char Key[64];
	char TempBuffer[MAX_ENTITY_TEXT_LENGTH];
	
	bson_iter_t EntityIter, ArrayIter, DocumentIter, CountIter;

	const bson_value_t *FieldValue = nullptr;

	int EntityIndex = 0;

	if (! bson_iter_init(&EntityIter, Document.GetDocumentStr() ) )
		return FALSE;

	if (!bson_iter_find(&EntityIter, "entities"))

		return FALSE;

	bson_iter_recurse(&EntityIter, &ArrayIter);
	bson_iter_recurse(&EntityIter, &CountIter);

	ArraySize = GetArrayCount(&CountIter);

	*Data = new DOMAIN_ENTITY_STR[ArraySize]();

	while (bson_iter_next(&ArrayIter))
	{
		//Parsing data for each element
		bson_iter_recurse(&ArrayIter, &DocumentIter);
		while (bson_iter_next(&DocumentIter)) {

			strcpy(Key, bson_iter_key(&DocumentIter));
			FieldValue = bson_iter_value(&DocumentIter);

			if ((strcmp(Key, "original_entity") == 0) && BSON_ITER_HOLDS_UTF8(&DocumentIter)) {

				CopyString(TempBuffer, FieldValue->value.v_utf8.str, MAX_ENTITY_TEXT_LENGTH);
				ConvertUtf8ToAnsi(TempBuffer, TempBuffer);
				CopyString((*Data)[EntityIndex].OriginalEntity, TempBuffer, MAX_ENTITY_TEXT_LENGTH);
				continue;
			}
			if ((strcmp(Key, "stemmed_entity") == 0) && BSON_ITER_HOLDS_UTF8(&DocumentIter)) {

				CopyString(TempBuffer, FieldValue->value.v_utf8.str, MAX_ENTITY_TEXT_LENGTH);
				ConvertUtf8ToAnsi(TempBuffer, TempBuffer);
				CopyString((*Data)[EntityIndex].StemmedEntity, TempBuffer, MAX_ENTITY_TEXT_LENGTH);
				continue;
			}
			if ((strcmp(Key, "language") == 0) && BSON_ITER_HOLDS_UTF8(&DocumentIter)) {

				CopyString(TempBuffer, FieldValue->value.v_utf8.str, MAX_ENTITY_TEXT_LENGTH);
				ConvertUtf8ToAnsi(TempBuffer, TempBuffer);
				CopyString((*Data)[EntityIndex].Language, TempBuffer, MAX_ENTITY_TEXT_LENGTH);
				continue;
			}
			if ((strcmp(Key, "type_id") == 0) && BSON_ITER_HOLDS_INT32(&DocumentIter)) {
				(*Data)[EntityIndex].Type_id = FieldValue->value.v_int32;
				continue;
			}
			if ((strcmp(Key, "entity_id") == 0) && BSON_ITER_HOLDS_INT32(&DocumentIter)) {
				(*Data)[EntityIndex].Entity_id = FieldValue->value.v_int32;
				continue;
			}
			if ((strcmp(Key, "parent_id") == 0) && BSON_ITER_HOLDS_INT32(&DocumentIter)) {
				(*Data)[EntityIndex].Parent_id = FieldValue->value.v_int32;
				continue;
			}
			if ((strcmp(Key, "classId") == 0) && BSON_ITER_HOLDS_INT32(&DocumentIter)) {
				(*Data)[EntityIndex].ClassId = FieldValue->value.v_int32;
				continue;
			}
			if ((strcmp(Key, "PropertyId") == 0) && BSON_ITER_HOLDS_INT32(&DocumentIter)) {
				(*Data)[EntityIndex].PropertyId = FieldValue->value.v_int32;
				continue;
			}
			if ((strcmp(Key, "ambClass") == 0) && BSON_ITER_HOLDS_BOOL(&DocumentIter)) {
				(*Data)[EntityIndex].AmbClass = FieldValue->value.v_int32;
				continue;
			}
			if ((strcmp(Key, "female") == 0) && BSON_ITER_HOLDS_BOOL(&DocumentIter)) {
				(*Data)[EntityIndex].Female = FieldValue->value.v_int32;
				continue;
			}
			if ((strcmp(Key, "individuals") == 0) && BSON_ITER_HOLDS_ARRAY(&DocumentIter)) {
				SerializeIndividualsArray(&DocumentIter, Data, EntityIndex);
			}

		}
		EntityIndex++;

	}

	return TRUE;
	
}

void CDomainEntities::SerializeIndividualsArray(bson_iter_t *EntityIter, DOMAIN_ENTITY_STR **Data, int EntityIndex)
{
	char Key[64], TempBuffer[MAX_ENTITY_TEXT_LENGTH];
	const bson_value_t *FieldValue = nullptr;
	bson_iter_t  ArrayIter, ElementIter, CountIter;
	int IndividualIndex, ArraySize = 0;

	bson_iter_recurse(EntityIter, &ArrayIter);
	bson_iter_recurse(EntityIter, &CountIter);
	ArraySize = GetArrayCount(&CountIter);
	(*Data)[EntityIndex].Individuals = new int[ArraySize]();

	while (bson_iter_next(&ArrayIter))
	{
		IndividualIndex = (*Data)[EntityIndex].NOfIndividuals;

		FieldValue = bson_iter_value(&ArrayIter);
		
		(*Data)[EntityIndex].Individuals[IndividualIndex] = FieldValue->value.v_int32;
			
		(*Data)[EntityIndex].NOfIndividuals++;
	}
}