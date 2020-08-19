#include"stdafx.h"
#include "EntitySerializer.h"

void CEntitySerializer::SerializeFrameDocument(bson_iter_t *Iterator, ENTITY_STR &Entity)
{
	bson_iter_t SubIterator;
	char Key[MAX_STRING_LENGTH];
	int Count = 0;
	
	while (bson_iter_next(Iterator)) {

		strcpy(Key, bson_iter_key(Iterator));

		if (strcmp(Key, "senseId") == 0 && BSON_ITER_HOLDS_INT32(Iterator)) {

			Entity.Frame.SenseId = bson_iter_int32(Iterator);
		}

		else if (strcmp(Key, "entityId") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {
			
			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.Frame.EntityId, Key, MAX_STRING_LENGTH);
		}

		else if (strcmp(Key, "parentId") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {

			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.Frame.ParentId, Key, MAX_STRING_LENGTH);
		}

		else if (strcmp(Key, "type") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {
			
			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.Frame.Type, Key, MAX_STRING_LENGTH);
		}

		else if (strcmp(Key, "sbj") == 0 && BSON_ITER_HOLDS_ARRAY(Iterator)) {

			if (!bson_iter_recurse(Iterator, &SubIterator)) continue;

			SerializeSbjArray(&SubIterator, Entity, Count);
		}

		else if (strcmp(Key, "obj") == 0 && BSON_ITER_HOLDS_ARRAY(Iterator)) {

			if (!bson_iter_recurse(Iterator, &SubIterator)) continue;

			SerializeObjArray(&SubIterator, Entity, Count);
		}

		else if (strcmp(Key, "cmp") == 0 && BSON_ITER_HOLDS_ARRAY(Iterator)) {

			if (!bson_iter_recurse(Iterator, &SubIterator)) continue;

			SerializeCmpArray(&SubIterator, Entity, Count);
		}
	}
	
}



void CEntitySerializer::SerializeSbjArray(bson_iter_t *Iterator, ENTITY_STR &Entity, int Count)
{
	bson_iter_t ArrayIterator;

	Entity.Frame.Sbj = new ARG_STR[Count];

	while (bson_iter_next(Iterator)) {

		if (BSON_ITER_HOLDS_DOCUMENT(Iterator) && bson_iter_recurse(Iterator, &ArrayIterator)) {

			if (Entity.Frame.NOfSbj >= Count)  break;

			SerializeSbjDocument(&ArrayIterator, Entity);
			Entity.Frame.NOfSbj++;

		}

	}


}

void CEntitySerializer::SerializeObjArray(bson_iter_t *Iterator, ENTITY_STR &Entity, int Count)
{
	bson_iter_t ArrayIterator;
	Entity.Frame.Obj = new ARG_STR[Count];

	while (bson_iter_next(Iterator)) {

		if (BSON_ITER_HOLDS_DOCUMENT(Iterator) && bson_iter_recurse(Iterator, &ArrayIterator)) {

			if (Entity.Frame.NOfObj >= Count)  break;

			SerializeObjDocument(&ArrayIterator, Entity);
			Entity.Frame.NOfObj++;
		}
	}

}

void CEntitySerializer::SerializeCmpArray(bson_iter_t *Iterator, ENTITY_STR &Entity, int Count)
{
	bson_iter_t ArrayIterator;
	Entity.Frame.Cmp = new ARG_STR[Count];

	while (bson_iter_next(Iterator)) {

		if (BSON_ITER_HOLDS_DOCUMENT(Iterator) && bson_iter_recurse(Iterator, &ArrayIterator)) {

			if (Entity.Frame.NOfCmp >= Count)  break;

			SerializeCmpDocument(&ArrayIterator, Entity);
			Entity.Frame.NOfCmp++;
		}
	}

}

