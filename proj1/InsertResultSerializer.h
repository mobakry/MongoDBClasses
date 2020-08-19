#pragma once
#include "BsonSerializer.h"

using namespace std;

typedef struct {
	bool Result;
	uint32_t InsertedCount;
}INSERT_RESULT_STR;

class CInsertResultSerializer: public CBsonSerializer<INSERT_RESULT_STR>{

public:
	void Serialize(const CBsonDocument &Document, INSERT_RESULT_STR &InsertResult);
	bool Serialize(const CBsonDocument &document, INSERT_RESULT_STR **Data, int &ArrayCount) { return true; }

 };

