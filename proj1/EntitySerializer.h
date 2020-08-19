#pragma once
#include "BsonSerializer.h"
#include "Global.h"

using namespace std;

#define MAX_STRING_LENGTH 128
#define MAX_NOF_ENTITY_INFO 10
#define MAX_NOF_FRAME_FACTS 10
#define MAX_NOF_OBJECTS 10
#define MAX_NOF_ARG 10


typedef struct {

	int EntityId;
	char SubjectId[MAX_STRING_LENGTH];
	int PredicateId;
	char Node_id[MAX_STRING_LENGTH];
	char Parent[MAX_STRING_LENGTH];
	char Previous_sibling[MAX_STRING_LENGTH];
 
}FRAME_FACTS_STR;

typedef struct {

	char EntityText[MAX_STRING_LENGTH];
	char StemmedEntity[MAX_STRING_LENGTH];
	char Language[MAX_STRING_LENGTH];
	bool Female;
	bool IsReviewed;

}ENTITY_INFO_STR;

typedef struct {

	int I;
	char S[MAX_STRING_LENGTH];
	char T[MAX_STRING_LENGTH];

}ARG_STR;

typedef struct {

	bool Request;
	bool RequestGain;
	bool RelObj;
	bool RelSbj;
	bool DomaninEllipsis;
	bool EllipsisExceptObj;
	bool SbjMandatory;
	bool FramePropLinkedToObj;
	bool GenObjSbj;
	bool GenSbjObj;
	bool ExactObject;

}FRAME_FEAT_STR;

typedef struct {

	int SenseId;
	char EntityId[MAX_STRING_LENGTH];
	char ParentId[MAX_STRING_LENGTH];
	char Type[MAX_STRING_LENGTH];

	ARG_STR *Sbj;
	int NOfSbj;

	ARG_STR	*Obj;
	int NOfObj;

	ARG_STR *Cmp;
	int NOfCmp;

	FRAME_FEAT_STR	FrameFeat;

}FRAME_STR;

enum ENTITY_TYPE{ 
	_CLASS_ENTITY, 
	_PROP_ENTITY,
	_ACTION_ENTITY,
	_INDIVIDUAL_ENTITY,
	_OBJECT_ENTITY,
	_ADVERB_ENTITY
};


typedef struct {

	int Id;
	int ObjectType;
	int ParentId;
	int TemplateId;

	bool AmpClass;
	bool List;
	bool ErrorInStem;

	ENTITY_TYPE EntityType;

	FRAME_STR Frame;

	int *Objects;
	int NOfObjects;

	ENTITY_INFO_STR *EntityInfo;
	int NOfEntityInfo;
	
	FRAME_FACTS_STR *FrameFacts;
	int NOfFrameFacts;

	
}ENTITY_STR;

 

class CEntitySerializer :public CBsonSerializer<ENTITY_STR>
{
public:

	void Serialize(const CBsonDocument &Document, ENTITY_STR &Entity);
	bool Serialize(const CBsonDocument &document, ENTITY_STR **Data, int &ArrayCount) { return true; }


private:

	void SerializeEntityInfoArray(bson_iter_t *Iterator, ENTITY_STR &Entity, int Count);
	void SerializeEntityInfoDocument(bson_iter_t *Iterator, ENTITY_STR &Entity);

	void SerializeFrameFactsArray(bson_iter_t *Iterator, ENTITY_STR &Entity, int Count);
	void SerializeFrameFactsDocument(bson_iter_t *Iterator, ENTITY_STR &Entity);

	void SerializeObjectsArray(bson_iter_t *Iterator, ENTITY_STR &Entity, int Count);

	void SerializeFrameDocument(bson_iter_t *Iterator, ENTITY_STR &Entity);


	void SerializeSbjArray(bson_iter_t *Iterator, ENTITY_STR &Entity, int Count);
	void SerializeObjArray(bson_iter_t *Iterator, ENTITY_STR &Entity, int Count);
	void SerializeCmpArray(bson_iter_t *Iterator, ENTITY_STR &Entity, int Count);

	void SerializeSbjDocument(bson_iter_t *Iterator, ENTITY_STR &Entity);
	void SerializeObjDocument(bson_iter_t *Iterator, ENTITY_STR &Entity);
	void SerializeCmpDocument(bson_iter_t *Iterator, ENTITY_STR &Entity);

};