void CEntitySerializer::SerializeSbjDocument(bson_iter_t *Iterator, ENTITY_STR &Entity) 
{
 	char Key[MAX_STRING_LENGTH];

	while (bson_iter_next(Iterator)) {

		strcpy(Key, bson_iter_key(Iterator));

		if (strcmp(Key, "I") == 0 && BSON_ITER_HOLDS_INT32(Iterator)) {

			Entity.Frame.Sbj[Entity.Frame.NOfSbj].I = bson_iter_int32(Iterator);
		}

		else if (strcmp(Key, "S") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {

			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.Frame.Sbj[Entity.Frame.NOfSbj].S, Key, MAX_STRING_LENGTH);
		}

		else if (strcmp(Key, "T") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {
			
			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.Frame.Sbj[Entity.Frame.NOfSbj].T, Key, MAX_STRING_LENGTH);
		}

	}
}


void CEntitySerializer::SerializeObjDocument(bson_iter_t *Iterator, ENTITY_STR &Entity)
{
 	char Key[MAX_STRING_LENGTH];

	while (bson_iter_next(Iterator)) {

		strcpy(Key, bson_iter_key(Iterator));

		if (strcmp(Key, "I") == 0 && BSON_ITER_HOLDS_INT32(Iterator)) {

			Entity.Frame.Obj[Entity.Frame.NOfObj].I = bson_iter_int32(Iterator);
		}

		else if (strcmp(Key, "S") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {

			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.Frame.Obj[Entity.Frame.NOfObj].S, Key, MAX_STRING_LENGTH);
		}

		else if (strcmp(Key, "T") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {

			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.Frame.Obj[Entity.Frame.NOfObj].T, Key, MAX_STRING_LENGTH);
		}

	}
}

void CEntitySerializer::SerializeCmpDocument(bson_iter_t *Iterator, ENTITY_STR &Entity) 
{
 	char Key[MAX_STRING_LENGTH];

	while (bson_iter_next(Iterator)) {

		strcpy(Key, bson_iter_key(Iterator));

		if (strcmp(Key, "I") == 0 && BSON_ITER_HOLDS_INT32(Iterator)) {

			Entity.Frame.Cmp[Entity.Frame.NOfCmp].I = bson_iter_int32(Iterator);
		}

		else if (strcmp(Key, "S") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {
			
			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.Frame.Cmp[Entity.Frame.NOfCmp].S, Key, MAX_STRING_LENGTH);
		}

		else if (strcmp(Key, "T") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {
			
			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.Frame.Cmp[Entity.Frame.NOfCmp].T, Key, MAX_STRING_LENGTH);
		}

	}
}

void CEntitySerializer::SerializeEntityInfoDocument(bson_iter_t *Iterator, ENTITY_STR &Entity)
{
 	char Key[MAX_STRING_LENGTH];

	while (bson_iter_next(Iterator)) {

		strcpy_s(Key, bson_iter_key(Iterator));

		if (strcmp(Key, "entityText") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {

			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.EntityInfo[Entity.NOfEntityInfo].EntityText, Key, MAX_STRING_LENGTH);
		}

		else if (strcmp(Key, "stemmedEntity") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {

			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.EntityInfo[Entity.NOfEntityInfo].StemmedEntity, Key, MAX_STRING_LENGTH);
		}

		else if (strcmp(Key, "language") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {

			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.EntityInfo[Entity.NOfEntityInfo].Language, Key, MAX_STRING_LENGTH);
		}

		else if (strcmp(Key, "female") == 0 && BSON_ITER_HOLDS_BOOL(Iterator)) {

			Entity.EntityInfo[Entity.NOfEntityInfo].Female = bson_iter_bool(Iterator);
		}

		else if (strcmp(Key, "isReviewed") == 0 && BSON_ITER_HOLDS_BOOL(Iterator)) {

			Entity.EntityInfo[Entity.NOfEntityInfo].IsReviewed = bson_iter_bool(Iterator);
		}

	}
}


