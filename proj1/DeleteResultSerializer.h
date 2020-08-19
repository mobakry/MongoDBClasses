#pragma once
#include "BsonSerializer.h"

using namespace std;

typedef struct {

	bool Result;
	uint32_t DeletedCount;

}DELETE_RESULT_STR;


class CDeleteResultSerializer :public CBsonSerializer<DELETE_RESULT_STR>
{
public:
	void Serialize(const CBsonDocument &Document, DELETE_RESULT_STR &DeleteResult);
	bool Serialize(const CBsonDocument &document, DELETE_RESULT_STR **Data, int &ArrayCount) { return true; }

};

