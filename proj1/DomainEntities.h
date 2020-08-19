#pragma once
#include "BsonSerializer.h"

#define		MAX_ENTITY_TEXT_LENGTH				256

typedef struct {

	char OriginalEntity[MAX_ENTITY_TEXT_LENGTH];
	char StemmedEntity[MAX_ENTITY_TEXT_LENGTH];
	char Language[MAX_ENTITY_TEXT_LENGTH];
	int Type_id;
	int Entity_id;
	int Parent_id;
	int ClassId;
	int PropertyId;
	bool AmbClass;
	bool Female;
	int *Individuals;
	int NOfIndividuals;

}DOMAIN_ENTITY_STR;


class CDomainEntities :	public CBsonSerializer<DOMAIN_ENTITY_STR>
{
public:
	void Serialize(const CBsonDocument &Document, DOMAIN_ENTITY_STR &Data) {}
	bool Serialize(const CBsonDocument &Document, DOMAIN_ENTITY_STR **Data, int &ArraySize);
	void SerializeIndividualsArray(bson_iter_t *EntityIter, DOMAIN_ENTITY_STR **Data, int EntityIndex);


};