void CEntitySerializer::SerializeEntityInfoArray(bson_iter_t *Iterator, ENTITY_STR &Entity, int Count)
{
	bson_iter_t ArrayIterator;

	Entity.EntityInfo = new ENTITY_INFO_STR[Count];

	while (bson_iter_next(Iterator)) {

		if (BSON_ITER_HOLDS_DOCUMENT(Iterator) && bson_iter_recurse(Iterator, &ArrayIterator)) {

			if (Entity.NOfEntityInfo >= Count)  break;

			SerializeEntityInfoDocument(&ArrayIterator, Entity);
			Entity.NOfEntityInfo++;

		}

	}
}


void CEntitySerializer::SerializeFrameFactsDocument(bson_iter_t *Iterator, ENTITY_STR &Entity)
{
 	char Key[MAX_STRING_LENGTH];

	while (bson_iter_next(Iterator)) {

		strcpy(Key, bson_iter_key(Iterator));

		if (strcmp(Key, "entityId") == 0 && BSON_ITER_HOLDS_INT32(Iterator)) {

			Entity.FrameFacts[Entity.NOfFrameFacts].EntityId = bson_iter_int32(Iterator);
		}

		else if (strcmp(Key, "subjectId") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {
			
			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.FrameFacts[Entity.NOfFrameFacts].SubjectId, Key, MAX_STRING_LENGTH);
		}

		else if (strcmp(Key, "predicateId") == 0 && BSON_ITER_HOLDS_INT32(Iterator)) {

			Entity.FrameFacts[Entity.NOfFrameFacts].PredicateId = bson_iter_int32(Iterator);
		}


		else if (strcmp(Key, "node_id") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {

			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.FrameFacts[Entity.NOfFrameFacts].Node_id, Key, MAX_STRING_LENGTH);
		}

		else if (strcmp(Key, "parent") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {

			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.FrameFacts[Entity.NOfFrameFacts].Parent, Key, MAX_STRING_LENGTH);
		}

		else if (strcmp(Key, "previous_sibling") == 0 && BSON_ITER_HOLDS_UTF8(Iterator)) {

			CopyString(Key, (char*)bson_iter_utf8(Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			CopyString(Entity.FrameFacts[Entity.NOfFrameFacts].Previous_sibling, Key, MAX_STRING_LENGTH);
		}

		else if (strcmp(Key, "objectEntitiesValues") == 0 && BSON_ITER_HOLDS_ARRAY(Iterator)) {
			
		}

	}

}

void CEntitySerializer::SerializeFrameFactsArray(bson_iter_t *Iterator, ENTITY_STR &Entity, int Count)
{
	bson_iter_t ArrayIterator;

	Entity.FrameFacts = new FRAME_FACTS_STR[Count];

	while (bson_iter_next(Iterator)) {

		if (BSON_ITER_HOLDS_DOCUMENT(Iterator) && bson_iter_recurse(Iterator, &ArrayIterator)) {

			if (Entity.NOfEntityInfo >= Count)  break;

			SerializeFrameFactsDocument(&ArrayIterator, Entity);
			Entity.NOfFrameFacts++;

		}

	}
}


void CEntitySerializer::SerializeObjectsArray(bson_iter_t *Iterator, ENTITY_STR &Entity, int Count)
{

	Entity.Objects = new int[Count];

	while (bson_iter_next(Iterator)) {

		if (BSON_ITER_HOLDS_INT32(Iterator)) {

			if (Entity.NOfObjects >= Count)  break;

			Entity.Objects[Entity.NOfObjects] = bson_iter_int32(Iterator);
			Entity.NOfObjects++;
		}

	}
}

void AssignEntityType(char *Key, ENTITY_TYPE &EntityType)
{
	if (strcmp(Key, "class") == 0) {
		EntityType = _CLASS_ENTITY;
	}

	else if (strcmp(Key, "prop") == 0) {
		EntityType =  _PROP_ENTITY;
	}

	else if (strcmp(Key, "action") == 0) {
		EntityType =  _ACTION_ENTITY;
	}

	else if (strcmp(Key, "individual") == 0) {
		EntityType =  _INDIVIDUAL_ENTITY;
	}

	else if (strcmp(Key, "object") == 0) {
		EntityType =  _OBJECT_ENTITY;
	}

	else if (strcmp(Key, "adverb") == 0) {
		EntityType = _ADVERB_ENTITY;
	}
	
}

void CEntitySerializer::Serialize(const CBsonDocument &Document, ENTITY_STR &Entity)
{
	bson_iter_t Iterator;
	bson_iter_t SubIterator;
	char Key[MAX_STRING_LENGTH];
	int Count = 0;

	if (!bson_iter_init(&Iterator, Document.GetDocumentStr())) return;

	memset(&Entity, 0, sizeof(ENTITY_STR));

	//Entity.NOfEntityInfo = 0;
	//Entity.NOfFrameFacts = 0;
	//Entity.NOfObjects = 0;
 

	while (bson_iter_next(&Iterator)) {

		strcpy(Key, bson_iter_key(&Iterator));

		if (strcmp(Key, "entityType") == 0 && BSON_ITER_HOLDS_UTF8(&Iterator)) {

			CopyString(Key, (char*)bson_iter_utf8(&Iterator, NULL), MAX_STRING_LENGTH);
			ConvertUtf8ToAnsi(Key, Key);
			AssignEntityType(Key, Entity.EntityType);
 		}

		else if (strcmp(Key, "_id") == 0 && BSON_ITER_HOLDS_INT32(&Iterator)) {

			Entity.Id = bson_iter_int32(&Iterator);
		}

		else if (strcmp(Key, "parentId") == 0 && BSON_ITER_HOLDS_INT32(&Iterator)) {

			Entity.ParentId = bson_iter_int32(&Iterator);
		}


		else if (strcmp(Key, "entityInfo") == 0 && BSON_ITER_HOLDS_ARRAY(&Iterator)) {

			if (!bson_iter_recurse(&Iterator, &SubIterator)) continue;
			Count = GetCount(&SubIterator);
			
			if (!bson_iter_recurse(&Iterator, &SubIterator)) continue;
			SerializeEntityInfoArray(&SubIterator, Entity, Count);
		}

		else if (strcmp(Key, "frame") == 0 && BSON_ITER_HOLDS_DOCUMENT(&Iterator)) {

			if (!bson_iter_recurse(&Iterator, &SubIterator)) continue;

			SerializeFrameDocument(&SubIterator, Entity);
		}

		else if (strcmp(Key, "objects") == 0 && BSON_ITER_HOLDS_ARRAY(&Iterator)) {
			
			if (!bson_iter_recurse(&Iterator, &SubIterator)) continue;
			Count = GetCount(&SubIterator);

			if (!bson_iter_recurse(&Iterator, &SubIterator)) continue;
			SerializeObjectsArray(&SubIterator, Entity, Count);
		}

		else if (strcmp(Key, "ambClass") == 0 && BSON_ITER_HOLDS_BOOL(&Iterator)) {

			Entity.AmpClass = bson_iter_bool(&Iterator);
		}

		else if (strcmp(Key, "errorInStem") == 0 && BSON_ITER_HOLDS_BOOL(&Iterator)) {

			Entity.ErrorInStem = bson_iter_bool(&Iterator);
		}

		else if (strcmp(Key, "frameFacts") == 0 && BSON_ITER_HOLDS_ARRAY(&Iterator)) {
			
			if (!bson_iter_recurse(&Iterator, &SubIterator)) continue;
			Count = GetCount(&SubIterator);

			if (!bson_iter_recurse(&Iterator, &SubIterator)) continue;
			SerializeFrameFactsArray(&SubIterator, Entity, Count);
		}

		else if (strcmp(Key, "list") == 0 && BSON_ITER_HOLDS_BOOL(&Iterator)) {

			Entity.List = bson_iter_bool(&Iterator);
		}

		else if (strcmp(Key, "objectType") == 0 && BSON_ITER_HOLDS_INT32(&Iterator)) {

			Entity.ObjectType = bson_iter_int32(&Iterator);
		}

		else if (strcmp(Key, "templateId") == 0 && BSON_ITER_HOLDS_INT32(&Iterator)) {

			Entity.TemplateId = bson_iter_int32(&Iterator);	
		}

	}
}
